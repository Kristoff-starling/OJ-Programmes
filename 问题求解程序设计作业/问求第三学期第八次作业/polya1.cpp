#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,m;

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

int calc_phi(int n)
{
    int res=n,lim=int(sqrt(n))+1;
    rep(p,2,lim) if (n%p==0)
    {
        res=res/p*(p-1);
        while (n%p==0) n/=p;
        if (n==1) break;
    }
    if (n!=1) res=res/n*(n-1);
    return res;
}

int main ()
{
    scanf("%d%d",&n,&m);int ans=0,lim=int(sqrt(n));
    rep(i,1,lim) if (n%i==0)
    {
        Add(ans,1ll*quick_pow(m,i)*calc_phi(n/i)%MOD);
        if (i!=n/i) Add(ans,1ll*quick_pow(m,n/i)*calc_phi(i)%MOD);
    }
    ans=1ll*ans*quick_pow(n,MOD-2)%MOD;
    printf("%d\n",ans);return 0;
}