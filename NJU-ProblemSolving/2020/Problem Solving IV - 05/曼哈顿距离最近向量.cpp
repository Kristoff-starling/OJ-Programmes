#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const LL LINF=2e16;

int n,m,a[100048],b[100048];
LL dp[2][20048];

int myabs(int x) {return x>=0?x:-x;}

void clear(int layer) {for (int i=0;i<=m;i++) dp[layer][i]=LINF;}

int main ()
{
    scanf("%d%d",&m,&n);
    rep(i,1,m) scanf("%d",b+i);
    rep(i,1,n) scanf("%d",a+i);
    sort(a+1,a+n+1);sort(b+1,b+m+1);
    int cur=0,nxt=1;memset(dp[0],0,sizeof(dp[0]));
    LL ans=LINF;
    rep(i,1,n)
    {
        // dp[nxt][j] <=> dp[i][j]
        dp[nxt][0]=LINF;
        rep(j,1,m)
        {
            dp[nxt][j]=min(dp[nxt][j-1],dp[cur][j-1]+myabs(a[i]-b[j]));
            if (i==n) ans=min(ans,dp[nxt][j]);
        }
        cur^=1;nxt^=1;
    }
    printf("%lld\n",ans);
    return 0;
}