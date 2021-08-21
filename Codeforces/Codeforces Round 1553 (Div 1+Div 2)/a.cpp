#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int ca;scanf("%d",&ca);int n;
    while (ca--)
    {
        scanf("%d",&n);
        int ans=n/10;
        if (n%10==9) ans++;
        printf("%d\n",ans);
    }
    return 0;
}