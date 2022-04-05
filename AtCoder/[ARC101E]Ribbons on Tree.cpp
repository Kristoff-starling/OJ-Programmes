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
const int MOD=1e9+7;
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

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=5000;

int n;
vector<int> v[MAXN+48];int sz[MAXN+48];
int dp[MAXN+48][MAXN+48][2],dp2[2][MAXN+48][2];
int fac[MAXN+48];

inline void init_fac()
{
	fac[0]=1;
	for (register int i=2;i<=n;i+=2) fac[i]=1ll*fac[i-2]*(i-1)%MOD;
}

inline void dfs(int cur,int father)
{
	sz[cur]=1;int cu=0,nx=1;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		register int y=v[cur][i];
		if (y!=father) dfs(y,cur),sz[cur]+=sz[y];
	}
	dp2[0][1][0]=1;int cursz=1;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		register int y=v[cur][i];
		if (y!=father)
		{
			for (register int j=1;j<=cursz;j++)
				for (register int t1=0;t1<=1;t1++)
				{
					for (register int k=1;k<=sz[y];k++)
						for (register int t2=0;t2<=1;t2++)
						{
							//cut the edge
							Add(dp2[nx][j][t1^t2^1],1ll*dp2[cu][j][t1]*dp[y][k][t2]%MOD*fac[k]%MOD);
							//keep the edge
							Add(dp2[nx][j+k][t1^t2],1ll*dp2[cu][j][t1]*dp[y][k][t2]%MOD);
						}
					dp2[cu][j][t1]=0;
				}
			cu^=1;nx^=1;cursz+=sz[y];
		}
	}
	for (register int i=1;i<=sz[cur];i++)
		for (register int t=0;t<=1;t++)
			dp[cur][i][t]=dp2[cu][i][t],dp2[cu][i][t]=0;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);int x,y;
	for (register int i=1;i<=n-1;i++)
	{
		io.Get(x);io.Get(y);
		v[x].pb(y);v[y].pb(x);
	}
	init_fac();
	dfs(1,-1);
	int ans=0;
	for (register int i=1;i<=n;i++) Add(ans,1ll*dp[1][i][0]*fac[i]%MOD);
	for (register int i=1;i<=n;i++) Sub(ans,1ll*dp[1][i][1]*fac[i]%MOD);
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}