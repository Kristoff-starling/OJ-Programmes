#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=3e5;

template<typename T> void check_max(T &x,T y) {if (y>x) x=y;}
template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}

int n;
vector<int> v1[MAXN+48],v2[MAXN+48];
int in[MAXN+48],out[MAXN+48],depth[MAXN+48],ind;
int h[MAXN+48],ans;

int root1[MAXN+48];
struct SegmentTree1
{
    int tot,lazy[MAXN*40+48],lson[MAXN*40+48],rson[MAXN*40+48];
    int Create() {++tot;lazy[tot]=lson[tot]=rson[tot]=0;return tot;}
    void init() {tot=0;root1[0]=Create();rep(i,1,n) root1[i]=0;}
    void modify(int last,int &cur,int left,int right,int val,int l,int r)
    {
        if (!cur) cur=Create();
        lazy[cur]=lazy[last];lson[cur]=lson[last];rson[cur]=rson[last];
        if (left<=l && r<=right) {lazy[cur]=val;return;}
        int mid=(l+r)>>1;
        if (left<=mid) lson[cur]=Create(),modify(lson[last],lson[cur],left,right,val,l,mid);
        if (mid+1<=right) rson[cur]=Create(),modify(rson[last],rson[cur],left,right,val,mid+1,r);
    }
    int query(int cur,int pos,int l,int r)
    {
        if (!cur) return 0;
        if (l==r) return lazy[cur];
        int res=lazy[cur],mid=(l+r)>>1;
        if (pos<=mid) check_max(res,query(lson[cur],pos,l,mid)); else check_max(res,query(rson[cur],pos,mid+1,r));
        return res;
    }
}tree1;

int root2[MAXN+48];
struct SegmentTree2
{
    int lson[MAXN*40+48],rson[MAXN*40+48],maxn[MAXN*40+48],tot;
    int Create() {++tot;lson[tot]=rson[tot]=maxn[tot]=0;return tot;}
    void init() {tot=0;root2[0]=Create();rep(i,1,n) root2[i]=0;}
    void modify(int last,int &cur,int pos,int val,int l,int r)
    {
        if (!cur) cur=Create();
        lson[cur]=lson[last];rson[cur]=rson[last];maxn[cur]=val;
        if (l==r) return;
        int mid=(l+r)>>1;
        if (pos<=mid) lson[cur]=Create(),modify(lson[last],lson[cur],pos,val,l,mid);
        else rson[cur]=Create(),modify(rson[last],rson[cur],pos,val,mid+1,r);
    }
    int query(int cur,int left,int right,int l,int r)
    {
        if (!cur) return 0;
        if (left<=l && r<=right) return maxn[cur];
        int res=0,mid=(l+r)>>1;
        if (left<=mid) check_max(res,query(lson[cur],left,right,l,mid));
        if (mid+1<=right) check_max(res,query(rson[cur],left,right,mid+1,r));
        return res;
    }
}tree2;

void dfs2(int cur,int father)
{
    in[cur]=++ind;
    for (auto y : v2[cur]) if (y!=father) dfs2(y,cur);
    out[cur]=ind;
}

void dfs1(int cur,int father)
{
    depth[cur]=depth[father]+1;
    root1[cur]=tree1.Create();tree1.modify(root1[father],root1[cur],in[cur],out[cur],depth[cur],1,n);
    root2[cur]=tree2.Create();tree2.modify(root2[father],root2[cur],in[cur],depth[cur],1,n);
    h[cur]=max(tree1.query(root1[father],in[cur],1,n),tree2.query(root2[father],in[cur],out[cur],1,n));
    check_max(h[cur],h[father]);check_max(ans,depth[cur]-h[cur]);
    for (auto y : v1[cur]) if (y!=father) dfs1(y,cur);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);int x,y;
        tree1.init();tree2.init();rep(i,1,n) v1[i].clear(),v2[i].clear();
        rep(i,1,n-1) scanf("%d%d",&x,&y),v1[x].pb(y),v1[y].pb(x);
        rep(i,1,n-1) scanf("%d%d",&x,&y),v2[x].pb(y),v2[y].pb(x);
        ind=0;dfs2(1,0);
        ans=0;depth[0]=0;dfs1(1,0);
        printf("%d\n",ans);
    }
    return 0;
}