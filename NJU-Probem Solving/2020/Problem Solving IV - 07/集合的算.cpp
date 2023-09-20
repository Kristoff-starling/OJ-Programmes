#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MOD=998244353;

int n,k;
int a[10048];
int dp[1048][1048];

void Add(int &x,int y) {x+=y;if (x>=MOD) x-=MOD;}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&k);
        rep(i,1,n) scanf("%d",a+i);
        memset(dp[0],0,sizeof(dp[0]));
        dp[0][0]=1;
        rep(i,1,n) rep(j,0,k)
        {
            dp[i][j]=dp[i-1][j];
            if (j-a[i]>=0) Add(dp[i][j],dp[i-1][j-a[i]]);
        }
        printf("%d\n", dp[n][k]);
    }
    return 0;
}