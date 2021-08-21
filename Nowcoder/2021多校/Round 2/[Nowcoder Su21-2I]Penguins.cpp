#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;++i)
#define REP(i,a,b) for (int i=a;i>=b;--i)
#define Pair pair<int,int>
#define pb push_back
#define mp make_pair
using namespace std;

char map1[48][48],map2[48][48];

int dx1[]={1,0,0,-1};
int dy1[]={0,-1,1,0};
int dx2[]={1,0,0,-1};
int dy2[]={0,1,-1,0};
string ch[]={"D","L","R","U"};

int q[1000048],head,tail;
bool visited[21][21][21][21];

void push(int x,int y,int z,int w) {q[++tail]=x;q[++tail]=y;q[++tail]=z;q[++tail]=w;}

struct node
{
    int x1,y1,x2,y2;
    node () {}
    node (int _x1,int _y1,int _x2,int _y2) {x1=_x1;y1=_y1;x2=_x2;y2=_y2;}
}from[21][21][21][21];

int fromdir[21][21][21][21];

string construct_path(int x1,int y1,int x2,int y2)
{
    if (x1==20 && y1==20 && x2==20 && y2==1) return "";
    return construct_path(from[x1][y1][x2][y2].x1,from[x1][y1][x2][y2].y1,from[x1][y1][x2][y2].x2,from[x1][y1][x2][y2].y2)+ch[fromdir[x1][y1][x2][y2]];
}

int main ()
{
    rep(i,1,20) scanf("%s%s",map1[i]+1,map2[i]+1);
    head=1;tail=0;push(20,20,20,1);visited[20][20][20][1]=true;bool f=false;
    while (head<=tail)
    {
        int x1=q[head++],y1=q[head++],x2=q[head++],y2=q[head++];
        rep(dir,0,3)
        {
            int tox1=x1+dx1[dir],toy1=y1+dy1[dir];
            if (tox1<1 || tox1>20 || toy1<1 || toy1>20 || map1[tox1][toy1]=='#') tox1=x1,toy1=y1;
            int tox2=x2+dx2[dir],toy2=y2+dy2[dir];
            if (tox2<1 || tox2>20 || toy2<1 || toy2>20 || map2[tox2][toy2]=='#') tox2=x2,toy2=y2;
            if (!visited[tox1][toy1][tox2][toy2])
            {
                visited[tox1][toy1][tox2][toy2]=true;
                from[tox1][toy1][tox2][toy2]=node(x1,y1,x2,y2);fromdir[tox1][toy1][tox2][toy2]=dir;
                push(tox1,toy1,tox2,toy2);
                if (tox1==1 && toy1==20 && tox2==1 && toy2==1) {f=true;break;}
            }
        }
        if (f) break;
    }
    string path=construct_path(1,20,1,1);
    printf("%d\n",int(path.size()));
    cout<<path<<endl;
    int x1=20,y1=20,x2=20,y2=1;
    map1[x1][y1]=map2[x2][y2]='A';
    rep(i,0,int(path.size())-1)
    {
        int dir;
        if (path[i]=='D') dir=0;
        if (path[i]=='L') dir=1;
        if (path[i]=='R') dir=2;
        if (path[i]=='U') dir=3;
        int tox1=x1+dx1[dir],toy1=y1+dy1[dir];
        if (tox1<1 || tox1>20 || toy1<1 || toy1>20 || map1[tox1][toy1]=='#') tox1=x1,toy1=y1;
        int tox2=x2+dx2[dir],toy2=y2+dy2[dir];
        if (tox2<1 || tox2>20 || toy2<1 || toy2>20 || map2[tox2][toy2]=='#') tox2=x2,toy2=y2;
        x1=tox1;y1=toy1;x2=tox2;y2=toy2;
        map1[x1][y1]=map2[x2][y2]='A';
    }
    rep(i,1,20) printf("%s %s\n",map1[i]+1,map2[i]+1);
    return 0;
}