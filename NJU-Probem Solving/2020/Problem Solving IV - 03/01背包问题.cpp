#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
using namespace std;

int n,V;

int c[48],v[48];

struct node
{
    int w;LL val;
    bool operator < (const node &other) const {return w<other.w;}
}a[2000048],b[2000048];int atot,btot;
LL maxa[2000048],maxb[2000048];

void init(int l,int r,int &tot,node arr[],LL mx[])
{
    int cnt=r-l+1;
    rep(Mask,0,(1<<cnt)-1)
    {
        int weight=0;LL val=0;
        rep(i,0,cnt-1) if (Mask>>i&1)
        {
            weight+=c[l+i];val+=v[l+i];
            if (weight>V) {weight=-1;break;}
        }
        if (weight!=-1) arr[++tot]=node{.w=weight,.val=val};
    }
    sort(arr+1,arr+tot+1);
    mx[1]=arr[1].val;rep(i,2,tot) mx[i]=max(mx[i-1],arr[i].val);
}

int main ()
{
    scanf("%d%d",&n,&V);atot=btot=0;
    rep(i,1,n) scanf("%d%d",c+i,v+i);
    init(1,n>>1,atot,a,maxa);init((n>>1)+1,n,btot,b,maxb);
    int pt=btot;LL ans=0;
    rep(i,1,atot)
    {
        while (pt>0 && a[i].w+b[pt].w>V) pt--;
        if (pt>0) ans=max(ans,maxa[i]+maxb[pt]);
    }
    printf("%lld\n",ans);
    return 0;
}