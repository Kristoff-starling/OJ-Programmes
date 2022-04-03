#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

const int MAXN=1e6;
const int MOD=1e9+7;

int n;
int a[MAXN+48];
unordered_set<int> t[MAXN+48];

int quick_pow(int x,int y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%MOD;
        x=1ll*x*x%MOD;y>>=1;
    }
    return res;
}

int tot,prime[MAXN+48],isprime[MAXN+48];

void sieve_prime()
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
}

vector<int> pos[MAXN+48];

void defac(int n,int id)
{
    int cnt=0,curfac=0;
    while (n!=1)
    {
        if (isprime[n]!=curfac)
        {
            if (cnt&1) pos[curfac].push_back(id);
            cnt=0,curfac=isprime[n];
        }
        cnt++;n/=isprime[n];
    }
    if (cnt&1) pos[curfac].push_back(id);
}

int main ()
{
    sieve_prime();
    scanf("%d",&n);
    rep(i,1,n) scanf("%d",a+i),defac(a[i],i);
    int ans=1;
    rep(_,1,tot)
    {
        int cur=prime[_],sz=int(pos[cur].size());
        if (sz>0) ans=1ll*ans*quick_pow(cur,min(sz,n-sz))%MOD;
    }
    printf("%d\n",ans);
    return 0;
}