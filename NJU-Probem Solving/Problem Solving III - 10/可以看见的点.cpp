#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;

bool isprime[MAXN+48];int prime[MAXN+48],tot;int phi[MAXN+48];
int n;

void sieve()
{
    memset(isprime,true,sizeof(isprime));
    phi[1]=1;
    rep(i,2,n)
    {
        if (isprime[i]) prime[++tot]=i,phi[i]=i-1;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=n;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j]; else phi[i*prime[j]]=phi[i]*(prime[j]-1);
            if (i%prime[j]==0) break;
        }
    }
}

int main ()
{
    scanf("%d",&n);sieve();
    long long ans=0;rep(i,1,n) ans+=phi[i];
    printf("%lld\n",ans*2+1);
    return 0;
}