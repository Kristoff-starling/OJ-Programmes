#include <cstdio>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n;LL ans;

int gcd(int x,int y) {return (!y)?x:gcd(y,x%y);}

LL quick_pow(LL x,LL y)
{
    LL res=1;
    while (y)
    {
        if (y&1) res*=x;
        x*=x;y>>=1;
    }
    return res;
}

int main ()
{
    while (scanf("%d",&n) && n!=-1)
    {
        if (n==0) {puts("0");continue;}
        ans=0;rep(i,1,n) ans+=quick_pow(3,gcd(i,n));
        if (n&1) ans+=quick_pow(3,(n+1)/2)*n; else ans+=quick_pow(3,n/2)*n/2+quick_pow(3,n/2+1)*n/2;
        ans/=(n*2);printf("%lld\n",ans);
    }
    return 0;
}