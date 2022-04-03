#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n;

void pr(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    printf("%d %d %d %d %d %d %d %d\n", a1, a2, a3, a4, a5, a6, a7, a8);
}

int main ()
{
    int ca;scanf("%d",&ca);
    rep(t,1,ca)
    {
        scanf("%d",&n);
        printf("Case #%d:\nYES\n", t);
        if (n==1) {puts("1 1 0 0 0 1 0 0");continue;}
        rep(i,1,n)
        {
            pr(i, i, i, i-1, 0, i, i-1, 1);
            rep(j,i+1,n)
                pr(i, j, i, j-1, 1, i, j-1, 0);
        }
    }
    return 0;
}