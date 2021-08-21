#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MOD=1e9+7;
const int MAXN=4e6;

int n,q;

int fac[MAXN+48],ifac[MAXN+48];

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

void init()
{
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    REP(i,MAXN-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int C(int x,int y) {if (x<y) return 0;return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;}

int ans[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&q);
    init();int x;
    rep(i,0,n*3) ans[i]=C(3*n+3,i+1);
    int inv=quick_pow(3,MOD-2);
    rep(i,0,n*3)
    {
        ans[i]=1ll*ans[i]*inv%MOD;
        Sub(ans[i+1],1ll*ans[i]*3%MOD);
        Sub(ans[i+2],1ll*ans[i]%MOD);
    }
    while (q--)
    {
        scanf("%d",&x);
        printf("%d\n",ans[x]);
    }
    return 0;
}