#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int n,m;
char s[1000048];
char ss[1048];

int dp[1048][1048];

int nxt[1000048][27];

int main ()
{
	//freopen ("a.in","r",stdin);
	scanf("%s%s",s+1,ss+1);n=strlen(s+1);m=strlen(ss+1);
	rep(i,1,26) nxt[n][i]=n+1;
	REP(i,n-1,0)
	{
		rep(j,1,26) nxt[i][j]=nxt[i+1][j];
		nxt[i][s[i+1]-'a'+1]=i+1;
	}
	rep(i,0,m) rep(j,0,m) dp[i][j]=n+1;
	rep(i,0,m) dp[i][0]=0; 
	rep(i,1,m) rep(j,1,i)
	{
		dp[i][j]=dp[i-1][j];
		int pos=dp[i-1][j-1];
		if (pos<n) dp[i][j]=min(dp[i][j],nxt[pos][ss[i]-'a'+1]);
	}
	int ans=m;while (dp[m][ans]>n) ans--;
	printf("%d\n",ans);return 0;
}