#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,m;
int a[1048][1048];
int r[1048],c[1048];

int main ()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
    rep(i,1,n)
    {
        r[i]=a[i][1];
        rep(j,2,m) r[i]=min(r[i], a[i][j]);
    }
    rep(j,1,m)
    {
        c[j]=a[1][j];
        rep(i,2,n) c[j]=min(c[j],a[i][j]);
    }
    int ans=0;
    rep(i,1,n) rep(j,1,m) if (a[i][j] == r[i] && a[i][j] == c[j]) ans++;
    printf("%d\n",ans);return 0;
}