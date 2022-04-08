#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define mp make_pair
#define pb push_back
#define Pair pair<int,int>
#define x first
#define y second
using namespace std;

int dx[]={1,0,-1,-1,0,1},dy[]={1,1,0,-1,-1,0};
int Dx[]={1,2,1,-1,-2,-1},Dy[]={2,1,-1,-2,-1,1};
int _x[]={2,0,-2,-2,0,2},_y[]={2,2,0,-2,-2,0};

map<Pair,int> layer;
set<Pair> stone;
queue<int> q;
vector<Pair> pos;

bool onbound(int x,int y)
{
    return layer.find(mp(x,y))!=layer.end() && layer[mp(x,y)]==9;
}

bool blocked(int x,int y)
{
    assert(layer.find(mp(x,y))!=layer.end());
    return stone.find(mp(x,y))!=stone.end();
}

void putstone(int x,int y)
{
    printf("%d %d\n",x,y);
    fflush(stdout);
    stone.insert(mp(x,y));
}

void initstone()
{
    int tx,ty;
    scanf("%d%d",&tx,&ty);putstone(-1,8);
	scanf("%d%d",&tx,&ty);putstone(-9,-1);
	scanf("%d%d",&tx,&ty);putstone(-8,-9);
	scanf("%d%d",&tx,&ty);putstone(1,-8);
	scanf("%d%d",&tx,&ty);putstone(9,1);
	scanf("%d%d",&tx,&ty);putstone(8,9);
}

void bfs()
{
    layer.clear();pos.clear();layer[mp(0,0)]=0;
    q.push(0);q.push(0);int x,y,xx,yy,step;
    while (!q.empty())
    {
        x=q.front();q.pop();y=q.front();q.pop();
        pos.pb(mp(x,y));
        step=layer[mp(x,y)];
        if (step==9) continue;
        rep(dir,0,5)
        {
            xx=x+dx[dir];yy=y+dy[dir];
            if (layer.find(mp(xx,yy))==layer.end())
            {
                layer[mp(xx,yy)]=step+1;
                q.push(xx);q.push(yy);
            }
        }
    }
}

bool trapped(int x,int y)
{
    int xx,yy;
    rep(dir,0,5)
    {
        xx=x+dx[dir];yy=y+dy[dir]; 
        if (!blocked(xx,yy)) return false;
    }
    return true;
}

int main ()
{
    bfs();int cx,cy,xx,yy,step;
    initstone();
    for (;;)
    {
        scanf("%d%d",&cx,&cy);step=layer[mp(cx,cy)];
        assert(0<=step && step<=8);
        bool stoned=false;
        if (step>=7)
        {
            int *ddx,*ddy;
            if (step==7) ddx=Dx,ddy=Dy; else ddx=dx,ddy=dy;
            rep(dir,0,5)
            {
                xx=cx+ddx[dir];yy=cy+ddy[dir];
                if (onbound(xx,yy) && !blocked(xx,yy))
                {
                    putstone(xx,yy);
                    stoned=true;break;
                }
            }
        }
        if (step==8 && !stoned)
        {
            rep(dir,0,5)
            {
                xx=cx+_x[dir];yy=cy+_y[dir];
                if (onbound(xx,yy) && !blocked(xx,yy))
                {
                    putstone(xx,yy);
                    stoned=true;break;
                }
            }
        }
        if (!stoned)
        {
            for (auto item : pos)
                if (stone.find(item)==stone.end() && item!=mp(cx,cy))
                {
                    putstone(item.x,item.y);
                    break;
                }
        }
        if (trapped(cx,cy)) break;
    }
    return 0;
}