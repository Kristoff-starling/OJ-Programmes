#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int ca,m;long long n;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%lld",&m,&n);
        if (m==1) puts(n==0?"1":"2");
        else if (n==0L) printf("%lld\n",(1ll<<m));
        else printf("%lld\n", (1ll<<m)-1);
    }
}