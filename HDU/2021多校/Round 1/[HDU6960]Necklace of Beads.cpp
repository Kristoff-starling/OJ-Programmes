#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MOD=998244353;
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

int pw[MAXN+48];
int prime[MAXN+48],phi[MAXN+48],tot;bool isprime[MAXN+48];
int fac[MAXN+48],ifac[MAXN+48];

int C(int x,int y) {return (x<y)?0:1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;}

void init()
{
    fac[0]=1;rep(i,1,MAXN) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN]=quick_pow(fac[MAXN],MOD-2);
    REP(i,MAXN-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
    pw[0]=1;rep(i,1,MAXN) pw[i]=add(pw[i-1]+pw[i-1]);
    memset(isprime,true,sizeof(isprime));isprime[1]=false;phi[1]=1;
    rep(i,2,MAXN)
    {
        if (isprime[i]) prime[++tot]=i,phi[i]=i-1;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j]; else phi[i*prime[j]]=phi[i]*(prime[j]-1);
            if (i%prime[j]==0) break;
        }
    }
}

int n,k;

int calc(int d)
{
    int res=0;if (~d&1) res=2;
    rep(i,1,k/(n/d)) Add(res,1ll*pw[i]*add(C(d-i,i)+C(d-i-1,i-1))%MOD);
    return res;
}

int main ()
{
    init();int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&k);int lim=int(sqrt(n)),ans=0;
        rep(i,1,lim) if (n%i==0)
        {
            Add(ans,1ll*phi[n/i]*calc(i)%MOD);
            if (i!=n/i) Add(ans,1ll*phi[i]*calc(n/i)%MOD);
        }
        ans=1ll*ans*quick_pow(n,MOD-2)%MOD;
        printf("%d\n",ans);
    }
    return 0;
}