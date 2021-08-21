#include <bits/stdc++.h>
using namespace std;

long long a,p;

long long quick_Mul(long long x,long long y)
{
   __int128 X=x,Y=y;X=X*Y%p;
   return X;
}

long long quick_pow(long long x,long long y)
{
    long long res=1;
    while (y)
    {
        if (y&1) res=quick_Mul(res,x);
        x=quick_Mul(x,x);y>>=1;
    }
    return res;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%lld%lld",&a,&p);
        long long res=quick_pow(a,(p-1)/2);
        assert(res==1 || res==p-1);
        if (res==1) puts("0"); else puts("1");
    }
    return 0;
}