#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=(1<<20);
const int INF=1e9;

int n;
int dp[MAXN+48][21],ga[21][21];

int main ()
{
    scanf("%d",&n);rep(i,1,n) rep(j,1,n) scanf("%d",&ga[i][j]);
    rep(k,1,n) rep(i,1,n) rep(j,1,n) ga[i][j]=min(ga[i][j],ga[i][k]+ga[k][j]);
    rep(i,1,(1<<n)-1) rep(j,1,n) dp[i][j]=INF;
    rep(i,1,n) dp[1<<(i-1)][i]=0;
    rep(Mask,1,(1<<n)-1) rep(i,1,n) rep(j,1,n)
        if (!(Mask&(1<<(j-1)))) dp[Mask^(1<<(j-1))][j]=min(dp[Mask^(1<<(j-1))][j],dp[Mask][i]+ga[i][j]);
    int ans=INF;
    rep(i,1,n) ans=min(ans,dp[(1<<n)-1][i]);
    printf("%d\n",ans);return 0;
}