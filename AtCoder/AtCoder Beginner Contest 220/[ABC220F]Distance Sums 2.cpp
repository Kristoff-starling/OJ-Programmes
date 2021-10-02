#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=2e5;

int n;
vector<int> v[MAXN+48];
int sz[MAXN+48];LL ans[MAXN+48];

void dfs(int cur,int father)
{
    sz[cur]=1;
    for (auto y : v[cur]) if (y!=father) dfs(y,cur),sz[cur]+=sz[y];
}

void dfs2(int cur,int father,LL tmp)
{
    ans[cur]=tmp;
    for (auto y : v[cur]) if (y!=father) dfs2(y,cur,tmp-sz[y]+n-sz[y]);
}

int main ()
{
    scanf("%d",&n);int x,y;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
    dfs(1,0);LL tmp=0;rep(i,2,n) tmp+=sz[i];dfs2(1,0,tmp);
    rep(i,1,n) printf("%lld\n",ans[i]);
    return 0;
}