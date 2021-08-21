#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

int n,p;

template<typename T> T add(T x) {if (x>=p) x-=p;return x;}
template<typename T> T sub(T x) {if (x<0) x+=p;return x;}
template<typename T> void Add(T &x,T y) {x=add(x+y);}
template<typename T> void Sub(T &x,T y) {x=sub(x-y);}

LL C[501][501],f[501][501],g[501][501][501],h[501][501];

int main ()
{
    scanf("%d%d",&n,&p);
    if (n==1) {puts("0");return 0;}
    if (n==2) {puts("1");return 0;}
    C[0][0]=1;
    rep(i,1,n)
    {
        C[i][0]=C[i][i]=1;
        rep(j,1,i-1) C[i][j]=add(C[i-1][j-1]+C[i-1][j]);
    }
    rep(i,0,n) g[0][i][0]=1;
    rep(k,1,n) rep(i,1,n) rep(j,0,i)
    {
        Add(g[k][i][j],1ll*i*g[k-1][i][j]%p);
        if (j) Add(g[k][i][j],1ll*j*g[k-1][i-1][j-1]%p);
    }
    f[1][1]=1;f[2][2]=1;h[1][1]=0;h[2][2]=1;
    rep(i,1,n) rep(j,1,i) if (f[i][j])
    {
        if (i>=3) Add(h[i][j],2ll*f[i][j]%p);
        rep(k,max(j,2),n) if (i+k<=n)
        {
            Add(f[i+k][k],1ll*f[i][j]*g[k][i][j]%p*C[i+k][i]%p);
            Add(h[i+k][k],1ll*h[i][j]*g[k][i][j]%p*C[i+k][i]%p);
        }
    }
    LL ans=0;rep(i,2,n) Add(ans,h[n][i]);
    printf("%lld\n",ans);return 0;
}