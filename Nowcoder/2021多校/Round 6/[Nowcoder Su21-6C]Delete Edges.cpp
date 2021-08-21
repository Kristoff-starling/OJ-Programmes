#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int tot,a[4000048],b[4000048],c[4000048];

int main ()
{
    int n;scanf("%d",&n);
    rep(i,1,n-2) rep(j,i+1,n-1)
    {
        int k=2*n-i-j;if (k>n) k-=n;
        if (j<k) a[++tot]=i,b[tot]=j,c[tot]=k;
    }
    printf("%d\n",tot);
    rep(i,1,tot) printf("%d %d %d\n",a[i],b[i],c[i]);
    return 0;
}