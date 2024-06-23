#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e9;

int n,m,q,dist[201][201],t[201];

struct Query
{
    int x,y,t,id;
    void input(int _id) {scanf("%d%d%d",&x,&y,&t);++x;++y;id=_id;}
    bool operator < (const Query &other) const {return t<other.t;}
}Q[50001];

int ans[50001];

int main ()
{
    scanf("%d%d",&n,&m);int x,y,c;
    rep(i,1,n) rep(j,1,n) dist[i][j]=INF;
    rep(i,1,n) dist[i][i]=0;
    rep(i,1,n) scanf("%d",t+i);
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),++x,++y,dist[x][y]=min(dist[x][y],c),dist[y][x]=min(dist[y][x],c);
    scanf("%d",&q);rep(i,1,q) Q[i].input(i);
    sort(Q+1,Q+q+1);int pt=1;
    while (pt<=q && Q[pt].t<t[1]) ans[Q[pt].id]=-1,pt++;
    rep(k,1,n)
    {
        rep(i,1,n) rep(j,1,n) if (i!=j && i!=k && j!=k) dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
        while (pt<=q && (k==n || t[k+1]>Q[pt].t))
        {
            if (t[Q[pt].x]>Q[pt].t || t[Q[pt].y]>Q[pt].t) ans[Q[pt].id]=-1;
            else if (dist[Q[pt].x][Q[pt].y]>=INF) ans[Q[pt].id]=-1; else ans[Q[pt].id]=dist[Q[pt].x][Q[pt].y];
            pt++;
        }
    }
    rep(i,1,q) printf("%d\n",ans[i]);
    return 0;
}