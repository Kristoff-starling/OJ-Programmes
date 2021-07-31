#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int> 
#define x first
#define y second
#define mp make_pair
#define pb push_back
using namespace std;

const int MAXN=1000;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int myabs(int x) {return x>=0?x:-x;}

struct sta
{
    int x,y,d;
    sta () {}
    sta (int _x,int _y,int _d) {x=_x;y=_y;d=_d;}
};

int n,m,Map[MAXN+48][MAXN+48];sta from[MAXN+48][MAXN+48][4];
int type[100][100];

int q[15000048],head,tail;

void Push(int x,int y,int dir) {q[++tail]=x;q[++tail]=y;q[++tail]=dir;}

vector<sta> path;int ang[MAXN+48][MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    type[2][3]=0;type[1][0]=0;
    type[2][1]=1;type[3][0]=1;
    type[0][1]=2;type[3][2]=2;
    type[1][2]=3;type[0][3]=3;
    while (ca--)
    {
        scanf("%d%d",&n,&m);rep(i,1,n) rep(j,1,m) scanf("%d",&Map[i][j]);
        rep(i,1,n) rep(j,1,m) rep(dir,0,3) from[i][j][dir]=sta(0,0,0);
        head=1;tail=0;Push(0,1,2);
        while (head<=tail)
        {
            int x=q[head++],y=q[head++],dir=q[head++];
            if (x==n && y==m && dir==2) break;
            int nx=x+dx[dir],ny=y+dy[dir];
            if (!(1<=nx && nx<=n && 1<=ny && ny<=m)) continue;
            if (Map[nx][ny]<=3)
            {
                vector<int> can;can.clear();
                if (dir==1 || dir==3) can.pb(0),can.pb(2); else can.pb(1),can.pb(3); 
                for (auto nxdir : can) if (!from[nx][ny][nxdir].y) Push(nx,ny,nxdir),from[nx][ny][nxdir]=sta(x,y,dir);
            }
            else
            {
                int nxdir=dir;
                if (!from[nx][ny][nxdir].y) Push(nx,ny,nxdir),from[nx][ny][nxdir]=sta(x,y,dir);
            }
        }
        if (from[n][m][2].y)
        {
            puts("YES");path.clear();
            int x=n,y=m,dir=2;
            while (!(x==0 && y==1))
            {
                path.pb(sta(x,y,dir));
                sta last=from[x][y][dir];
                x=last.x;y=last.y;dir=last.d;
            }
            path.pb(sta(0,1,2));
            reverse(path.begin(),path.end());
            rep(i,1,n) rep(j,1,m) ang[i][j]=0;
            printf("%d\n",(int(path.size())-1)*2);x=0;y=1;dir=2;
            for (int i=0;i<int(path.size())-1;i++)
            {
                int nx=path[i+1].x,ny=path[i+1].y,ndir=path[i+1].d;
                if (dir==ndir)
                {
                    int cur=(Map[nx][ny]&1)^(ang[nx][ny]%2);
                    if (((dir==2 || dir==0) && !cur) || ((dir==3 || dir==1) && cur))
                    {
                        printf("1 90 %d %d\n",nx,ny);
                        ang[nx][ny]++;
                    }
                    else printf("1 0 %d %d\n",nx,ny);
                }
                else
                {
                    int cur=(Map[nx][ny]+ang[nx][ny])%4,need=type[dir][ndir];
                    int rot=need-cur;if (rot<0) rot+=4;
                    printf("1 %d %d %d\n",rot*90,nx,ny);ang[nx][ny]+=rot;
                }
                x=nx;y=ny;dir=ndir;
                printf("0 %d %d\n",x,y);
            }
        }
        else puts("NO");
    }
    return 0;
}