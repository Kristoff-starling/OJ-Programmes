#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

LL n,c,p,q,phi,e;

void exgcd(LL a,LL b,LL &x,LL &y)
{
    if (b==0) {x=1;y=0;return;}
    exgcd(b,a%b,x,y);
    LL t=x;x=y;y=t-a/b*y;
}

inline LL add(LL x,LL m) {if (x>=m) x-=m;return x;}

LL quick_mul(LL x,LL y,LL m)
{
    LL res=0;x%=m;
    while (y)
    {
        if (y&1) res=add(res+x,m);
        x=add(x+x,m);y>>=1;
    }
    return res;
}

LL quick_pow(__int128 x,__int128 y,LL m)
{
    LL res=1;x%=m;
    /*
    while (y)
    {
        if (y&1) res=quick_mul(res,x,m);
        x=quick_mul(x,x,m);y>>=1;
    }
    */
    while (y)
    {
        if (y&1) res=res*x%m;
        x=x*x%m;y>>=1;        
    }
    return res;
}

int main ()
{
    // freopen ("a.in","r",stdin);
    // freopen ("a.out","w",stdout);
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%lld%lld",&n,&c);
        LL sqt=(LL)(sqrt(n));
        for (p=sqt;n%p!=0;p--);
        for (q=sqt+1;n%q!=0;q++);
        phi=(p-1)*(q-1);
        e=(1ll<<30)+3;
        LL d,y;exgcd(e,phi,d,y);d%=phi;if (d<0) d+=phi;
        printf("%lld\n",quick_pow(c,d,n));
    }
    return 0;
}