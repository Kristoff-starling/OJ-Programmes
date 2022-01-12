#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

namespace MillerRabin
{
    //Miller_Rabin
    //int: 2, 7, 61
    //long long
    int lp[]={2,325,9375,28178,450775,9780504,1795265022};
    //3e15: 2, 2570940, 880937, 610386380, 4130785767
    //4e13: 2, 2570940, 211991001, 3749873356
    LL quick_pow(LL x,LL y,LL MO)
    {
        int res=1;
        while (y)
        {
            if (y&1) res=res*x%MO;
            x=x*x%MO;y>>=1;
        }
        return res;
    }
    LL x[148];
    bool solve(LL n)
    {
        int i;
        if (n==1) return false;
        if (n==2) return true;
        for (i=0;i<=6;i++)
            if (n%lp[i]==0) return false;
        LL tmp=n-1;int k=0,ti=2;
        while (!(tmp&1)) k++,tmp>>=1;
        while (ti--)
        {
            LL a=rand()%(n-2)+2;
            x[0]=quick_pow(a,tmp,n);
            for (i=1;i<=k;i++)
            {
                x[i]=x[i-1]*x[i-1]%n;
                if (x[i]==1 && x[i-1]!=1 && x[i-1]!=n-1) return false;
            }
            if (x[k]!=1) return false;
        }
        return true;
    }
}

int main ()
{
    LL l,r;
    cin>>l>>r;int ans=0;
    for (LL i=l;i<=r;i++) if(MillerRabin::solve(i)) ans++;
    printf("%d\n",ans);return 0;
}