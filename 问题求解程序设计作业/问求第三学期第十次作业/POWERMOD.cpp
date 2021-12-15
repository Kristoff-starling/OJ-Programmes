#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL a,b,m;

LL quick_mul(LL x,LL y)
{
    LL res=0;x%=m;
    while (y)
    {
        if (y&1) res=(res+x)%m;
        x=(x+x)%m;y>>=1;
    }
    return res;
}

LL quick_pow(LL x,LL y)
{
    LL res=1;x%=m;
    while (y)
    {
        if (y&1) res=quick_mul(res,x);
        x=quick_mul(x,x);y>>=1;
    }
    return res;
}

int main ()
{
    scanf("%lld%lld%lld",&a,&b,&m);
    printf("%lld\n",quick_pow(a,b));
    return 0;
}