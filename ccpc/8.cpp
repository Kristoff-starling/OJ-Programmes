#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e6;
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

int fac[MAXN+48],ifac[MAXN+48],sum[MAXN+48];

void init()
{
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    for (int i=MAXN-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
    sum[1]=ifac[1];rep(i,2,MAXN) sum[i]=(sum[i-1]+ifac[i])%MOD;
}

int main ()
{
    int ca;scanf("%d",&ca);init();
    while (ca--)
    {
        int n,m;scanf("%d%d",&n,&m);int ans;
        ans=1ll*fac[m]*fac[n-m]%MOD*(n-m+1)%MOD;
        ans=(ans+1ll*(m-1)*fac[m]%MOD*fac[n-m]%MOD)%MOD;
        ans=(ans-1ll*fac[m]*sum[m-1]%MOD+MOD)%MOD;
        printf("%d\n",ans);
    }
    return 0;
}