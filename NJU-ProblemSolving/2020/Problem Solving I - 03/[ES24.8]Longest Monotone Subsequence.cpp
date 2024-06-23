#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define RPE(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

template<typename T> inline void check_max(T &x,T y) {if (x<y) x=y;}
template<typename T> inline void check_min(T &x,T y) {if (x>y) x=y;}

int n,a[48],dp[48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);int ans=0;
    rep(i,1,n) dp[i]=1;rep(i,2,n) rep(j,1,i-1) if (a[i]<a[j]) check_max(dp[i],dp[j]+1);
    rep(i,1,n) check_max(ans,dp[i]);
    rep(i,1,n) dp[i]=1;rep(i,2,n) rep(j,1,i-1) if (a[i]>a[j]) check_max(dp[i],dp[j]+1);
    rep(i,1,n) check_max(ans,dp[i]);
    printf("%d\n",ans);return 0;
}