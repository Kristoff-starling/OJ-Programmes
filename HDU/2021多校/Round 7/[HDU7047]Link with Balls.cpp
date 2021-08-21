#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2e6;
const int MOD=1e9+7;

int quick_pow(int x,int y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%MOD;
        x=1ll*x*x%MOD;y>>=1;
    }
    return res;
}

int fac[MAXN+48],ifac[MAXN+48];

void init()
{
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    for (int i=MAXN-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int C(int x,int y)
{
    if (x<0 || x<y || y<0) return 0;
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

int main ()
{
    int ca;scanf("%d",&ca);
    init();
    while (ca--)
    {
        int n,m;scanf("%d%d",&n,&m);
        printf("%d\n",(C(m+n,n)-C(m-1,n)+MOD)%MOD);
    }
    return 0;
}