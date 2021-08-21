#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;

int n;
int a[148][148],b[148][148];
vector<Pair> dp[101][101];

bool cmp(Pair x,Pair y) {return 1ll*x.x*x.y>1ll*y.x*y.y;}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);
        rep(i,1,n) rep(j,1,n) scanf("%d",&a[i][j]);
        rep(i,1,n) rep(j,1,n) scanf("%d",&b[i][j]);
        rep(i,1,n) rep(j,1,n) dp[i][j].clear();
        dp[1][1].pb(mp(a[1][1],b[1][1]));
        rep(i,1,n) rep(j,1,n)
        {
            if (i!=1) for (auto item : dp[i-1][j]) dp[i][j].pb(mp(item.x+a[i][j],item.y+b[i][j]));
            if (j!=1) for (auto item : dp[i][j-1]) dp[i][j].pb(mp(item.x+a[i][j],item.y+b[i][j]));
            sort(dp[i][j].begin(),dp[i][j].end(),cmp);
            while (int(dp[i][j].size())>=100) dp[i][j].pop_back();
        }
        printf("%lld\n",1ll*dp[n][n][0].x*dp[n][n][0].y);
    }
    return 0;
}