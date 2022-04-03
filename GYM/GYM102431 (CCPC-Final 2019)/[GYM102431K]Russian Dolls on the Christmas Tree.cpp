#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define pb push_back
#define mp make_pair
#define Pair pair<int,int>
#define x first
#define y second
using namespace std;

const int MAXN=2e5;

int n;
vector<int> v[MAXN+48],vv[MAXN+48];
set<Pair> s[MAXN+48];int ind[MAXN+48];
int sz[MAXN+48];
int ans[MAXN+48];

void init()
{
    rep(i,1,n) v[i].clear(),vv[i].clear(),s[i].clear();
    rep(i,1,n) ind[i]=i,sz[i]=0,ans[i]=0;
}

bool cmp_sz(int x,int y) {return sz[x]>sz[y];}

/*
void print(int id)
{
    puts("-------------------------");
    for (set<Pair>::iterator iter=s[id].begin();iter!=s[id].end();iter++)
        printf("%d %d\n", iter->x,iter->y);
    puts("-------------------------");
}
*/

void Insert(int id,Pair item)
{
    set<Pair>::iterator pre,cur=s[id].lower_bound(item);
    int L,R;
    if (cur!=s[id].end() && item.y+1==cur->x)
    {
        L=item.x;R=cur->y;pre=cur;
        if (cur!=s[id].begin() && (--pre)->y+1==item.x)
        {
            L=pre->x;
            s[id].erase(pre);s[id].erase(cur);
            s[id].insert(mp(L,R));
        }
        else
        {
            s[id].erase(cur);
            s[id].insert(mp(L,R));
        }
    }
    else
    {
        L=item.x;R=item.y;
        if (cur!=s[id].begin() && (--cur)->y+1==item.x)
        {
            L=cur->x;
            s[id].erase(cur);s[id].insert(mp(L,R));
        }
        else s[id].insert(mp(L,R));
    }
}

void dfs(int cur,int father)
{
    sz[cur]=1;
    for (auto y : v[cur])
        if (y!=father) vv[cur].pb(y),dfs(y,cur),sz[cur]+=sz[y];
}

void dfs2(int cur)
{
    if (sz[cur]==1) {s[ind[cur]].insert(mp(cur,cur));ans[cur]=1;return;}
    for (auto y : vv[cur]) dfs2(y);
    sort(vv[cur].begin(),vv[cur].end(),cmp_sz);
    ind[cur]=ind[vv[cur][0]];Insert(ind[cur],mp(cur,cur));
    for (int i=1;i<int(vv[cur].size());i++)
        for (set<Pair>::iterator iter=s[ind[vv[cur][i]]].begin();iter!=s[ind[vv[cur][i]]].end();iter++)
            Insert(ind[cur],*iter);
    ans[cur]=int(s[ind[cur]].size());
}

int main ()
{
    int ca,x,y;scanf("%d",&ca);
    rep(t,1,ca)
    {
        scanf("%d",&n);init();
        rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
        dfs(1,0);dfs2(1);
        printf("Case #%d: ",t);
        rep(i,1,n-1) printf("%d ",ans[i]);
        printf("%d\n",ans[n]);
    }
    return 0;
}