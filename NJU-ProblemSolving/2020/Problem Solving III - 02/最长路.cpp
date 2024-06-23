#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=2e5;

int n,m;
vector<pair<int,int> > v[MAXN+48];
int dist[MAXN+48];

int solve(int cur)
{
    if (dist[cur]!=-1) return dist[cur];
    dist[cur]=0;
    for (auto item : v[cur]) dist[cur]=max(dist[cur],solve(item.x)+item.y);
    return dist[cur];
}

int main ()
{
    scanf("%d%d",&n,&m);int x,y,c;
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),v[x].pb(mp(y,c));
    rep(i,1,n) dist[i]=-1;
    int ans=0;rep(i,1,n) ans=max(ans,solve(i));
    printf("%d\n",ans);return 0;
}