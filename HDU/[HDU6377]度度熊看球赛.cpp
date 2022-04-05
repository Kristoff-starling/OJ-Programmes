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

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int fac[MAXN+48],inv[MAXN+48],finv[MAXN+48];
inline void init_inv()
{
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (register int i=2;i<=MAXN;i++)
	{
		fac[i]=(1ll*fac[i-1]*i)%MOD;
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(1ll*finv[i-1]*inv[i])%MOD;
	}
}

inline int C(int x,int y)
{
	if (x<y) return 0;
	return ((1ll*fac[x]*finv[y])%MOD*finv[x-y])%MOD;
}

int dp[MAXN+48][MAXN+48];
int pw[MAXN+48];

int main ()
{
	init_inv();int i,j;
	dp[0][0]=1;
	for (i=0;i<=MAXN-1;i++)
		for (j=0;j<=i;j++)
			if (dp[i][j])
			{
				dp[i+1][j]=add(dp[i+1][j]+(1ll*dp[i][j]*j)%MOD);
				dp[i+1][j+1]=add(dp[i+1][j+1]+(1ll*dp[i][j]*(2*i-j+1))%MOD);
				if (j>=2) dp[i+1][j-2]=add(dp[i+1][j-2]+(1ll*dp[i][j]*C(j,2))%MOD);
				if (j) dp[i+1][j-1]=add(dp[i+1][j-1]+((1ll*dp[i][j]*j)%MOD*(2*i-j+1))%MOD);
				dp[i+1][j]=add(dp[i+1][j]+(1ll*dp[i][j]*C(2*i-j+1,2))%MOD);
			}
	pw[0]=1;for (i=1;i<=MAXN;i++) pw[i]=add(pw[i-1]+pw[i-1]);
	int n,d;
	while (scanf("%d%d",&n,&d)!=EOF)
	{
		int ans=0,coef=1;
		for (i=0;i<=n;i++)
		{
			ans=add(ans+(1ll*dp[n][i]*coef)%MOD);
			coef=(1ll*coef*d)%MOD;
		}
		ans=(1ll*ans*pw[n])%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
