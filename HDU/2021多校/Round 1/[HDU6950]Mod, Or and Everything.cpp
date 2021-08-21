#include <bits/stdc++.h>
using namespace std;

long long n;

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%lld",&n);
        long long ans=1;
        while (n-ans>ans) ans<<=1;
        printf("%lld\n",ans-1);
    }
    return 0;
}