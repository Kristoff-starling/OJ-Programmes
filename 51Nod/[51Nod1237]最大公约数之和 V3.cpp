#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e7;
const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int prime[MAXN+48],tot;bool isprime[MAXN+48];int phi[MAXN+48],sum[MAXN+48];

void init()
{
    memset(isprime,true,sizeof(isprime));isprime[1]=false;phi[1]=1;
    rep(i,2,MAXN)
    {
        if (isprime[i]) prime[++tot]=i,phi[i]=i-1;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j]; else phi[i*prime[j]]=phi[i]*(prime[j]-1);
            if (i%prime[j]==0) break;
        }
    }
    sum[0]=0;rep(i,1,MAXN) sum[i]=add(sum[i-1]+phi[i]);
}

unordered_map<long long,int> M;

int calc(long long n)
{
    if (n<=MAXN) return sum[n];
    if (M.find(n)!=M.end()) return M[n];
    int res=(n+1)%MOD*(n%MOD)%MOD*((MOD+1)/2)%MOD;long long l,r;
    for (l=2;l<=n;l=r+1)
    {
        r=n/(n/l);
        Sub(res,(r-l+1)%MOD*calc(n/l)%MOD);
    }
    return M[n]=res;
}

int main ()
{
    init();long long n;scanf("%lld",&n);
    long long l,r;int ans=0;
    for (l=1;l<=n;l=r+1)
    {
        r=n/(n/l);
        Add(ans,(n/l%MOD)*(n/l%MOD)%MOD*sub(calc(r)-calc(l-1))%MOD);
    }
    printf("%d\n",ans);return 0;
}