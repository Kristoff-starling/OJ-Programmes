#include <bits/stdc++.h>
using namespace std;

const int MOD=1e9+7;

int main ()
{
    int ca;
    scanf("%d",&ca);long long n;
    while (ca--)
    {
        scanf("%lld",&n);
        n%=MOD;
        int ans=1ll*2*n%MOD*n%MOD*(n-1)%MOD*(n-1)%MOD;
        printf("%d\n",ans);
    }
    return 0;
}