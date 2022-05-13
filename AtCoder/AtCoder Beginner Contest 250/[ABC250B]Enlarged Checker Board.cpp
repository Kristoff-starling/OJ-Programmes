#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int main ()
{
    int n,a,b;scanf("%d%d%d",&n,&a,&b);
    rep(i,0,n*a-1)
    {
        rep(j,0,n*b-1)
            if ((i/a+j/b)&1) printf("#"); else printf(".");
        puts("");
    }
    return 0;
}