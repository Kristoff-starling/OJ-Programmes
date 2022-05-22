#include <bits/stdc++.h>
using namespace std;

int main ()
{
    long long ca,k;scanf("%lld",&ca);
    while (ca--)
    {
        scanf("%lld",&k);
        if (k==1) puts("0");
        else if (k==2) puts("1");
        else
        {
            long long ans=1,sum=2,pw=1;
            while (sum<k)
            {
                pw<<=1;
                ans++;
                sum+=pw*ans;
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}