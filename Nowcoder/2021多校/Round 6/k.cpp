#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
#define LL long long
#define pLL pair<LL,LL>
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=5e5;
const int MOD=998244353;
const LL LINF=1e18;

int n,q,seed,a[MAXN+48];
vector<int> v[MAXN+48];

template<typename T> void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}

struct Rand{
    unsigned int n,seed;
    Rand(unsigned int n,unsigned int seed)
    :n(n),seed(seed){}
    int get(long long lastans){
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
        return (seed^lastans)%n+1;
    }
};

int depth[MAXN+48],anc[MAXN+48][21];
LL maxn[MAXN+48][21][4];
int Log[MAXN+48];

void dfs(int cur,int father)
{
    depth[cur]=depth[father]+1;
    anc[cur][0]=father;rep(i,1,18) anc[cur][i]=anc[anc[cur][i-1]][i-1];
    maxn[cur][0][3]=a[cur];maxn[cur][0][0]=0;
    rep(i,1,18)
    {
        int nxt=anc[cur][i-1];
        rep(sta1,0,3) rep(sta2,0,3) if (maxn[cur][i-1][sta1]>-LINF && maxn[nxt][i-1][sta2]>-LINF)
        {
            int j=0;
            if ((sta1&2)) j|=2;
            if ((sta2&1)) j|=1;
            if ((sta1&1) && (sta2&2)) continue;
            check_max(maxn[cur][i][j],maxn[cur][i-1][sta1]+maxn[nxt][i-1][sta2]);
        }
    }
    for (auto y : v[cur]) if (y!=father) dfs(y,cur);
}

pLL query_lca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    REP(i,18,0) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return mp(u,u);
    REP(i,18,0) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return mp(anc[u][0],v);
}

pLL calc(int u,int v)
{
    LL res[2];res[0]=0;res[1]=-LINF;
    LL tores[2];int d=depth[u]-depth[v]+1;
    REP(i,Log[d]+1,0) if (depth[anc[u][i]]>=depth[v])
    {
        tores[0]=tores[1]=-LINF;
        check_max(tores[0],res[0]+maxn[u][i][0]);
        check_max(tores[0],res[1]+maxn[u][i][0]);
        check_max(tores[1],res[0]+maxn[u][i][1]);
        check_max(tores[1],res[1]+maxn[u][i][1]);
        check_max(tores[0],res[0]+maxn[u][i][2]);
        check_max(tores[1],res[0]+maxn[u][i][3]);
        res[0]=tores[0];res[1]=tores[1];
        u=anc[u][i];
    }
    tores[0]=tores[1]=-LINF;
    check_max(tores[0],res[0]);check_max(tores[0],res[1]);
    check_max(tores[1],res[0]+a[v]);
    return mp(tores[0],tores[1]);
}

long long query(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    pLL rr=query_lca(u,v);
    int LCA=rr.x;
    if (LCA==v)
    {
        pLL res=calc(u,v);
        return max(res.x,res.y);
    }
    else
    {
        int p=rr.y;
        pLL res1=calc(u,LCA);
        pLL res2=calc(v,p);
        LL res=res1.x+res2.x;
        check_max(res,res1.x+res2.y);
        check_max(res,res1.y+res2.x);
        return res;
    }
}

int main ()
{
    // double T=clock();
    // freopen ("a.in","r",stdin);
    scanf("%d%d%d",&n,&q,&seed);rep(i,1,n) scanf("%d",a+i);int x;
    rep(i,2,n) scanf("%d",&x),v[i].pb(x),v[x].pb(i);
    rep(i,1,n) rep(j,0,18) rep(k,0,3) maxn[i][j][k]=-1e18;
    int rt;
    rep(i,1,n) if (int(v[i].size())==1) rt=i;
    double t=clock();
    depth[0]=0;dfs(rt,0);
    cerr<<(clock()-t)/CLOCKS_PER_SEC<<endl;
    Log[1]=0;rep(i,1,n) Log[i]=Log[i>>1]+1;
    long long lastans=0,ans=0;
    Rand rand(n,seed);
    for(int i=0;i<q;i++){
        int u=rand.get(lastans);
        int v=rand.get(lastans);
        int x=rand.get(lastans);
        lastans=query(u,v);//calculate the answer
        ans=(ans+lastans%MOD*x)%MOD;
        // if (i%100000==0) cerr<<i<<endl;
    }
    printf("%lld\n",ans);
    // cerr<<(clock()-T)/CLOCKS_PER_SEC<<endl;
    return 0;
}