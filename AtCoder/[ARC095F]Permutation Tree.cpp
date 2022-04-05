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

const int MAXN=1e5;

int n;
vector<int> v[MAXN+48];

int depth[MAXN+48],fa[MAXN+48];
inline void dfs(int cur,int father)
{
	for (auto y : v[cur])
		if (y!=father) depth[y]=depth[cur]+1,fa[y]=cur,dfs(y,cur);
}

bool visited[MAXN+48];int cnt[MAXN+48];
int dlist[MAXN+48],tot;
inline void dfs(int cur)
{
	visited[cur]=true;
	for (auto y : v[cur])
		if (!visited[y]) cnt[cur]++,depth[y]=depth[cur]+1,dfs(y);
}

inline bool check_invalid()
{
	memset(visited,false,sizeof(visited));
	for (register int i=1;i<=tot;i++) visited[dlist[i]]=true;
	for (register int i=1;i<=n;i++)
		if (!visited[i] && depth[i]!=2) return true;
	return false;
}

int a[MAXN+48],ans[MAXN+48];

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
	depth[1]=1;dfs(1,-1);
	int mdepth=-1,st,ed;
	for (register int i=1;i<=n;i++) if (depth[i]>mdepth) mdepth=depth[i],st=i;
	depth[st]=1;dfs(st,-1);
	mdepth=-1;
	for (register int i=1;i<=n;i++) if (depth[i]>mdepth) mdepth=depth[i],ed=i;
	for (register int cur=ed;cur!=st;cur=fa[cur]) dlist[++tot]=cur;dlist[++tot]=st;
	for (register int i=1;i<=tot;i++) visited[dlist[i]]=true,depth[dlist[i]]=1;
	for (register int i=1;i<=tot;i++) dfs(dlist[i]);
	if (check_invalid()) {io.Print(-1,'\n');io.flush();return 0;}	
	for (register int i=1;i<=tot;i++) a[i]=cnt[dlist[i]]+1;
	int l=1,r=tot;bool res=false;
	while (l<=r)
	{
		if (a[l]<a[r]) {res=false;break;}
		if (a[l]>a[r]) {res=true;break;}
		l++;r--;
	}
	if (res) reverse(a+1,a+tot+1);int pt=0,p=0;
	for (register int i=1;i<=tot;i++)
	{
		int tmp=++pt;
		for (register int j=1;j<=a[i]-1;j++) ans[++p]=++pt;
		ans[++p]=tmp;
	}
	for (register int i=1;i<=n;i++) io.Print(ans[i],' ');io.Writechar('\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}