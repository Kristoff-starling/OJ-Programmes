#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int main ()
{
    int ca;scanf("%d",&ca);LL n;
    while (ca--)
    {
        scanf("%lld",&n);
        int lim=int(sqrt(n));
        bool f=true;
        rep(i,2,lim) if (n%i==0) {f=false;break;}
        puts(f?"true":"false");
    }
    return 0;
}