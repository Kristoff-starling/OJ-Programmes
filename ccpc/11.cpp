#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=1e5;

int n;
bool type[MAXN+48];vector<int> v[MAXN+48];
int w[MAXN+48],ans[MAXN+48];

int sz[MAXN+48],maxn[MAXN+48];
void dfs(int cur,int father)
{
    sz[cur]=1;
    for (auto y : v[cur]) if (y!=father && !type[y]) dfs(y,cur),sz[cur]+=sz[y];
}

int find_root(int cur,int father,int Sz)
{
    for (auto y : v[cur]) if (y!=father && !type[y] && sz[y]>Sz/2) return find_root(y,cur,Sz);
    return cur;
}

vector<int> V,vv[MAXN+48];

void dfs2(int cur,int father,int bel)
{
    if (maxn[cur]==w[cur]) V.pb(w[cur]),vv[bel].pb(w[cur]);
    for (auto y : v[cur]) if (y!=father && !type[y])
    {
        maxn[y]=max(maxn[cur],w[y]);
        dfs2(y,cur,bel);
    }
}

int bsearch(int cmp)
{
    if (!int(V.size())) return 0;
    if (V.back()<cmp) return 0;
    int l=0,r=int(V.size())-1,mid,aa;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (V[mid]<cmp) l=mid+1; else aa=mid,r=mid-1;
    }
    return int(V.size())-aa;
}

int bsearch(int bel,int cmp)
{
    if (!int(vv[bel].size())) return 0;
    if (vv[bel].back()<cmp) return 0;
    int l=0,r=int(vv[bel].size())-1,mid,aa;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (vv[bel][mid]<cmp) l=mid+1; else aa=mid,r=mid-1;
    }
    return int(vv[bel].size())-aa;
}

void calc(int cur,int father,int bel)
{
    ans[cur]+=bsearch(maxn[cur])-bsearch(bel,maxn[cur]);
    for (auto y : v[cur]) if (y!=father && !type[y]) calc(y,cur,bel);
}

void solve(int cur)
{
    dfs(cur,0);int rt=find_root(cur,0,sz[cur]);
    maxn[rt]=w[rt];V.pb(w[rt]);for (auto y : v[rt]) if (!type[y]) maxn[y]=max(w[y],w[rt]),dfs2(y,rt,y),sort(vv[y].begin(),vv[y].end());
    sort(V.begin(),V.end());
    ans[rt]+=bsearch(w[rt]);
    for (auto y : v[rt]) if (!type[y]) calc(y,rt,y);
    for (auto y : v[rt]) if (!type[y]) vv[y].clear();V.clear();
    type[rt]=true;for (auto y : v[rt]) if (!type[y]) solve(y);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) v[i].clear(),type[i]=false;
        int x,y;rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
        rep(i,1,n) scanf("%d",w+i),ans[i]=0;
        solve(1);
        rep(i,1,n) printf("%d\n",ans[i]);
    }
    return 0;
}