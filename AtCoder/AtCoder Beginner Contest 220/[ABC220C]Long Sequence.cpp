#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;

int n;long long X;
int a[MAXN+48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
    scanf("%lld",&X);long long sum=0;
    rep(i,1,n) sum+=a[i];long long ans=0;
    if (X%sum==0) ans=X/sum*n+1;
    else
    {
        ans=X/sum*n;X=X%sum;
        int pt=1;
        while (X>=0) ans++,X-=a[pt++];
    }
    printf("%lld\n",ans);
    return 0;
}