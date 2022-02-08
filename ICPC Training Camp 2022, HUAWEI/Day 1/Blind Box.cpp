#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MOD=998244353;
const int MAXN=3e5;

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
void init()
{
    fac[0]=1;
    rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);    
    REP(i,MAXN-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int C(int x,int y)
{
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

int main ()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();int ans=0;
    for (int i=0;i<=m;i++)
    {
        int curans=1ll*C(m,i)*quick_pow(m-i,n+m)%MOD;
        if (i%2==0) Add(ans,curans); else Sub(ans,curans);
    }
    ans=1ll*ans*ifac[m]%MOD;
    int ians=0;
    for (int i=n-1;i<=n+m-2;i++)
        Add(ians,C(i,i-n+1));
    printf("%d\n", 1ll*ans*quick_pow(ians,MOD-2)%MOD);
    return 0;
}