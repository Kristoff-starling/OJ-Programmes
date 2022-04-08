#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,a[200048];
int dp[1100048];

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) scanf("%d",a+i),dp[a[i]]++;
    rep(i,0,19) rep(Mask,0,(1<<20)-1)
        if (Mask&(1<<i)) dp[Mask]+=dp[Mask^(1<<i)];
    long long ans=0;
    rep(i,1,n) ans+=dp[((1<<20)-1)^a[i]];
    printf("%lld\n",ans);return 0;
}