#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=1e5;

int n,q;
double p[MAXN+48],dp[MAXN+48],psum[MAXN+48];int fa[MAXN+48];
vector<int> v[MAXN+48];

inline void dfs(int cur,int father)
{
	dp[cur]=psum[cur]=0;fa[cur]=father;
	for (auto y : v[cur])
		if (y!=father) dfs(y,cur),dp[cur]+=dp[y],psum[cur]+=double(1.0-p[y]);
	dp[cur]-=double(1.0-p[cur])*(psum[cur]-1);
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%d",&n);int x,y;double nv;
	for (register int i=1;i<=n;i++) scanf("%lf",&p[i]);
	for (register int i=1;i<=n-1;i++)
	{
		scanf("%d%d",&x,&y);x++;y++;
		v[x].pb(y);v[y].pb(x);
	}
	dfs(1,-1);
	scanf("%d",&q);double ans=dp[1];
	while (q--)
	{
		scanf("%d%lf",&x,&nv);x++;
		ans+=double(1.0-p[x])*(psum[x]-1);ans-=double(1.0-nv)*(psum[x]-1);
		if (x!=1)
		{
			int f=fa[x];
			ans+=double(1.0-p[f])*(psum[f]-1);
			psum[f]-=double(1.0-p[x]);psum[f]+=double(1.0-nv);
			ans-=double(1.0-p[f])*(psum[f]-1);
		}
		p[x]=nv;
		printf("%lf\n",ans);
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}