#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MOD=998244353;
const int MAXN=2e6;

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

int fac[MAXN+48],ifac[MAXN+48];

void init_C()
{
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    REP(i,MAXN-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int C(int x,int y)
{
    if (x<y) return 0;
    if (y<0) return 0;
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

char s[MAXN+48];int n,k;
int F[MAXN+48],G[MAXN+48],sum[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);init_C();
    while (ca--)
    {
        scanf("%d%s",&k,s+1);n=strlen(s+1);
        F[0]=((k>1)?1:0);rep(i,1,n) F[i]=sub(add(F[i-1]+F[i-1])-C(i-1,k-2));
        G[0]=1;rep(i,1,n) G[i]=sub(add(G[i-1]+G[i-1])-C(i-1,k-1));
        int pw=1;sum[0]=F[n-2];
        rep(i,1,n-2) pw=1ll*pw*10%MOD,sum[i]=add(sum[i-1]+1ll*pw*F[n-2-i]%MOD);
        int ans=0;pw=1;
        rep(i,1,n-1) Add(ans,1ll*(s[i]-'0')*sum[n-1-i]%MOD);
        REP(i,n,1) Add(ans,1ll*(s[i]-'0')*pw%MOD*G[i-1]%MOD),pw=1ll*pw*10%MOD;
        printf("%d\n",ans);
    }
    return 0;
}