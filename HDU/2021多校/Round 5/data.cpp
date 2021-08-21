#include <bits/stdc++.h>
using namespace std;

int n=1e6;

int main ()
{
    freopen ("a.in","w",stdout);
    int T=5;
    cout<<T<<endl;
    while (T--)
    {
        printf("%d\n",n);
        for (int i=0;i<=n-1;i++) printf("%d ",i);
        puts("");
    }
    return 0;
}