#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=5000;

int n,m;
int dp[5048][5048],ans[5048][5048];
char s1[MAXN+48],s2[MAXN+48];

int main ()
{
	scanf("%s%s",s1+1,s2+1);n=strlen(s1+1);m=strlen(s2+1);
	memset(dp,0,sizeof(dp));
	rep(i,1,n) rep(j,1,m)
		if (s1[i]!=s2[j]) dp[i][j]=0; else dp[i][j]=dp[i-1][j-1]+1;
	rep(i,1,n) rep(j,1,m) ans[i][j]=max(ans[i][j-1],max(ans[i-1][j],dp[i][j])); 
	rep(i,1,n-1) printf("%d ",ans[i][m]);
	printf("%d\n",ans[n][m]);
	return 0;
}