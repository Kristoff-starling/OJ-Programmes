#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,m,k;
int cnt[2],cc[200][200];
bool edge[200][200][4];
bool visited[200][200];

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

bool three;int curcnt;
vector<int> v;

void dfs(int x,int y)
{
    curcnt++;if (cc[x][y]==3) three=true;
    visited[x][y]=true;
    rep(dir,0,3)
    {
        int xx=x+dx[dir],yy=y+dy[dir];
        if (1<=xx && xx<=n-1 && 1<=yy && yy<=m-1 && !visited[xx][yy] && !edge[x][y][dir]) dfs(xx,yy);
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d",&n,&m,&k);int x,y,op;
        cnt[0]=cnt[1]=0;int cur=0;
        rep(i,1,n-1) rep(j,1,m-1) cc[i][j]=0,visited[i][j]=false;
        rep(i,1,n-1) rep(j,1,m-1) rep(dir,0,3) edge[i][j][dir]=false;
        rep(i,1,k)
        {
            scanf("%d%d%d",&x,&y,&op);
            if (op==0)
            {
                bool f=false;
                if (x!=1) {cc[x-1][y]++;edge[x-1][y][2]=true;if (cc[x-1][y]==4) cnt[cur]++,f=true;}
                if (x!=n) {cc[x][y]++;edge[x][y][0]=true;if (cc[x][y]==4) cnt[cur]++,f=true;}
                if (!f) cur^=1;
            }
            else
            {
                bool f=false;
                if (y!=1) {cc[x][y-1]++;edge[x][y-1][1]=true;if (cc[x][y-1]==4) cnt[cur]++,f=true;}
                if (y!=m) {cc[x][y]++;edge[x][y][3]=true;if (cc[x][y]==4) cnt[cur]++,f=true;}
                if (!f) cur^=1;
            }
        }
        v.clear();
        rep(i,1,n-1) rep(j,1,m-1) if (!visited[i][j] && cc[i][j]!=4)
        {
            three=false;curcnt=0;dfs(i,j);
            if (three) cnt[cur]+=curcnt; else v.push_back(curcnt);
        }
        sort(v.begin(),v.end());
        for (int i=0;i<int(v.size());i++)
            if (i&1) cnt[cur]+=v[i]; else cnt[cur^1]+=v[i];
        if (cnt[0]>cnt[1])
            puts("Little Rabbit");
        else if (cnt[0]<cnt[1])
            puts("Little Horse");
        else puts("Tie");
    }
    return 0;
}