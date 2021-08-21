#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MOD=1e9+7;
const int MAXN=1e6;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

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

int f[MAXN+48],sum[MAXN+48],fac[MAXN+48],inv[MAXN+48];

int main ()
{
    f[1]=f[2]=0;
    rep(i,3,MAXN) if (i&1) f[i]=add(f[i/2]+f[i/2]+1); else f[i]=add(f[i/2]+f[i/2-1]+1);
    sum[1]=f[1];rep(i,2,MAXN) sum[i]=add(sum[i-1]+f[i]);
    rep(i,1,MAXN) sum[i]=add(sum[i]+sum[i]);
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    inv[MAXN]=quick_pow(fac[MAXN],MOD-2);REP(i,MAXN-1,0) inv[i]=1ll*inv[i+1]*(i+1)%MOD;
    rep(i,1,MAXN) inv[i]=1ll*fac[i-1]*inv[i]%MOD;
    int n,ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);
        if (n==1 || n==2) {puts("1");continue;}
        printf("%d\n",1ll*add(n+n+n-4+sum[n-2])*inv[n]%MOD);
    }
    return 0;
}