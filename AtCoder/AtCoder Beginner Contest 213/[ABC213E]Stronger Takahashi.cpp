#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define x first
#define y second
#define pb push_back
#define mp make_pair
using namespace std;

int n,m;
char Map[1000][1000];

vector<Pair> v[300048];

int calc(int x,int y) {return (x-1)*m+y;}

int dist[300048];
priority_queue<Pair> q;

void dijkstra()
{
    for (int i=1;i<=n*m;i++) dist[i]=1e8;
    dist[1]=0;q.push(mp(0,1));
    while (!q.empty())
    {
        int x=q.top().y,dd=-q.top().x;q.pop();
        if (dd>dist[x]) continue;
        for (int i=0;i<int(v[x].size());i++)
        {
            int y=v[x][i].x;
            if (dist[y]>dist[x]+v[x][i].y)
            {
                dist[y]=dist[x]+v[x][i].y;
                q.push(mp(-dist[y],y));
            }
        }
    }
}

int main ()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%s",Map[i]+1);
    rep(i,1,n) rep(j,1,m-1) if (Map[i][j+1]=='.') v[calc(i,j)].pb(mp(calc(i,j+1),0));
    rep(i,1,n) rep(j,2,m) if (Map[i][j-1]=='.') v[calc(i,j)].pb(mp(calc(i,j-1),0));
    rep(i,1,n-1) rep(j,1,m) if (Map[i+1][j]=='.') v[calc(i,j)].pb(mp(calc(i+1,j),0));
    rep(i,2,n) rep(j,1,m) if (Map[i-1][j]=='.') v[calc(i,j)].pb(mp(calc(i-1,j),0));
    rep(i,1,n) rep(j,1,m) rep(dx,-2,2) rep(dy,-2,2)
    {
        if (dx==0 && dy==0) continue;
        if (abs(dx)==2 && abs(dy)==2) continue;
        int xx=i+dx,yy=j+dy;
        if (1<=xx && xx<=n && 1<=yy && yy<=m && Map[xx][yy]=='#') v[calc(i,j)].pb(mp(calc(xx,yy),1));
    }
    dijkstra();
    printf("%d\n",dist[calc(n,m)]);
    return 0;
}