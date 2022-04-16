#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int main ()
{
    int n,m;scanf("%d%d",&n,&m);
    long long ans=0;
    for (int i=0;i<=n;i+=2) for (int j=0;j<=m;j+=2)
    {
        if (i==0 && j==0) continue;
        if (i==0 || j==0)
            ans+=(n-i+1)*(m-j+1);
        else
            ans+=(n-i+1)*(m-j+1)*2;
    }
    printf("%lld\n",ans);
    return 0;
}