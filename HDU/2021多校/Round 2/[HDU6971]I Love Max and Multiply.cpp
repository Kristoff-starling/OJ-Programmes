#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
using namespace std;

const int MOD=998244353;

const int MAXN=3e5;

int n,a[MAXN+48],b[MAXN+48];LL c[MAXN+48];
int maxa[MAXN+48],maxb[MAXN+48],mina[MAXN+48],minb[MAXN+48];

void check_max(int &x,int y) {x=max(x,y);}
void check_min(int &x,int y) {x=min(x,y);}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);rep(i,1,n) scanf("%d",b+i);
        rep(i,0,n-1) maxa[i]=maxb[i]=-1e9-1,mina[i]=minb[i]=1e9+1;
        rep(i,1,n) check_max(maxa[i-1],a[i]),check_min(mina[i-1],a[i]),check_max(maxb[i-1],b[i]),check_min(minb[i-1],b[i]);
        REP(i,n-1,1) rep(j,0,17) if (i&(1<<j))
        {
            check_max(maxa[i^(1<<j)],maxa[i]);
            check_max(maxb[i^(1<<j)],maxb[i]);
            check_min(mina[i^(1<<j)],mina[i]);
            check_min(minb[i^(1<<j)],minb[i]);
        }
        rep(i,0,n-1)
        {
            c[i]=max(1ll*maxa[i]*maxb[i],1ll*maxa[i]*minb[i]);
            c[i]=max(c[i],1ll*mina[i]*maxb[i]);
            c[i]=max(c[i],1ll*mina[i]*minb[i]);
        }
        REP(i,n-2,0) c[i]=max(c[i],c[i+1]);rep(i,0,n-1) c[i]%=MOD;
        LL ans=0;rep(i,0,n-1) ans=(ans+c[i])%MOD;
        ans=(ans+MOD)%MOD;printf("%lld\n",ans);
    }
    return 0;
}