#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

bool isprime[100000001];int prime[20000048],tot;

void sieve(int n)
{
    isprime[2]=isprime[3]=isprime[5]=1;
    for (int k=6;k<=n;k+=6) isprime[k+1]=isprime[k+5]=1;
    for (int i=2;i<=5;i++)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=n;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    }
    for (int k=6;k<=n;k+=6)
    {
        int i=k+1;
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=n;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
        i+=4;
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=n;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    } 
}

int main ()
{
    int n,q,k;scanf("%d%d",&n,&q);sieve(n);
    while (q--)
    {
        scanf("%d",&k);
        printf("%d\n",prime[k]);
    }
    return 0;
}