#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define pb push_back
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define x first
#define y second
#define mp make_pair
using namespace std;

const int MAXN=2e5;
const LL LINF=2e16;

int n,m;
vector<Pair> v[MAXN+48];
priority_queue<pLL> q;
LL dist[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&m);int x,y,c;
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),v[x].pb(mp(y,c));
    rep(i,1,n) dist[i]=LINF;dist[1]=0;q.push(mp(0,1));
    while (!q.empty())
    {
        int cur=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd>dist[cur]) continue;
        for (auto item : v[cur]) if (dist[item.x]>dist[cur]+item.y) dist[item.x]=dist[cur]+item.y,q.push(mp(-dist[item.x],item.x));
    }
    rep(i,1,n) if (dist[i]>=LINF) printf("-1 "); else printf("%lld ",dist[i]);
    puts("");return 0;
}