#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=1e6;

int n,a[MAXN+48];
Pair dp[MAXN+48];

Pair Merge(Pair a,Pair b)
{
    Pair res;
    if (a.x>=b.x) res.x=a.x,res.y=max(a.y,b.x);
    else res.x=b.x,res.y=max(b.y,a.x);
    return res;
}

int main ()
{
    scanf("%d",&n);rep(i,0,(1<<n)-1) scanf("%d",a+i),dp[i]=mp(a[i],0);
    rep(j,0,n-1) rep(i,0,(1<<n)-1) if (i>>j&1) dp[i]=Merge(dp[i],dp[i^(1<<j)]);
    int ans=dp[0].x+dp[0].y;
    rep(i,1,(1<<n)-1)
    {
        ans=max(ans,dp[i].x+dp[i].y);
        printf("%d\n",ans);
    }
    return 0;
}