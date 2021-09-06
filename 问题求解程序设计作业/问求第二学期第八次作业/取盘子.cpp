#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int n,k,p;
int v[1048][1048];
int sum[1048][1048];
int dp[51][2048];

int main ()
{
//	freopen ("a.in","r",stdin);
	scanf("%d%d%d",&n,&k,&p);
	rep(i,1,n) rep(j,1,k) scanf("%d",&v[i][j]);
	rep(i,1,n)
	{
		sum[i][0]=0;
		rep(j,1,k) sum[i][j]=sum[i][j-1]+v[i][j];
	}
	rep(i,0,n) rep(j,0,p) dp[i][j]=-1e9;rep(i,0,n) dp[i][0]=0;
	rep(i,1,n) rep(j,1,p) rep(m,0,min(k,j)) dp[i][j]=max(dp[i][j],dp[i-1][j-m]+sum[i][m]);
	printf("%d\n",dp[n][p]);return 0;
}