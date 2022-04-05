#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

const int MAXN=1e5;

int n,X[MAXN+48],Y[MAXN+48];
int val[MAXN+48],tot,t1,t2;

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        int t,x;scanf("%d",&n);
        rep(i,1,n) scanf("%d%d",&t,&x),X[i]=t+x,Y[i]=t-x;
        tot=0;rep(i,1,n) val[++tot]=X[i];
        sort(val+1,val+tot+1);t1=tot=unique(val+1,val+tot+1)-(val+1);
        rep(i,1,n) X[i]=lower_bound(val+1,val+tot+1,X[i])-val;
        tot=0;rep(i,1,n) val[++tot]=Y[i];
        sort(val+1,val+tot+1);t2=tot=unique(val+1,val+tot+1)-(val+1);
        rep(i,1,n) Y[i]=lower_bound(val+1,val+tot+1,Y[i])-val;
    }
    return 0;
}