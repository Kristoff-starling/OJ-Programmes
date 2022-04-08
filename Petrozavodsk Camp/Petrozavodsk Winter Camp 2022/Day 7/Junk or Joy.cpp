#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

bool isprime[100048];
int prime[100048],tot;
int k;
int fac[48],ftot;
LL pw[100048][40];int lim[100048];

void init()
{
    tot=0;memset(isprime,true,sizeof(isprime));
    rep(i,2,100000)
    {
        if (isprime[i]) prime[++tot]=i;
        for (int j=1;j<=tot && 1ll*i*prime[j]<=100000;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) break;
        }
    }
    rep(i,2,100000)
    {
        pw[i][0]=1;lim[i]=0;
        while (pw[i][lim[i]]<=2000000000)
        {
            lim[i]++;
            pw[i][lim[i]]=pw[i][lim[i]-1]*i;
        }
        lim[i]--;
    }
}

void Fac(int n)
{
    ftot=0;
    for (int i=1;i<=tot && n!=1;i++)
    {
        if (n%prime[i]==0)
        {
            fac[++ftot]=1;
            while (n%prime[i]==0) fac[ftot]*=prime[i],n/=prime[i];
        }
    }
    if (n!=1) fac[++ftot]=n;
}

namespace MR
{
    typedef long double ld;
    typedef long long ll;
    typedef unsigned long long ull;
    #define Fo(i,a,b) for(LL i=(a); i<=(b); i++)
    #define Ro(i,b,a) for(LL i=(b); i>=(a); i--)
    #define Eo(i,x,_) for(LL i=head[x]; i; i=_[i].next)
    #define Ms(a,b) memset((a),(b),sizeof(a))
    inline ull qmul(ull a,ull b,const ull mod){
        ll c=(ll)(a)*b-(ll)((ull)((ld)(a)*b/mod)*mod);
        return c<0? c+mod:(c<mod? c:c-mod);
    }

    LL qpow(LL a , LL b , LL mod) {
        LL res = 1;
        while(b) {
            if(b&1)
                res = qmul(res,a,mod);
            a = qmul(a,a,mod);
            b>>=1;
        }
        return res;
    }

    bool check(LL x) {
        if(x==2) return true;
        if(x<2||x%2==0) return false;
        LL A[12]={2,3,5,7,11,13,17,19,23,29,31,37};
        Fo(i,0,11)
            if(x==A[i])
                return true;
        LL m=x-1 , k=0;
        while(m%2==0) {
            k++;
            m>>=1;
        }
        Fo(i,0,11) {
            LL y = qpow(A[i],m,x) , z;
            z = y;
            Fo(j,1,k) {
                y = qmul(y,y,x);
                if(y==1&&z!=1&&z!=x-1)
                    return false;
                z = y;
            }
            if(y!=1)
                return false;
        }
        return true;
    }
}

int calc(int a,int b)
{
    if (b<=a || b%a!=0) return 0;
    b/=a;int res=0;
    if (b!=2 && MR::check(b)) res++;
    int l,r,last=b;
    for (int m=2;m<=30;m++)
    {
        l=2;r=min(last,100000);
        while (l<=r)
        {
            int mid=(l+r)>>1;
            if (lim[mid]<m || pw[mid][m]>b) r=mid-1; else last=mid,l=mid+1;
        }
        if (lim[last]>=m && pw[last][m]==b && isprime[last] && last!=2)
            res++;
        last++;
    }
    return res;
}

bool issquare(__int128 n)
{
    LL l=2,r=100000000000LL;__int128 mid;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (mid*mid==n) return true;
        if (mid*mid>n) r=mid-1; else l=mid+1;
    }
    return false;
}

int main ()
{
    int ca;scanf("%d",&ca);
    init();
    while (ca--)
    {
        scanf("%d",&k);Fac(k);int ans=0;
        if (k==1) {puts("2");continue;}
        // no 2
        if (ftot>=1 && fac[1]%2!=0)
        {
            rep(Mask,0,(1<<ftot)-1)
            {
                int s=1;
                rep(i,0,ftot-1) if (Mask>>i&1) s*=fac[i+1];
                ans+=calc(k/s,s+2);ans+=calc(k/s,s-2);
            }
        }
        // has 2
        else
        {
            if (ftot>=1 && fac[1]!=2)
            {
                rep(Mask,0,(1<<ftot)-1) if (Mask&1)
                {
                    int s=1;
                    rep(i,1,ftot-1) if (Mask>>i&1) s*=fac[i+1];
                    ans+=calc(k/s/2,s*2+2);ans+=calc(k/s/2,s*2-2);
                    ans+=calc(k/s/fac[1]*2,s*fac[1]/2+2);
                    ans+=calc(k/s/fac[1]*2,s*fac[1]/2-2);
                }
            }
        }
        // p=2
        __int128 num=k;
        for (int m=1;m<=35;m++)
        {
            num<<=1;
            if (issquare(num+1)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}