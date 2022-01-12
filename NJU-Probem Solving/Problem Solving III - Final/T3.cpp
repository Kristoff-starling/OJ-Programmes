#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define Pair pair<int,int>
#define mp make_pair
#define x first
#define y second
#define LL long long
using namespace std;

const int MAXN=8e5;
const LL LINF=1e18;

LL dist[MAXN+48][2][2];

int t1,t2,n,m;
vector<Pair> v[MAXN+48];

typedef pair<LL, pair<int,Pair> > info;
priority_queue<info> q;

void dijkstra()
{
    rep(i,1,n) rep(sta1,0,t1) rep(sta2,0,t2) dist[i][sta1][sta2]=LINF;
    dist[1][0][0]=0;
    q.push(mp(0,mp(1,mp(0,0))));
    while (!q.empty())
    {
        info cur=q.top();q.pop();
        if (-cur.x>dist[cur.y.x][cur.y.y.x][cur.y.y.y]) continue;
        for (auto item : v[cur.y.x])
        {
            int to=item.x;
            if (dist[to][cur.y.y.x][cur.y.y.y]>-cur.x+item.y)
            {
                dist[to][cur.y.y.x][cur.y.y.y]=-cur.x+item.y;
                q.push(mp(cur.x-item.y,mp(to,mp(cur.y.y.x,cur.y.y.y))));
            }
            if (cur.y.y.x<t1 && dist[to][cur.y.y.x+1][cur.y.y.y]>-cur.x)
            {
                dist[to][cur.y.y.x+1][cur.y.y.y]=-cur.x;
                q.push(mp(cur.x,mp(to,mp(cur.y.y.x+1,cur.y.y.y))));
            }
            if (cur.y.y.y<t2 && dist[to][cur.y.y.x][cur.y.y.y+1]>-cur.x+3ll*item.y)
            {
                dist[to][cur.y.y.x][cur.y.y.y+1]=-cur.x+3ll*item.y;
                q.push(mp(cur.x-3ll*item.y,mp(to,mp(cur.y.y.x,cur.y.y.y+1))));
            }
            if (cur.y.y.x<t1 && cur.y.y.y<t2 && dist[to][cur.y.y.x+1][cur.y.y.y+1]>-cur.x+2ll*item.y)
            {
                dist[to][cur.y.y.x+1][cur.y.y.y+1]=-cur.x+2ll*item.y;
                q.push(mp(cur.x-2ll*item.y,mp(to,mp(cur.y.y.x+1,cur.y.y.y+1))));
            }
        }
    }
}

int main ()
{
    scanf("%d%d",&t1,&t2);
    t1=(t1==1?1:0);t2=(t2==2?1:0);
    scanf("%d%d",&n,&m);
    int x,y,c;
    rep(i,1,m)
    {
        scanf("%d%d%d",&x,&y,&c);
        v[x].pb(mp(y,c));v[y].pb(mp(x,c));
    }
    dijkstra();
    rep(i,2,n) printf("%lld ",dist[i][t1][t2]);
    puts("");return 0;
}