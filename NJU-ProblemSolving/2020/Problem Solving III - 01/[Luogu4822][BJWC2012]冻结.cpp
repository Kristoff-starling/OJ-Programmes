#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define Pair pair<int,int>
#define x first
#define y second
using namespace std;

const int INF=1e9;

struct node
{
    int dist,cur,cnt;
    node () {}
    node (int _dist,int _cur,int _cnt) {dist=_dist;cur=_cur;cnt=_cnt;}
    bool operator < (const node &other) const {return dist>other.dist;}
};

int n,m,k;
priority_queue<node> q;
vector<Pair> v[100];
int dist[101][101];

int main ()
{
    scanf("%d%d%d",&n,&m,&k);int x,y,c;
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),v[x].pb(mp(y,c)),v[y].pb(mp(x,c));
    rep(i,1,n) rep(j,0,k) dist[i][j]=INF;
    q.push(node(0,1,0));dist[1][0]=0;
    while (!q.empty())
    {
        node minn=q.top();q.pop();
        if (minn.dist>dist[minn.cur][minn.cnt]) continue;
        for (auto item : v[minn.cur])
        {
            if (dist[item.x][minn.cnt]>minn.dist+item.y)
                dist[item.x][minn.cnt]=minn.dist+item.y,q.push(node(dist[item.x][minn.cnt],item.x,minn.cnt));
            if (minn.cnt<k && dist[item.x][minn.cnt+1]>minn.dist+item.y/2)
                dist[item.x][minn.cnt+1]=minn.dist+item.y/2,q.push(node(dist[item.x][minn.cnt+1],item.x,minn.cnt+1));
        }
    }
    int ans=INF;rep(i,0,k) ans=min(ans,dist[n][i]);
    printf("%d\n",ans);return 0;
}