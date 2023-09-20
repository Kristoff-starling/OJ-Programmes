#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

const int MAXN=10000;

int n,q,w[MAXN+48],xsum[MAXN+48];
int anc[MAXN+48][21],depth[MAXN+48];
vector<int> v[MAXN+48];

void dfs(int cur,int father)
{
    anc[cur][0]=father;
    depth[cur]=depth[father]+1;
    xsum[cur]=(xsum[father]^w[cur]);
    rep(j,1,20) anc[cur][j]=anc[anc[cur][j-1]][j-1];
    for (auto y : v[cur]) if (y!=father) dfs(y,cur);
}

int query_lca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    REP(i,20,0) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return v;
    REP(i,20,0) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return anc[u][0];
}

int main ()
{
    scanf("%d%d",&n,&q);int x,y;
    rep(i,1,n) scanf("%d",w+i);
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
    dfs(1,0);
    while (q--)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",xsum[x]^xsum[y]^w[query_lca(x,y)]);
    }
    return 0;
}