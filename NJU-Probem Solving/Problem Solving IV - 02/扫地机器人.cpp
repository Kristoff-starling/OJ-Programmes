#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
#define REP(i,a,b) for (int i=(a);i>=(b);--i)
#define Pair pair<int,int>
#define pb push_back
#define mp make_pair
using namespace std;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int n,m;
int rc,lr,ud;

vector<Pair> path;

void snake(int x,int l,int r,int dir)
{
    int X=x,y=(dir==3?r:l);
    rep(i,l,r)
    {
        rep(j,1,X-1)
        {
            path.pb(mp(x,y));
            if (~i&1) x+=dx[2],y+=dy[2]; else x+=dx[0],y+=dy[0];
        }
        path.pb(mp(x,y));
        if (i!=r) x+=dx[dir],y+=dy[dir]; else x+=dx[2],y+=dy[2];
    }
    REP(i,r,l)
    {
        rep(j,1,n-X-1)
        {
            path.pb(mp(x,y));
            if (~i&1) x+=dx[2],y+=dy[2]; else x+=dx[0],y+=dy[0];
        }
        path.pb(mp(x,y));
        x+=dx[4-dir];y+=dy[4-dir];
    }
}

void decode(int x,int y)
{
    if (ud==1) x=n+1-x;
    if (lr==1) y=m+1-y;
    if (rc==1) swap(x,y);
    printf("%d %d\n",x-1,y-1);
}

int main()
{
    int x,y;
    rc=lr=ud=0;scanf("%d%d%d%d",&n,&m,&x,&y);x++;y++;
    if (m&1) swap(n,m),swap(x,y),rc=1;
    if (y&1) y=m+1-y,lr=1;
    if (x==n) x=1,ud=1;
    snake(x,1,y,3);snake(x+1,y+1,m,1);
    for (auto item : path) decode(item.first,item.second);
    return 0;
}