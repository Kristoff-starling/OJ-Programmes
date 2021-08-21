#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e6;

int n,a[MAXN+48],cnt[MAXN+48];

int main ()
{
    long long ans=0;
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i),cnt[a[i]]++;
    for (int i=1;i<=MAXN;i++) if (cnt[i])
        for (int j=1;1ll*i*j<=MAXN;j++)
            ans+=1ll*cnt[i]*cnt[j]*cnt[i*j];
    printf("%lld\n",ans);
    return 0;
}