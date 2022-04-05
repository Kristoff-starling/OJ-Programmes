#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> T myabs(T x) {return x>=0?x:-x;}
template<typename T> T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
int add(int x) {if (x>=MOD) x-=MOD;return x;}
int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
int sub(int x,int MO) {if (x<0) x+=MO;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Add(int &x,int y,int MO) {x=add(x+y,MO);}
void Sub(int &x,int y) {x=sub(x-y);}
void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=5e5;

int n,k;
int w[MAXN+48];

int head[MAXN+48],to[MAXN+48],Nxt[MAXN+48],tot;
void addedge(int s,int t) {to[++tot]=t;Nxt[tot]=head[s];head[s]=tot;}
int st[MAXN+48][2],ed[MAXN+48][2];

int sz[MAXN+48],son[MAXN+48],depth[MAXN+48],fa[MAXN+48],top[MAXN+48],minid[MAXN+48];
int seq[MAXN+48],pos[MAXN+48],ind;

void dfs1(int cur)
{
    sz[cur]=1;son[cur]=0;
    for (register int i=head[cur];i;i=Nxt[i])
    {
        int y=to[i];
        depth[y]=depth[cur]+1;fa[y]=cur;dfs1(y);
        sz[cur]+=sz[y];
        if ((!son[cur]) || sz[son[cur]]<sz[y]) son[cur]=y;
    }
}

void dfs2(int cur,int tp)
{
    top[cur]=tp;minid[cur]=cur;
    if (tp!=cur && w[minid[fa[cur]]]<w[cur]) minid[cur]=minid[fa[cur]];
    seq[++ind]=cur;pos[cur]=ind;
    if (son[cur]) dfs2(son[cur],tp);
    for (register int i=head[cur];i;i=Nxt[i])
    {
        int y=to[i];
        if (y!=son[cur]) dfs2(y,y);
    }
}

namespace SegmentTree
{
    int minn[MAXN*2+100000],sz;
    void update(int &x,int y) {if (w[y]<w[x]) x=y;}
    void build()
    {
        for (sz=1;sz<=ind+1;sz<<=1);
        for (register int i=sz+1;i<=sz+ind;i++) minn[i]=seq[i-sz];
        for (register int i=sz-1;i>=1;i--) minn[i]=minn[i<<1],update(minn[i],minn[i<<1|1]);
    }
    int query(int s,int t)
    {
        if (s==t) return minn[sz+s];
        int res=minn[sz+s];
        for (s+=sz-1,t+=sz+1;s^t^1;s>>=1,t>>=1)
        {
            if (~s&1) update(res,minn[s^1]);
            if (t&1) update(res,minn[t^1]);
        }
        return res;
    }
}

int query_min(int u,int v)
{
    int minidres=0;
    while (top[u]!=top[v])
    {
        if (depth[top[u]]<depth[top[v]]) swap(u,v);
        if (!minidres || w[minid[u]]<w[minidres]) minidres=minid[u];
        u=fa[top[u]];
    }
    if (depth[u]>depth[v]) swap(u,v);
    int res=SegmentTree::query(pos[u],pos[v]);
    if (!minidres || w[res]<w[minidres]) minidres=res;
    return minidres;
}

int query_lca(int u,int v)
{
    while (top[u]!=top[v])
    {
        if (depth[top[u]]<depth[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    if (depth[u]>depth[v]) swap(u,v);
    return u;
}

int jump(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    int tmp;while (top[u]!=top[v]) tmp=top[u],u=fa[top[u]];
    if (u==v) return tmp; else return seq[pos[u]-(depth[u]-depth[v]-1)];
}

struct Route
{
    LL info;int val;
    Route () {}
    Route (LL _info,int _val) {info=_info;val=_val;}
    bool operator < (const Route &other) const {return val<other.val;}
};

namespace Heap
{
    Route h[MAXN*4+48];int sz;
    bool empty() {return !sz;}
    void up()
    {
        int x=sz,y=sz>>1;
        while (y)
        {
            if (h[x].val<h[y].val) swap(h[x],h[y]),x=y,y>>=1;
            else break;
        }
    }
    void down()
    {
        int x=1,y=x<<1;
        while (y<=sz)
        {
            if (y<sz && h[y+1].val<h[y].val) y++;
            if (h[y].val<h[x].val) swap(h[x],h[y]),x=y,y<<=1; else break;
        }
    }
    void push(Route x) {h[++sz]=x;up();}
    Route top() {return h[1];}
    void pop() {swap(h[1],h[sz--]);down();}
}

LL encode(int x,int y,int z)
{
    return 1ll*x*(MAXN+48)*(MAXN+48)+1ll*y*(MAXN+48)+z;
}

void decode(LL info,int &u,int &v,int &pos)
{
    pos=info%(MAXN+48);
    v=info/(MAXN+48)%(MAXN+48);
    u=info/(1ll*(MAXN+48)*(MAXN+48))%(MAXN+48);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&k);int x,a,b,c;
    for (register int i=1;i<=n;i++) scanf("%d",w+i);
    for (register int i=2;i<=n;i++) scanf("%d",&x),addedge(x,i);
    fa[1]=0;depth[1]=1;dfs1(1);dfs2(1,1);
    SegmentTree::build();
    int tmp,tmp1,tmp2;
    for (register int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        if (depth[a]>depth[b]) swap(a,b);
        if (depth[a]>depth[c]) swap(a,c);
        if (depth[b]>depth[c]) swap(b,c);
        tmp=query_lca(a,b);
        if (tmp==a)
        {
            tmp2=query_lca(b,c);
            if (tmp2==b) st[i][0]=a,ed[i][0]=c,st[i][1]=-1,ed[i][1]=-1;
            else if (depth[tmp2]>depth[a])
                st[i][0]=b,ed[i][0]=c,st[i][1]=fa[tmp2],ed[i][1]=a;
            else st[i][0]=b,ed[i][0]=c,st[i][1]=-1,ed[i][1]=-1;
        }
        else
        {
            if (query_lca(c,tmp)!=tmp)
                st[i][0]=a,ed[i][0]=b,st[i][1]=c,ed[i][1]=fa[tmp];
            else
            {
                tmp1=query_lca(a,c);tmp2=query_lca(b,c);
                if (tmp1==tmp && tmp2==tmp)
                    st[i][0]=a,ed[i][0]=b,st[i][1]=c,ed[i][1]=jump(c,tmp);
                else
                {
                    if (tmp1==a) st[i][0]=b,ed[i][0]=c,st[i][1]=-1,ed[i][1]=-1;
                    else if (tmp2==b) st[i][0]=a,ed[i][0]=c,st[i][1]=-1,ed[i][1]=-1;
                    else if (tmp2==tmp)
                        st[i][0]=a,ed[i][0]=c,st[i][1]=b,ed[i][1]=fa[tmp1];
                    else
                        st[i][0]=b,ed[i][0]=c,st[i][1]=a,ed[i][1]=fa[tmp2];
                }
            }
        }
    }
    for (register int i=1;i<=n;i++) Heap::push(Route(encode(MAXN+1,MAXN+1,i),w[i]));
    int uu,vv,pp,LCA,tu,tv,u,v,res;Route cur;
    while (k--)
    {
        cur=Heap::top();Heap::pop();
        printf("%d\n",cur.val);
        decode(cur.info,uu,vv,pp);
        //explore to the next
        for (register int i=0;i<=1;i++)
        {
            u=st[pp][i];v=ed[pp][i];
            if (u==-1) continue;
            res=query_min(u,v);Heap::push(Route(encode(u,v,res),cur.val+w[res]));
        }
        //change the last one
        if (uu!=MAXN+1)
        {
            LCA=query_lca(uu,vv);
            if (LCA==pp) tu=(uu!=pp?jump(uu,LCA):-1),tv=(vv!=pp?jump(vv,LCA):-1);
            else
            {
                if (query_lca(pp,uu)==LCA) swap(uu,vv);
                tu=(pp!=uu?jump(uu,pp):-1);tv=fa[pp];
            }
            if (tu!=-1) res=query_min(uu,tu),Heap::push(Route(encode(uu,tu,res),cur.val-w[pp]+w[res]));
            if (tv!=-1) res=query_min(vv,tv),Heap::push(Route(encode(vv,tv,res),cur.val-w[pp]+w[res]));
        }
    }
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}