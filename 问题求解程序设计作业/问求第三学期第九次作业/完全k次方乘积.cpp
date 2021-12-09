#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define mp make_pair
#define pb push_back
using namespace std;

int n,k;
int a[100048];

vector<Pair> fac[100048];
int isprime[100048],prime[100048],tot;
void sieve()
{
    rep(i,1,100000) isprime[i]=i;tot=0;
    rep(i,2,100000)
    {
        if (isprime[i]==i) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=100000;j++)
        {
            isprime[i*prime[j]]=prime[j];
            if (i%prime[j]==0) break;
        }
    }
    rep(i,2,100000)
    {
        int curcnt=0,curfac=0,tmp=i;
        while (tmp!=1)
        {
            if (isprime[tmp]!=curfac)
            {
                if (curfac && curcnt%k) fac[i].pb(mp(curfac,curcnt%k));
                curfac=isprime[tmp];curcnt=1;
            }
            else curcnt++;
            tmp/=isprime[tmp];
        }
        if (curfac && curcnt%k) fac[i].pb(mp(curfac,curcnt%k));
    }
}

int cnt[100048];

int get_complement(int x,int &cur)
{
    LL res=1;cur=1;bool f=false;
    for (auto item : fac[x])
    {
        int pw=k-item.second;
        if (!f)
        {
            while (pw--)
            {
                res*=item.first;
                if (res>100000) f=true;
            }
        }
        pw=item.second;
        while (pw--) cur*=item.first;
    }
    return (f?-1:res);
}

int main ()
{
    scanf("%d%d",&n,&k);rep(i,1,n) scanf("%d",a+i);
    sieve();LL ans=0;
    rep(i,1,n)
    {
        int cur;int target=get_complement(a[i],cur);
        if (target!=-1) ans+=cnt[target];
        cnt[cur]++;
    }
    printf("%lld\n",ans);
    return 0;
}