#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=2e5;

int n;
vector<int> v[MAXN+48];

void dfs(int cur,int father)
{
    printf("%d ",cur);
    for (auto y : v[cur]) if (y!=father) {dfs(y,cur);printf("%d ",cur);}
}

int main ()
{
    int x,y;scanf("%d",&n);rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    rep(i,1,n) sort(v[i].begin(),v[i].end());
    dfs(1,0);return 0;
}