#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define LL long long
using namespace std;

const int MAXN=2e5;

int n;

struct node
{
    int x,y;
    bool operator < (const node &other) const {return x<other.x;}
}a[MAXN+48];

namespace DSU
{
    int pre[MAXN+48];
    void init() {rep(i,1,n) pre[i]=i;}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

struct edge
{
    int x,y;LL c;
    bool operator < (const edge &other) const {return c<other.c;}
}b[30000048];int tot;

LL calc_dist(int x1,int y1,int x2,int y2)
{
    return 1ll*(x1-x2)*(x1-x2)+1ll*(y1-y2)*(y1-y2);
}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1);int L,R;
    rep(i,1,n)
    {
        for (L=i-1;L>=1 && a[i].x==a[L].x;L--)
        {
            assert(tot<=3e7);
            b[++tot]=(struct edge){.x=i,.y=L,.c=calc_dist(a[i].x,a[i].y,a[L].x,a[L].y)};
        }
        for (int ptr=L;ptr>=1 && a[L].x-a[ptr].x<=10;ptr--)
        {
            assert(tot<=3e7);
            b[++tot]=(struct edge){.x=i,.y=ptr,.c=calc_dist(a[i].x,a[i].y,a[ptr].x,a[ptr].y)};
        }
        for (R=i+1;R<=n && a[i].x==a[R].x;R++)
        {
            assert(tot<=3e7);
            b[++tot]=(struct edge){.x=i,.y=R,.c=calc_dist(a[i].x,a[i].y,a[R].x,a[R].y)};
        }
        for (int ptr=R;ptr<=n && a[ptr].x-a[R].x<=10;ptr++)
        {
            assert(tot<=3e7);
            b[++tot]=(struct edge){.x=i,.y=ptr,.c=calc_dist(a[i].x,a[i].y,a[ptr].x,a[ptr].y)};
        }
    }
    sort(b+1,b+tot+1);LL ans=0;int cnt=0;
    DSU::init();
    for (int i=1;i<=tot && cnt<n-1;i++)
    {
        if (DSU::find_anc(b[i].x)!=DSU::find_anc(b[i].y))
        {
            cnt++;
            ans+=b[i].c;
            DSU::update(b[i].x,b[i].y);
        }
    }
    printf("%lld\n",ans);
    return 0;
}