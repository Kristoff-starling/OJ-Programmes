#include <bits/stdc++.h>
using namespace std;

int main ()
{
    long long a,b;
    scanf("%lld%lld",&a,&b);
    long double res=a;res/=b;
    if (res>=0) printf("%llu\n",(unsigned long long)floor(res)); else printf("%lld\n",(long long)ceil(res));
    return 0;
}