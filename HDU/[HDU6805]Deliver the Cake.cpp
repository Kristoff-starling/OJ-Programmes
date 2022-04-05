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
#define Pair pair<LL,LL>
#define LOWBIT(x) x & (-x)

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

const int MAXN=1e6;
const LL LINF=1e16;

int n,m,s,t,rest,S,T;
char sta[MAXN+48];

int tot;
vector<Pair> v[MAXN+48];
int lind[MAXN+48],rind[MAXN+48];

inline void Addedge(int x,int y,int c) {v[x].pb(mp(y,c));v[y].pb(mp(x,c));}

inline void addedge(int x,int y,int d)
{
    if (lind[x] && lind[y]) Addedge(lind[x],lind[y],d);
    if (lind[x] && rind[y]) Addedge(lind[x],rind[y],d+rest);
    if (rind[x] && lind[y]) Addedge(rind[x],lind[y],d+rest);
    if (rind[x] && rind[y]) Addedge(rind[x],rind[y],d);
}

LL dist[MAXN+48];
priority_queue<Pair> q;
inline void dijkstra()
{
    rep(i,1,tot) dist[i]=LINF;
    dist[S]=0;q.push(mp(0,S));
    while (!q.empty())
    {
        int x=q.top().y;LL dd=-q.top().x;q.pop();
        if (dd>dist[x]) continue;
        for (int i=0;i<int(v[x].size());i++)
        {
            int to=v[x][i].x;
            if (dist[to]>dist[x]+v[x][i].y)
            {
                dist[to]=dist[x]+v[x][i].y;
                q.push(mp(-dist[to],to));
            }
        }
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d%d%d",&n,&m,&s,&t,&rest);
        scanf("%s",sta+1);tot=n;
        rep(i,1,n)
            if (sta[i]=='L') lind[i]=i,rind[i]=0;
            else if (sta[i]=='R') lind[i]=0,rind[i]=i;
            else lind[i]=++tot,rind[i]=++tot;
        S=++tot;T=++tot;rep(i,1,tot) v[i].clear();
        int x,y,d;
        rep(i,1,m) scanf("%d%d%d",&x,&y,&d),addedge(x,y,d);
        if (lind[s]) Addedge(S,lind[s],0);
        if (rind[s]) Addedge(S,rind[s],0);
        if (lind[t]) Addedge(lind[t],T,0);
        if (rind[t]) Addedge(rind[t],T,0);
        dijkstra();printf("%lld\n",dist[T]);
    }
    return 0;
}