#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=2000;

int n;
int dp[23][2001][2001];

void check_max(int &x,int y) {if (y>x) x=y;}

int main ()
{
    scanf("%d",&n);
    memset(dp,-1,sizeof(dp));
    dp[0][0][0]=1;dp[0][1][0]=dp[0][0][1]=0;
    rep(t,0,20)
    {
        rep(i,0,n) rep(j,0,i)
        {
            int k=dp[t][j][i-j],w=dp[t][i-j][j];
            if (k>=0) check_max(dp[t+1][i][min(k,n-i)],w);
        }
        rep(i,0,n) if (dp[t][0][i]!=-1)
            rep(j,0,n-i) if (dp[t][i][j]!=-1)
            {
                int k=dp[t][i][j];
                check_max(dp[t+1][i][min(k,n-i)],dp[t][0][i]+j);
                check_max(dp[t+1][i][min(dp[t][0][i]+j,n-i)],k);
            }
        rep(i,0,n) REP(j,n-i-1,0) check_max(dp[t+1][i][j],dp[t+1][i][j+1]);
    }
    rep(i,1,n)
    {
        int ans=0;
        while (dp[ans][n-i+1][i-1]<0) ans++;
        printf("%d ",ans);
    }
    puts("");return 0;
}