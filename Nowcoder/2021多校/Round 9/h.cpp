#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

LL n;
LL p[20];

int main ()
{
    scanf("%lld",&n);int len=1;LL pw=3,sum=3;
    while (sum<n)
    {
        pw=pw*3;
        sum+=pw;
        len++;
    }
    sum-=pw;n-=sum;
    p[0]=1;rep(i,1,len) p[i]=p[i-1]*3;
    LL res=0;
    rep(i,1,len)
    {
        LL pt=1;
        while (n>pt*p[len-i]) pt++;
        n-=(pt-1)*p[len-i];
        if (pt==1) res=res*10+2;
        else if (pt==2) res=res*10+3;
        else res=res*10+6;
    }
    printf("%lld\n",res);
    return 0;
}