#include <bits/stdc++.h>
#define Pair pair<int,int>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define REP(i,a,b) for (int i=(a);i>=(b);--i)
using namespace std;

const int MAXN=2e5;

int n,q,root;
int anc[MAXN+48][21];
int depth[MAXN+48],len[MAXN+48];
vector<Pair> v[MAXN+48];

void dfs(int cur,int father,int last)
{
    anc[cur][0]=father;depth[cur]=depth[father]+1;len[cur]=len[father]+last;
    rep(j,1,20) anc[cur][j]=anc[anc[cur][j-1]][j-1];
    for (auto item : v[cur]) if (item.x!=father) dfs(item.x,cur,item.y);
}

int query_lca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    REP(i,20,0) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return u;
    REP(i,20,0) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return anc[u][0];
}

int main ()
{
    scanf("%d%d",&n,&q);int x,y,c,LCA;
    rep(i,1,n-1) scanf("%d%d%d",&x,&y,&c),v[x].pb(mp(y,c)),v[y].pb(mp(x,c));
    dfs(1,0,0);
    while (q--)
    {
        scanf("%d%d",&x,&y);
        LCA=query_lca(x,y);
        printf("%d\n",len[x]+len[y]-len[LCA]-len[LCA]);
    }
    return 0;
}