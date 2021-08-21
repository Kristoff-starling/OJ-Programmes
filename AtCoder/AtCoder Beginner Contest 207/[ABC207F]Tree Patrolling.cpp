#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MOD=1e9+7;

int n,sz[2048];
vector<int> v[2048];

int dp[3][2048][2048],DP[3][2048][2048];

int add(int x) {if (x>=MOD) x-=MOD;return x;}
void Add(int &x,int y) {x=x+y;if (x>=MOD) x-=MOD;}

void dfs(int cur,int father)
{
    sz[cur]=1;
    for (int i=0;i<int(v[cur].size());i++)
    {
        int to=v[cur][i];
        if (to!=father) dfs(to,cur),sz[cur]+=sz[to];
    }
    int N=int(v[cur].size())-1;if (cur==1) N++;
    rep(i,0,N) rep(j,0,sz[cur]) DP[0][i][j]=DP[1][i][j]=DP[2][i][j]=0;
    DP[0][0][0]=1;DP[2][0][1]=1;int i=0,ss=1;
    for (int t=0;t<=int(v[cur].size())-1;t++)
    {
        int to=v[cur][t];if (to==father) continue;
        ss+=sz[to];
        rep(j,0,ss) rep(k,0,min(j,sz[to]))
        {
            Add(DP[0][i+1][j],1ll*DP[0][i][j-k]*add(dp[0][to][k]+dp[1][to][k])%MOD);
            Add(DP[1][i+1][j],1ll*DP[1][i][j-k]*add(add(dp[0][to][k]+dp[1][to][k])+dp[2][to][k])%MOD);
            if (j-k-1>=0) Add(DP[1][i+1][j],1ll*DP[0][i][j-k-1]*dp[2][to][k]%MOD);
            if (j-k-1>=0) Add(DP[2][i+1][j],1ll*DP[2][i][j-k-1]*dp[0][to][k]%MOD);
            Add(DP[2][i+1][j],1ll*DP[2][i][j-k]*add(dp[1][to][k]+dp[2][to][k])%MOD);
        }
        i++;
    }
    rep(sta,0,2) rep(j,0,sz[cur]) dp[sta][cur][j]=DP[sta][N][j];
}

int main ()
{
    scanf("%d",&n);int x,y;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    dfs(1,0);
    rep(i,0,n)
    {
        int ans=0;
        rep(sta,0,2) Add(ans,dp[sta][1][i]);
        printf("%d\n",ans);
    }
    return 0;
}