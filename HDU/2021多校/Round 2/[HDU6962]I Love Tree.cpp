#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
#define LL long long
#define LOWBIT(x) (x & (-x))
using namespace std;

const int MAXN=1e5;

int n,q;
vector<int> v[MAXN+48];
int L[MAXN+48],R[MAXN+48],id,fa[MAXN+48];
int anc[MAXN+48][21],depth[MAXN+48];

void dfs(int cur,int father)
{
    L[cur]=++id;fa[cur]=father;
    anc[cur][0]=father;rep(i,1,20) anc[cur][i]=anc[anc[cur][i-1]][i-1];
    for (auto y : v[cur]) if (y!=father) depth[y]=depth[cur]+1,dfs(y,cur);
    R[cur]=id;
}

int query_lca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    REP(i,20,0) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return u;
    REP(i,20,0) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return fa[u];
}

struct BIT
{
    LL c[MAXN+48];
    void init() {memset(c,0,sizeof(c));}
    void modify(int x,LL delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
    LL query(int x) {LL res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
    LL Query(int l,int r) {return query(r)-query(l-1);}
}t1,t2,t3;

void doit(int cur,LL tag,int type)
{
    if (!cur) return;
    t1.modify(L[cur],tag*tag*type);
    t2.modify(L[cur],tag);
    t3.modify(L[cur],type);
}

LL query(int cur)
{
    return t1.Query(L[cur],R[cur])-1ll*2*depth[cur]*t2.Query(L[cur],R[cur])+1ll*depth[cur]*depth[cur]*t3.Query(L[cur],R[cur]);
}

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    scanf("%d",&n);int x,y,op;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    id=0;depth[1]=1;dfs(1,0);
    scanf("%d",&q);t1.init();t2.init();t3.init();
    while (q--)
    {
        scanf("%d",&op);
        if (op==1)
        {
            scanf("%d%d",&x,&y);
            int LCA=query_lca(x,y),len=depth[x]-depth[LCA]+depth[y]-depth[LCA]+1;
            doit(x,depth[x]+1,1);doit(fa[LCA],-depth[x]-1,-1);
            if (LCA!=y)
            {
                doit(y,depth[y]-len,1);
                doit(LCA,-depth[y]+len,-1);
            }
        }
        else
        {
            scanf("%d",&x);
            printf("%lld\n",query(x));
        }
    }
    return 0;
}