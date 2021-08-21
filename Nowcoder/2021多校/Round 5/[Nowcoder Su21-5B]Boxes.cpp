#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=1e5;

int n;double C;
double a[MAXN+48];double sum[MAXN+48];

int main ()
{
    scanf("%d%lf",&n,&C);
    rep(i,1,n) scanf("%lf",a+i);
    sort(a+1,a+n+1);
    sum[1]=a[1];rep(i,2,n) sum[i]=sum[i-1]+a[i];
    double ans=sum[n];
    double ans2=C;double pw=0.5;
    REP(i,n-1,1)
    {
        double cur=sum[i];
        cur=cur*pw;ans2+=cur;
        pw/=2;
    }
    printf("%.8lf\n",min(ans,ans2));
    return 0;
}