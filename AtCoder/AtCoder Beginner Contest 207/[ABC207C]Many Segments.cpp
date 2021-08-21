#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int n;

struct Segment
{
    int l,r;
    bool L,R;
}a[2001];

bool check(Segment x,Segment y)
{
    if (x.l==y.l) return true;
    if (x.l>y.l) swap(x,y);
    if (y.l>x.r) return false;
    if (y.l==x.r && (!y.L || !x.R)) return false;
    return true;
}

int main ()
{
    scanf("%d",&n);int t;
    rep(i,1,n)
    {
        scanf("%d%d%d",&t,&a[i].l,&a[i].r);a[i].L=a[i].R=false;
        if (t<=2) a[i].L=true;
        if (t==1 || t==3) a[i].R=true;
    }
    int ans=0;
    rep(i,1,n-1) rep(j,i+1,n) if (check(a[i],a[j])) ans++;
    printf("%d\n",ans);return 0;
}