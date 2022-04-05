#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

const int MAXN=1000;

int n,a[MAXN+48],b[MAXN+48],t[MAXN+48];

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d%d",a+i,b+i);
        rep(i,1,n)
        {
            int cnt=100/a[i];
            if (100%a[i]==0) t[i]=(cnt-1)*b[i]; else t[i]=cnt*b[i];
        }
        int cc=0,minn=1e9;
        rep(i,1,n) if (t[i]<minn) cc=1,minn=t[i]; else if (t[i]==minn) cc++;
        double ans=1.0*cc/n*0.5+1.0*(n-cc)/n;
        printf("%.6lf\n",ans);
    }
    return 0;
} 