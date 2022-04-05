#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

const int MAXN=1e6;

int n;
int head[MAXN+48],to[MAXN*2+48],nxt[MAXN*2+48],tot;
inline void addedge(int s,int t) {to[++tot]=t;nxt[tot]=head[s];head[s]=tot;}

int fac[MAXN+48],ifac[MAXN+48],inv[MAXN+48];

inline void init()
{
	fac[0]=1;for (register int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[n]=quick_pow(fac[n],MOD-2);
	for (register int i=n-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
	inv[1]=1;for (register int i=2;i<=n;i++) inv[i]=1ll*ifac[i]*fac[i-1]%MOD;
}

int dp[MAXN+48],idp[MAXN+48],d[MAXN+48],depth[MAXN+48];

inline void dfs(int cur,int father)
{
	dp[cur]=1;idp[cur]=1;int cnt=0;
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;dfs(y,cur);cnt++;
			dp[cur]=1ll*dp[cur]*dp[y]%MOD;idp[cur]=1ll*idp[cur]*idp[y]%MOD;
		}
	}
	d[cur]=cnt;if (cur!=1) cnt++;
	dp[cur]=1ll*dp[cur]*fac[cnt]%MOD;idp[cur]=1ll*idp[cur]*ifac[cnt]%MOD;
}

int ans,anscnt;

inline void dfs2(int cur,int father,int curans)
{
	if (!d[cur])
	{
		if (depth[cur]>ans) ans=depth[cur],anscnt=curans;
		else if (depth[cur]==ans) Add(anscnt,curans);
		return;
	}
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=father)
		{
			int curdp;
			if (cur!=1) curdp=1ll*dp[cur]*inv[d[cur]+1]%MOD*idp[y]%MOD;
			else curdp=1ll*dp[cur]*inv[d[cur]]%MOD*idp[y]%MOD;
			dfs2(y,cur,1ll*curans*curdp%MOD);
		}
	}
}

int main ()
{
	Get(n);int x,y;
	for (register int i=1;i<=n-1;i++) Get(x,y),addedge(x,y),addedge(y,x);
	init();depth[1]=1;dfs(1,-1);
	ans=anscnt=0;dfs2(1,-1,1);
	printf("%d\n%d\n",(n-1)*2-(ans-1),anscnt);
	return 0;
}
