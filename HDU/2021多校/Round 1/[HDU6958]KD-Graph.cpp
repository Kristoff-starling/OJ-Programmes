#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=5e5;

int n,m,k;

struct Edge
{
    int x,y,c;
    void input() {scanf("%d%d%d",&x,&y,&c);}
    bool operator < (const Edge &other) const {return c<other.c;}
}a[MAXN+48];

int cnt;

namespace DSU
{
    int pre[MAXN+48];
    void init() {rep(i,1,n) pre[i]=i;cnt=n;}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    void update(int x,int y)
    {
        x=find_anc(x);y=find_anc(y);
        if (x!=y) cnt--,pre[x]=y;
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d",&n,&m,&k);
        rep(i,1,m) a[i].input();
        sort(a+1,a+m+1);
        if (n==k) {puts("0");continue;}
        DSU::init();int pt1=1,pt2;
        while (pt1<=m)
        {
            pt2=pt1;
            while (pt2<=m && a[pt2].c==a[pt1].c) pt2++;pt2--;
            rep(i,pt1,pt2) DSU::update(a[i].x,a[i].y);
            if (cnt==k) {printf("%d\n",a[pt1].c);break;}
            pt1=pt2+1;
        }
        if (pt1>m) puts("-1");
    }
    return 0;
}