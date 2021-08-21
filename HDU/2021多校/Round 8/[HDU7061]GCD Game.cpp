#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e7;

int isprime[MAXN+48];int prime[MAXN+48],tot;
int cnt[MAXN+48];

void sieve()
{
    tot=0;rep(i,1,MAXN) isprime[i]=i;
    rep(i,2,MAXN)
    {
        if (isprime[i]==i) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=prime[j];
            if (i%prime[j]==0) break;
        }
    }
    cnt[1]=0;
    rep(i,2,MAXN) cnt[i]=cnt[i/isprime[i]]+1;
}

int main ()
{
    sieve();
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        int n,x;scanf("%d",&n);int res=0;
        while (n--) scanf("%d",&x),res^=cnt[x];
        if (res) puts("Alice"); else puts("Bob");
    }
    return 0;
}