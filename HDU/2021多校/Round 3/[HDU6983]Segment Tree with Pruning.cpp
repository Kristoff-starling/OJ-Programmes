#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

LL n,k,ans;

void solve(LL len,LL cnt1,LL cnt2)
{
    ans+=cnt1+cnt2;
    if (len+1<=k) return;
    if (len==1)
    {
        ans+=2ll*cnt2;
        return;
    }
    LL newlen=len>>1;LL tocnt1=0,tocnt2=0;
    if (len>k)
    {
        tocnt1+=cnt1;
        if (len-newlen==newlen) tocnt1+=cnt1; else tocnt2+=cnt1;
    }
    if ((len+1)&1) tocnt1+=cnt2,tocnt2+=cnt2; else tocnt2+=2ll*cnt2;
    solve(newlen,tocnt1,tocnt2);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%lld%lld",&n,&k);
        ans=0;solve(n,1,0);
        printf("%lld\n",ans);
    }
    return 0;
}