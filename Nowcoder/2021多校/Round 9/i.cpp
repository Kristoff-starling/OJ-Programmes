#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;

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
    int n,w,x,y;scanf("%d%d%d%d",&n,&w,&x,&y);
    printf("%d\n",1ll*n*x%MOD*quick_pow(y,MOD-2)%MOD);
    return 0;
}