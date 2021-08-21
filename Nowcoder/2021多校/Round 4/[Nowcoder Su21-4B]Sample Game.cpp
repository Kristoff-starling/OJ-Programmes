#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;

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

int n,p[148];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",p+i);
    int sum=0;rep(i,1,n) Add(sum,p[i]);sum=quick_pow(sum,MOD-2);rep(i,1,n) p[i]=1ll*p[i]*sum%MOD;
    int f=1;rep(i,1,n) f=1ll*f*quick_pow(sub(1-p[i]),MOD-2)%MOD;
    int ss=0;rep(i,1,n) Add(ss,1ll*p[i]*quick_pow(sub(1-p[i]),MOD-2)%MOD);
    int ff=1ll*f*ss%MOD;ff=add(ff+ff);
    printf("%d\n",add(ff+f));return 0;
}