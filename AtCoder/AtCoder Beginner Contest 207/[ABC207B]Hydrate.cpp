#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
    int res=b/c;
    if (res>=d) {puts("-1");return 0;}
    long long div=1ll*d*c-b;
    long long ans=1ll*a/div;
    if ((long long)a%div!=0) ans++;
    printf("%lld\n",ans);return 0;
}