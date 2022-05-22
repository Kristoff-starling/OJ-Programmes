#include <bits/stdc++.h>
#define Pair pair<int,int>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

const int MAXN=500;
int n,m;

int a[MAXN+48][MAXN+48];
bool visited[MAXN+48][MAXN+48];

int col[2];
vector<Pair> List[2];
vector<Pair> L;

void dfs(int x,int y,int color)
{
    col[(x+y)&1]++;
    List[(x+y)&1].push_back(make_pair(x,y));
    visited[x][y]=true;
    rep(dir,0,3)
    {
        int xx=x+dx[dir],yy=y+dy[dir];
        if (1<=xx && xx<=n && 1<=yy && yy<=m && a[xx][yy]==color && !visited[xx][yy]) dfs(xx,yy,color);
    }
}

int main ()
{
    scanf("%d%d",&n,&m);rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
    int type=0,ans=0;
    rep(i,1,n) rep(j,1,m) if (!visited[i][j])
    {
        col[0]=col[1]=0;List[0].clear();List[1].clear();
        dfs(i,j,a[i][j]);
        if (col[0] && col[1]) type=1;
        int id = (col[0]<=col[1]?0:1);
        for (auto item : List[id]) L.push_back(item);
        ans+=min(col[0],col[1]);
    }
    printf("%d %d\n",type,ans);
    for (auto item : L) printf("%d %d 1\n",item.first, item.second);
    return 0;
}