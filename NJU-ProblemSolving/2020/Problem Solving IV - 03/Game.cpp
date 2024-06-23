#include <bits/stdc++.h>
#define pb push_back
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
using namespace std;

const int MAXN=1e5;

int n;
vector<int> v[MAXN+48];

int dp[MAXN+48][2];

void dfs(int cur,int father)
{
    dp[cur][0]=0;dp[cur][1]=1;
    for (auto y : v[cur]) if (y!=father) dfs(y,cur),dp[cur][0]+=dp[y][1],dp[cur][1]+=min(dp[y][0],dp[y][1]);
}

int main ()
{
    scanf("%d",&n);int x,k,y;
    rep(i,1,n)
    {
        scanf("%d%d",&x,&k);++x;
        while (k--)
        {
            scanf("%d",&y);++y;
            v[x].pb(y);v[y].pb(x);
        }
    }
    dfs(1,-1);
    printf("%d\n",min(dp[1][0],dp[1][1]));
    return 0;
}