#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,e;
int ga[200][200];

struct edge
{
    int x,y,c,type;
    void input()
    {
        scanf("%d%d%d",&x,&y,&c);
        if (c>0) type=-1; else type=1,c=-c;
    }
}edge[10048];

int bel[200];

int judgetype(int x,int y) {return edge[ga[x][y]].type;}
int judgevalue(int x,int y) {return edge[ga[x][y]].c;}

int main ()
{
    scanf("%d%d",&n,&e);
    rep(i,1,e)
    {
        edge[i].input();
        ga[edge[i].x][edge[i].y]=ga[edge[i].y][edge[i].x]=i;
    }
    rep(i,1,n)
    {
        int sum1=0,sum2=0;
        rep(j,1,i-1)
        {
            int t=judgetype(i,j),c=judgevalue(i,j);
            if (!t) continue;
            if (t==-1) {
                if (bel[j]==0) sum2+=c; else sum1+=c;
            }
            else {
                if (bel[j]==0) sum1+=c; else sum2+=c;
            }
        }
        if (sum1<=sum2) bel[i]=0; else bel[i]=1;
    }
    int cnt=0;
    vector<int> ed;ed.clear();
    rep(i,1,n) rep(j,i+1,n)
    {
        if (bel[i]!=bel[j] && judgetype(i,j)==-1)
            cnt++,ed.push_back(ga[i][j]);
        if (bel[i]==bel[j] && judgetype(i,j)==1)
            cnt++,ed.push_back(ga[i][j]);
    }
    printf("%d\n",cnt);
    for (auto id : ed) printf("%d\n",id);
    return 0;
}