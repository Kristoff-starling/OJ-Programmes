#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=1e7;

bool isprime[MAXN+48];long long sum[MAXN+48];
int prime[MAXN+48],tot;

void init()
{
    memset(isprime,true,sizeof(isprime));
    isprime[1]=false;
    rep(i,2,MAXN)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    }
    sum[1]=sum[2]=0;rep(i,3,MAXN) sum[i]=sum[i-1]+(isprime[i]?i:0);
}

int main ()
{
    int ca,n;scanf("%d",&ca);
    init();
    while (ca--)
    {
        scanf("%d",&n); 
        printf("%lld\n",1ll*n*(n+1)/2-3+sum[n]);
    }
    return 0;
}