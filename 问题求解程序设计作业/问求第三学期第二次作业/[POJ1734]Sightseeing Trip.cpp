#include <cstdio>
#include <vector>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e8;

template<typename T> void check_min(T &x,T y) {x=(x<y?x:y);}

int n,m;
int dist[201][201],ga[201][201],mid[201][201];
vector<int> path;

void construct_path(int x,int y)
{
    if (mid[x][y]==0) {path.push_back(x);return;}
    construct_path(x,mid[x][y]);construct_path(mid[x][y],y);
}

int main ()
{
	scanf("%d%d",&n,&m);int x,y,c;
    rep(i,1,n) rep(j,1,n) if (i==j) dist[i][j]=0; else dist[i][j]=INF;
    rep(i,1,m) scanf("%d%d%d",&x,&y,&c),check_min(dist[x][y],c),check_min(dist[y][x],c);
    rep(i,1,n) rep(j,1,n) ga[i][j]=dist[i][j],mid[i][j]=0;
    int ans=INF;
    rep(k,1,n)
    {
        rep(i,1,k-2) rep(j,i+1,k-1) if (ga[k][i]+dist[i][j]+ga[j][k]<ans)
        {
            ans=ga[k][i]+dist[i][j]+ga[j][k];
            path.clear();path.push_back(k);
            construct_path(i,j);path.push_back(j);
        }
        rep(i,1,n) rep(j,1,n) if (i!=k && j!=k && i!=j && dist[i][j]>dist[i][k]+dist[k][j])
        {
            dist[i][j]=dist[i][k]+dist[k][j];
            mid[i][j]=k;
        }
    }
    if (ans>=INF) puts("No solution."); else
    {
        for (int i=0;i<int(path.size());i++) printf("%d ",path[i]);
        puts("");
    }
	return 0;
}
