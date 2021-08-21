#include <bits/stdc++.h>
#define int long long
using namespace std;

const double eps=1e-10;

long double w,d;
long double t1,t2;
long double pi=acos(-1);

signed main ()
{
    int ca;scanf("%lld",&ca);
    while (ca--)
    {
        scanf("%Lf%Lf",&w,&d);
        if (w>d) swap(w,d);
        t1=w;t2=sqrt(w*w+d*d); 
        int ans=0,cnt;
        // 2: 0
        cnt=pi/t2;ans=max(ans,cnt*3);
        // 2: 1 
        if (pi>=t1) cnt=(pi-t1)/t2,ans=max(ans,cnt*3+2);
        // 2: 2
        if (pi>=t1*2) cnt=(pi-t1-t1)/t2,ans=max(ans,cnt*3+4);
        // 3: 0
        cnt=pi/t1;ans=max(ans,cnt*2);
        // 3: 1
        if (pi>=t2) cnt=(pi-t2)/t1,ans=max(ans,cnt*2+3);
        ans+=4;
        printf("%lld\n",ans);
    }
    return 0;
}