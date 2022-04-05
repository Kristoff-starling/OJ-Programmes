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
 
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    bool f;char ch;int res;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

const int MAXN=2000;
const int Height=1001;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

int n,k,q;
int dp[MAXN+48][MAXN+48],DP[MAXN+48];
int pw[MAXN+48];
int a[MAXN+48],g[MAXN+48],inv,K;

inline void construct_g()
{
	int i;
	for (i=1;i<=K;i++) a[i]=((1ll*sub(1-q)*pw[i-1])%MOD*dp[2][i-1])%MOD;
	g[K]=1;for (i=K;i>=1;i--) g[K-i]=sub(-a[i]);
	if (K&1) for (i=0;i<=K;i++) g[i]=sub(-g[i]);
	inv=quick_pow(g[K],MOD-2);
}

struct poly
{
	int a[MAXN*4+48],len;
	inline void clear() {for (register int i=0;i<len;i++) a[i]=0;}
	inline poly operator * (poly other)
	{
		poly res;res.len=len+other.len-1;res.clear();
		for (register int i=0;i<len;i++)
			for (register int j=0;j<other.len;j++)
				res.a[i+j]=add(res.a[i+j]+(1ll*a[i]*other.a[j])%MOD);
		for (register int i=res.len-1;i>=K;i--)
		{
			int tmp=(1ll*res.a[i]*inv)%MOD;
			for (register int j=i;j>=i-K;j--)
				res.a[j]=sub(res.a[j]-(1ll*g[j-i+K]*tmp)%MOD);
		}
		if (res.len>K) res.len=K;
		return res;
	}
};

inline poly quick_pow(poly x,int y)
{
	poly res;res.len=1;res.a[0]=1;
	while (y)
	{
		if (y&1) res=res*x,y--;
		x=x*x;y>>=1;
	}
	return res;
}

inline int solve(int limarea)
{
	int i,j,t;
	for (i=0;i<=Height+1;i++)
		for (j=0;j<=limarea;j++)
			dp[i][j]=0;
	dp[Height+1][0]=1;
	for (i=Height;i>=2;i--)
	{
		dp[i][0]=1;
		for (j=1;(i-1)*j<=limarea;j++)
		{
			for (t=0;t<=j-1;t++)
				dp[i][j]=add(dp[i][j]+(((1ll*dp[i][t]*sub(1-q))%MOD*dp[i+1][j-1-t])%MOD*pw[j-1-t])%MOD);
			dp[i][j]=add(dp[i][j]+(1ll*dp[i+1][j]*pw[j])%MOD);
		}
	}
	/*
	if (n<=MAXN)
	{
		DP[0]=1;
		for (i=1;i<=n;i++)
		{
			if (i<=limarea) DP[i]=(1ll*dp[2][i]*pw[i])%MOD; else DP[i]=0;
			for (j=0;j<=min(limarea,i-1);j++) DP[i]=add(DP[i]+(((1ll*DP[i-j-1]*sub(1-q))%MOD*dp[2][j])%MOD*pw[j])%MOD);
		}
		return DP[n];
	}
	*/
	DP[0]=1;
	for (i=1;i<=limarea;i++)
	{
		DP[i]=(1ll*dp[2][i]*pw[i])%MOD;
		for (j=0;j<=min(limarea,i-1);j++) DP[i]=add(DP[i]+(((1ll*DP[i-j-1]*sub(1-q))%MOD*dp[2][j])%MOD*pw[j])%MOD);
	}
	K=limarea+1;construct_g();
	poly base;base.len=2;base.clear();base.a[1]=1;
	poly res=quick_pow(base,n);int ans=0;
	for (i=0;i<=K-1;i++) ans=add(ans+(1ll*res.a[i]*DP[i])%MOD);
	return ans;
}

int main ()
{
	int i,x,y;
	n=getint();k=getint();x=getint();y=getint();
	q=(1ll*x*quick_pow(y,MOD-2))%MOD;
	pw[0]=1;for (i=1;i<=MAXN;i++) pw[i]=(1ll*pw[i-1]*q)%MOD;
	printf("%d\n",sub(solve(k)-solve(k-1)));
	return 0;
}
