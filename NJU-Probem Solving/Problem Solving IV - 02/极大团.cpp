#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);++i)
using namespace std;

int n,m;
int v[48];

int main ()
{
    scanf("%d%d",&n,&m);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),x--,y--,v[x]|=(1<<y),v[y]|=(1<<x);
    rep(i,0,n-1) v[i]|=(1<<i);
    int ans=0;
    rep(Mask,1,(1<<n)-1)
    {
        bool f=true;
        rep(i,0,n-1)
        {
            if ((Mask>>i&1) && (v[i]&Mask)!=Mask) f=false;
            if (!(Mask>>i&1) && (v[i]&Mask)==Mask) f=false;
        }
        if (f) ans++;
    }
    printf("%d\n",ans);
    return 0;
}