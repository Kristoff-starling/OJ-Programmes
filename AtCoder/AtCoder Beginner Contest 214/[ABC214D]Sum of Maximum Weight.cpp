#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;

int n;

struct Edge
{
    int x,y,c;
    void input() {scanf("%d%d%d",&x,&y,&c);}
    bool operator < (const Edge &other) const {return c<other.c;}
}a[MAXN+48];

namespace DSU
{
    int pre[MAXN+48],sz[MAXN+48];
    void init() {rep(i,1,n) pre[i]=i,sz[i]=1;}
    int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    int query(int x) {x=find_anc(x);return sz[x];}
    void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;sz[y]+=sz[x];}
}

int main ()
{
    scanf("%d",&n);rep(i,1,n-1) a[i].input();sort(a+1,a+n);DSU::init();
    long long ans=0;
    rep(i,1,n)
    {
        int sz1=DSU::query(a[i].x),sz2=DSU::query(a[i].y);
        ans+=1ll*sz1*sz2*a[i].c;
        DSU::update(a[i].x,a[i].y);
    }
    printf("%lld\n",ans);
    return 0;
}