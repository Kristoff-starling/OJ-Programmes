#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define Pair pair<int,int>
#define LL long long
#define pLL pair<LL,LL>
#define x first
#define y second
using namespace std;

const int MAXN=5e4;
const LL LINF=2e16;

int n,m,b;
int f[MAXN+48];

vector<Pair> v[MAXN+48];
LL dist[MAXN+48];priority_queue<pLL> q;

bool dijkstra(int lim)
{
    rep(i,1,n) dist[i]=LINF;
    dist[1]=0;q.push(mp(0,1));
    while (!q.empty())
    {
        int cur=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd>dist[cur]) continue;
        for (auto item : v[cur]) if (f[item.x]<=lim && dist[cur]+item.y<dist[item.x])
            dist[item.x]=dist[cur]+item.y,q.push(mp(-dist[item.x],item.x));
    }
    return dist[n]<=(long long)(b);
}

int main ()
{
    scanf("%d%d%d",&n,&m,&b);int x,y,c,maxn=0;
    rep(i,1,n) scanf("%d",f+i),maxn=max(maxn,f[i]);
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),v[x].pb(mp(y,c)),v[y].pb(mp(x,c));
    int L=f[1],R=maxn,mid,ans=-1;
    while (L<=R)
    {
        mid=(L+R)>>1;
        if (dijkstra(mid)) ans=mid,R=mid-1; else L=mid+1;
    }
    if (ans==-1) puts("AFK"); else printf("%d\n",ans);
    return 0;
}