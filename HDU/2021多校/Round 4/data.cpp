#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int a[100048];

int main ()
{
    freopen ("a.in","w",stdout);
    int ca=10001,n=100000;
    printf("%d\n",ca);
    printf("100000\n");
    rep(i,1,n) a[i]=i;
    random_shuffle(a+1,a+n+1);
    rep(i,1,n) printf("%d ",a[i]);puts("");
    ca--;
    while (ca--)
    {
        n=10;
        printf("%d\n",n);
        rep(i,1,n) a[i]=i;
    random_shuffle(a+1,a+n+1);
    rep(i,1,n) printf("%d ",a[i]);puts("");
    }
    return 0;
}