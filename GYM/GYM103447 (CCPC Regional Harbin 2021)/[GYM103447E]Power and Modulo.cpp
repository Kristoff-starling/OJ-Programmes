#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n;
int a[100048];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);

        bool flag=true;
        rep(i,1,n) if (a[i]!=0) {flag=false;break;}
        if (flag) {puts("1");continue;}

        flag=true;int M=0;
        if (a[1]!=1) {puts("-1");continue;}
        for (int i=1;i<=n-1;i++)
        {
            if (a[i]*2<a[i+1]) {flag=false;break;}
            if (a[i]*2==a[i+1]) continue;
            if (a[i]*2>a[i+1])
            {
                if (M!=0 && a[i]*2-a[i+1]!=M) {flag=false;break;}
                M=a[i]*2-a[i+1];
            }
        }
        rep(i,1,n) if (a[i]>=M) flag=false;
        if (!flag) puts("-1"); else printf("%d\n", M);
    }
    return 0;
}