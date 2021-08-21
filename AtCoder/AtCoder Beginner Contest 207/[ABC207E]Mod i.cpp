#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
using namespace std;

const int MOD=1e9+7;

int n;

LL a[3001],sum[3001];
int dp[3001][3001];

int s[3001][3001];

void Add(int &x,int y) {x=x+y;if (x>=MOD) x-=MOD;}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%lld",a+i);
    sum[1]=a[1];rep(i,2,n) sum[i]=sum[i-1]+a[i];
    memset(dp,0,sizeof(dp));dp[0][0]=1;s[0][0]=1;
    rep(i,1,n)
    {
        rep(j,1,i) dp[i][j]=s[j-1][sum[i]%j];
        rep(j,1,i) Add(s[j][sum[i]%(j+1)],dp[i][j]);
    }
    int ans=0;rep(i,1,n) Add(ans,dp[n][i]);
    printf("%d\n",ans);return 0;
}