#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

int cnt[48];

int main ()
{
    int n,x,ca;bool flag;scanf("%d",&ca);
    while (ca--)
    {
        rep(i,0,30) cnt[i]=0;
        scanf("%d",&n);
        while (n--)
        {
            scanf("%d",&x);
            rep(i,0,30) if (x>>i&1) cnt[i]++;
        }
        for (;;)
        {
            flag=false;
            REP(i,30,1) if (cnt[i]>cnt[i-1])
            {
                flag=true;
                int t=(cnt[i]-cnt[i-1]+2)/3;
                cnt[i]-=t;cnt[i-1]+=t*2;
            }
            if (!flag) break;
        }
        printf("%d\n",cnt[0]);
    }
    return 0;
}