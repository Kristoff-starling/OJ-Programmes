#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int a[1048][1048];

int main ()
{
    int n,m;scanf("%d%d",&n,&m);int bit;
    rep(i,1,n) rep(j,1,m)
    {
        if (j%4==1 || j%4==2) bit=0; else bit=1;
        if (i&1) bit^=1;
        a[i][j]=bit;
    }
    rep(i,1,n)
    {
        rep(j,1,m) printf("%d",a[i][j]);
        puts("");
    }
    return 0;
}