#include <bits/stdc++.h>
#define LL long long
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=1e5;

int n;
vector<Pair> v[MAXN+48];
LL depth[MAXN+48];

void dfs(int cur,int father)
{
    for (auto item : v[cur])
        if (item.x!=father) depth[item.x]=depth[cur]+item.y,dfs(item.x,cur);
}

int main ()
{
    scanf("%d",&n);int x,y,w;
    rep(i,1,n-1) scanf("%d%d%d",&x,&y,&w),v[x].pb(mp(y,w)),v[y].pb(mp(x,w));
    depth[1]=0;dfs(1,0);int rt=1;LL maxn=0;
    rep(i,1,n) if (depth[i]>maxn) maxn=depth[i],rt=i;
    depth[rt]=0;dfs(rt,0);maxn=0;
    rep(i,1,n) maxn=max(maxn,depth[i]);
    printf("%lld\n",maxn);
    return 0;
}