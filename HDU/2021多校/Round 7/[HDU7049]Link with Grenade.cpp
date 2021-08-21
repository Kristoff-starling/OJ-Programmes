#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
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

int main ()
{
    int ca;scanf("%d",&ca);
    int inv2=quick_pow(2,MOD-2);
    while (ca--)
    {
        int t,v,r;scanf("%d%d%d",&t,&v,&r);
        int R1=v*t,R2=r,d=5*t*t;
        if (R1+R2<=d) {puts("1");continue;}
        if (R1>R2 && R1-R2>=d) {puts("1");continue;}
        if (R2>R1 && R2-R1>=d) {puts("0");continue;}
        int aa=((d*d+R1*R1-R2*R2)%MOD+MOD)%MOD,bb=quick_pow(2ll*d*R1%MOD,MOD-2);
        aa=1ll*aa*bb%MOD;
        aa=(1-aa+MOD)%MOD;aa=1ll*aa*inv2%MOD;
        printf("%d\n",MOD+1-aa);
    }
    return 0;
}