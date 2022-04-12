#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
#define REP(i,a,b) for (int i=(a);i>=(b);i--)
using namespace std;

const int MAXN=2e5;

int n,X,Y,a[MAXN+48],nxt[MAXN+48][5];

int main ()
{
    scanf("%d%d%d",&n,&X,&Y);
    rep(i,1,n)
    {
        scanf("%d",a+i);
        if (a[i]>X || a[i]<Y) a[i]=0;
        else if (a[i]==X) a[i]=1;
        else if (Y<a[i] && a[i]<X) a[i]=2;
        else if (a[i]==Y) a[i]=3;
        else assert(0);
    }
    rep(i,0,3) nxt[n+1][i]=n+1;
    REP(i,n,1)
    {
        rep(j,0,3) nxt[i][j]=nxt[i+1][j];
        nxt[i][a[i]]=i;
    }
    long long ans=0;
    rep(i,1,n)
    {
        int lim=nxt[i][0],r;
        if (X!=Y) r=max(nxt[i][1],nxt[i][3]); else r=nxt[i][1];
        if (r>=lim) continue;
        ans+=lim-r; 
    }
    printf("%lld\n",ans);
    return 0;
}