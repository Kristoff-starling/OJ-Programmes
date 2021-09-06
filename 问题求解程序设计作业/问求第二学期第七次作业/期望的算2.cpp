#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

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

int f[1000048],g[1000048];

int main ()
{
    int n;scanf("%d",&n);
    g[n]=0;REP(i,n-1,0) g[i]=(g[i+1]+1ll*n*quick_pow(n-i,MOD-2)%MOD)%MOD;
    f[n]=0;REP(i,n-1,0) f[i]=(f[i+1]+1ll*n*quick_pow(n-i,MOD-2)%MOD*g[i]%MOD)%MOD;
    printf("%d\n",f[0]);
    return 0;
}