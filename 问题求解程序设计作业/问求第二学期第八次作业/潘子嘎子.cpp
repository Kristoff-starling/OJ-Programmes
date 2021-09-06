#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int n,m;
int w1[50048],v1[50048],w2[50048],v2[50048];

int dp[50001][1001];

int main ()
{
	//freopen ("a.in","r",stdin);
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",w1+i);rep(i,1,n) scanf("%d",v1+i);
	rep(i,1,n) scanf("%d",w2+i);rep(i,1,n) scanf("%d",v2+i);
	rep(i,1,n) rep(j,1,m)
	{
		dp[i][j]=max(dp[i][j],dp[i-1][j]);
		if (j>=w1[i]) dp[i][j]=max(dp[i][j],dp[i-1][j-w1[i]]+v1[i]);
		if (j>=w2[i]) dp[i][j]=max(dp[i][j],dp[i-1][j-w2[i]]+v2[i]);
	}
	int ans=0;rep(i,0,m) ans=max(ans,dp[n][i]);
	printf("%d\n",ans);return 0; 
}