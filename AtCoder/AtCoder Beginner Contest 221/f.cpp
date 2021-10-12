#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=2e5;
const int MOD=998244353;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n;
vector<int> v[MAXN+48];

int depth[MAXN+48],fa[MAXN+48];
int maxdepth[MAXN+48],maxcnt[MAXN+48];

void dfs(int cur,int father)
{
    depth[cur]=depth[father]+1;fa[cur]=father;
    for (auto y : v[cur]) if (y!=father) dfs(y,cur);
}

void dfs2(int cur,int father)
{
    depth[cur]=depth[father]+1;maxdepth[cur]=depth[cur];maxcnt[cur]=1;
    for (auto y : v[cur]) if (y!=father)
    {
        dfs2(y,cur);
        if (maxdepth[y]>maxdepth[cur]) maxdepth[cur]=maxdepth[y],maxcnt[cur]=maxcnt[y];
        else if (maxdepth[y]==maxdepth[cur]) maxcnt[cur]+=maxcnt[y];
    }
}

vector<pair<int,int> > sz;

int main ()
{
    scanf("%d",&n);int x,y;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    if (n==2) {puts("1");return 0;}
    depth[0]=0;dfs(1,0);int rt,le,maxn=0;
    rep(i,1,n) if (depth[i]>maxn) maxn=depth[i],rt=i;
    dfs(rt,0);maxn=0;rep(i,1,n) if (depth[i]>maxn) maxn=depth[i],le=i;
    int step=(depth[le]-depth[rt])/2;while (step--) le=fa[le];rt=le;
    dfs2(rt,0);
    for (auto y : v[rt]) sz.pb(mp(maxdepth[y],maxcnt[y]));
    sort(sz.begin(),sz.end());reverse(sz.begin(),sz.end());int tot=int(sz.size());
    if (sz[0].x==sz[1].x)
    {
        int lim=1;while (lim!=tot-1 && sz[lim+1].x==sz[lim].x) lim++;
        int ans=1;
        rep(i,0,lim) ans=1ll*ans*(sz[i].y+1)%MOD;
        Sub(ans,1);
        rep(i,0,lim) Sub(ans,sz[i].y);
        printf("%d\n",ans);
    }
    else
    {
        int pt=1,cnt=sz[pt].y;
        while (pt!=tot-1 && sz[pt].x==sz[pt+1].x) pt++,cnt+=sz[pt].y;
        printf("%d\n",int(1ll*sz[0].y*cnt%MOD));
    }
    return 0;
}