#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int ca,n,m;scanf("%d",&ca);
    for (int t=1;t<=ca;t++)
    {
        scanf("%d%d",&n,&m);
        printf("Case #%d: ",t);
        if (n>m) swap(n,m);
        if (n==1 && m==1) puts("1");
        else if (n==1 && m>1) puts("2");
        else if (n==2) printf("%d\n",2*m);
        else printf("%d\n", 2*n+2*m-4);
    }
    return 0;
}