#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=2e5;

bool isprime[MAXN+48];int prime[MAXN+48],tot;

void sieve()
{
    memset(isprime,true,sizeof(isprime));tot=0;
    rep(i,2,MAXN)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*prime[j]*i<=MAXN;j++)
        {
            isprime[prime[j]*i]=false;
            if (i%prime[j]==0) break;
        }
    }
}

int main ()
{
#ifndef ONLINE_JUDGE
    double T=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int n,w,ans=0;scanf("%d%d",&n,&w);
    sieve();
    rep(i,2,n)
    {
        int cnt=0,tmp=i;
        for (int j=1;j<=tot && tmp!=1;j++)
            while (tmp%prime[j]==0) cnt++,tmp/=prime[j];
        if (cnt==w) ans++;
    }
    printf("%d\n",ans);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}