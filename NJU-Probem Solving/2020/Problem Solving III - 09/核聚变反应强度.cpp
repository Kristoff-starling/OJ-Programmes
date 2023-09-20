#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

int n;
LL a[100048];

template<typename T> T mygcd(T x,T y) {return (!y)?x:mygcd(y,x%y);}
vector<LL> fac;

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%lld",a+i);
    rep(i,2,n) a[i]=mygcd(a[i],a[1]);
    int MAXN=1e6;LL tmp=a[1];
    rep(i,2,MAXN) if (tmp%i==0)
    {
        fac.push_back(i);
        while (tmp%i==0) tmp/=i;
    }
    if (tmp!=1) fac.push_back(tmp);
    rep(i,1,n) if (a[i]==1) printf("-1 ");
    else
    {
        int pt=0;while (a[i]%fac[pt]!=0) pt++;
        printf("%lld ",a[i]/fac[pt]);
    }
    puts("");return 0;
}