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

const int MAXN=100;

int n,m;
int dp[MAXN+48][MAXN+48];

int main ()
{
	int i,j,ca;ca=getint();
	while (ca--)
	{
		n=getint();m=getint();
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				dp[i][j]=INF;
		dp[0][0]=1;
		for (i=1;i<=n;i++)
		{
			int A=getint(),B=getint();
			for (j=0;j<=i-1;j++)
				if ((1ll*dp[i-1][j]*(B+1))<=INF) dp[i][j+1]=min(dp[i][j+1],dp[i-1][j]*(B+1));
			for (j=0;j<=i;j++)
				dp[i][j]=min(dp[i][j],dp[i-1][j]);
		}
		int ans=0;
		while (dp[n][ans]<=m) ans++;ans--;
		printf("%d\n",ans);
	}
	return 0;
}
