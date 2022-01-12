#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

LL quick_pow(LL x,LL y,LL MO)
{
    LL res=1;
    while (y)
    {
        if (y&1)
        {
            res*=x;
            if (res>=MO) res=res%MO;
        }
        x*=x;
        if (x>=MO) x=x%MO;
        y>>=1;
    }
    return res;
}

LL calc3(LL c,LL d)
{
    return quick_pow(c,d,5e8+2);
}

LL calc2(LL b,LL c,LL d)
{
    LL y=calc3(c,d);
    return quick_pow(b,y,1e9+6);
}

LL calc1(LL a,LL b,LL c,LL d)
{
    LL y=calc2(b,c,d);
    return quick_pow(a,y,1e9+7);
}

int main ()
{
    int ca;scanf("%d",&ca);
    LL a,b,c,d;
    while (ca--)
    {
        scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
        printf("%lld\n",calc1(a,b,c,d)%(1000000007));
    }
    return 0;
}