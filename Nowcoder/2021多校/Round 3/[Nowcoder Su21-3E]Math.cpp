#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define pb push_back
using namespace std;

const LL LINF=1e18;

vector<LL> v[1000048];

void init()
{
    rep(i,2,1000000)
    {
        v[i].pb(i);v[i].pb(1ll*i*i*i);
        for (;;)
        {
            int sz=int(v[i].size());
            __int128 tmp=1ll*i*i;tmp=tmp*v[i][sz-1];tmp=tmp-v[i][sz-2];
            if (tmp>(__int128)LINF) break;
            v[i].pb((LL)tmp);
        }
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    init();int lim=int(v[2].size())-2;LL n;
    while (ca--)
    {
        scanf("%lld",&n);LL ans=1;
        rep(i,0,lim)
        {
            int L=2,R=1000000,mid,res=1;
            while (L<=R)
            {
                mid=(L+R)>>1;
                if (int(v[mid].size())-2<i || v[mid][i+1]>n) R=mid-1; else res=mid,L=mid+1;
            }
            ans+=res-1;
        }
        printf("%lld\n",ans);
    }
    return 0;
}