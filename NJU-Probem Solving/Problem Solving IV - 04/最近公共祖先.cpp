#include <bits/stdc++.h>
#define pb push_back
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define REP(i,a,b) for (int i=(a);i>=(b);--i)
using namespace std;

const int MAXN=2e5;

int n,q,root;
int anc[MAXN+48][21];
int depth[MAXN+48];
vector<int> v[MAXN+48];

void dfs(int cur,int father)
{
    anc[cur][0]=father;depth[cur]=depth[father]+1;
    rep(j,1,20) anc[cur][j]=anc[anc[cur][j-1]][j-1];
    for (auto to : v[cur]) if (to!=father) dfs(to,cur);
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
    scanf("%d%d%d",&n,&q,&root);int x,y;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    dfs(root,0);
    while (q--)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",query_lca(x,y));
    }
    return 0;
}