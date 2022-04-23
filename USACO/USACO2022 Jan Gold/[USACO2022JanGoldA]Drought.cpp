#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

const int MOD=1e9+7;

int n,h[101];
int dp[101][1001],sum[101][1001];

int add(int x) {if (x>=MOD) x-=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}

int solve(int target)
{
    memset(dp,0,sizeof(dp));
    rep(i,0,h[1]-target) dp[1][i]=1;
    rep(i,2,n)
    {
        dp[i][h[i]-target]=dp[i-1][0];
        REP(j,h[i]-target-1,0)
            dp[i][j]=add(dp[i][j+1]+dp[i-1][h[i]-target-j]);
    }
    return dp[n][0];
}

int main ()
{
    scanf("%d",&n);int minn=2000;
    rep(i,1,n) scanf("%d",h+i),minn=min(minn,h[i]);
    if (~n&1) printf("%d\n", solve(0));
    else
    {
        int ans=0;
        for (int i=0;i<=minn;i++) Add(ans,solve(i));
        printf("%d\n",ans);
    }
    return 0;
}