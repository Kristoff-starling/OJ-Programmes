#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=1e4;

int n,m;

namespace DSU
{
    int pre[MAXN+48],val[MAXN+48];
    void init() {rep(i,0,n) pre[i]=i,val[i]=0;}
    int find_anc(int x)
    {
        if (x==pre[x]) return x;
        int fa=pre[x];pre[x]=find_anc(pre[x]);
        val[x]+=val[fa];
        return pre[x];
    }
    bool update(int x,int y,int c)
    {
        int fx=find_anc(x),fy=find_anc(y);
        if (fx!=fy)
            pre[fx]=fy,val[fx]=-val[x]+c+val[y];
        else
            if (c+val[y]!=val[x]) return false;
        return true;
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);
        DSU::init();int x,y,c;
        bool f=true;
        rep(i,1,m)
        {
            scanf("%d%d%d",&x,&y,&c);
            if (!DSU::update(y,x-1,c)) f=false;
        }
        puts(f?"true":"false");
    }
    return 0;
}