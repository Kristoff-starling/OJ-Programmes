#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=1e6;
int prime[MAXN+48],tot;bool isprime[MAXN+48];
int sum[MAXN+48];

void sieve()
{
    memset(isprime,true,sizeof(isprime));
    rep(i,2,MAXN)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    }
    sum[1]=0;rep(i,2,MAXN) sum[i]=sum[i-1]+(isprime[i]?1:0);
}

int main ()
{
    sieve();
    long long n,ans=0;scanf("%lld",&n);
    for (int i=1;i<=tot && 1ll*prime[i]*prime[i]*prime[i]<=n;i++)
    {
        long long rem = min(n / (1ll*prime[i]*prime[i]*prime[i]),(long long)prime[i]-1);
        ans+=sum[rem];
    }
    printf("%lld\n",ans);
    return 0;
}