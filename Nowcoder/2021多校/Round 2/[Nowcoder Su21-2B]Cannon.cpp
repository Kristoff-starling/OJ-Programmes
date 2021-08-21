#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;++i)
#define REP(i,a,b) for (int i=a;i>=b;--i)
using namespace std;

const int MOD=1e9+9;
const int MAXN=1e7;

int f[MAXN+48];

int fac[MAXN+48],ifac[MAXN+48];
int pw[MAXN+48];

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

int main ()
{
    int x,y;
    scanf("%d%d",&x,&y);
    int aans=1,cur=1;
    rep(i,1,x+y-4)
    {
        cur=1ll*cur*2%MOD*(x+y-4-(i-1))%MOD;
        aans^=cur;
    }
    printf("%d ",aans);
    f[0]=1;
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    REP(i,MAXN-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
    pw[0]=1;rep(i,1,MAXN) pw[i]=(pw[i-1]+pw[i-1])%MOD;
    rep(i,1,x+y-4)
    {
        f[i]=1ll*f[i-1]*2%MOD*(x+y-4-(i-1))%MOD;
        if (i<=x-2) f[i]=(f[i]+1ll*fac[x-2]*ifac[x-2-i]%MOD*pw[i]%MOD)%MOD;
        if (i<=y-2) f[i]=(f[i]+1ll*fac[y-2]*ifac[y-2-i]%MOD*pw[i]%MOD)%MOD;
        f[i]=1ll*f[i]*ifac[2]%MOD;
    }
    int ans=f[0];rep(i,1,x+y-4) ans^=f[i];
    printf("%d\n",ans);return 0;
}