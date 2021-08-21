#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define pb push_back
using namespace std;

const int MAXN=2e6;

int n;LL a[MAXN+48];

bool isprime[MAXN+48];int prime[MAXN+48],tot;

void sieve()
{
    memset(isprime,true,sizeof(isprime));tot=0;
    rep(i,2,MAXN)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    }
}

int gen() {return ((rand()<<15)+rand())%n+1;}

vector<LL> Decompose(LL x)
{
    vector<LL> res;res.clear();int pt=1;
    while (x!=1 && pt<=tot)
    {
        if (x%prime[pt]==0)
        {
            res.pb(prime[pt]);
            while (x%prime[pt]==0) x/=prime[pt];
        }
        pt++;
    }
    if (x!=1) res.pb(x);
    return res;
}

int main ()
{
    srand(time(NULL));
    int ca;scanf("%d",&ca);sieve();
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%lld",a+i);
        int K=30,ans=1;
        while (K--)
        {
            int p1,p2;
            do
            {
                p1=gen();p2=gen();
            }
            while (p1==p2);
            vector<LL> fac=Decompose(abs(a[p1]-a[p2]));
            for (auto t : fac)
            {
                int cnt=0;
                rep(i,1,n) if (abs(a[i]-a[p1])%t==0) cnt++;
                ans=max(ans,cnt);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}