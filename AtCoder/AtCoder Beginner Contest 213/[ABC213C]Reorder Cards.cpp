#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;

int n,X[MAXN+48],Y[MAXN+48];
int val[MAXN+48],tot;

int main ()
{
    int x,y;scanf("%d%d",&x,&y);scanf("%d",&n);
    rep(i,1,n) scanf("%d%d",X+i,Y+i);
    rep(i,1,n) val[i]=X[i];tot=n;
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    rep(i,1,n) X[i]=lower_bound(val+1,val+tot+1,X[i])-val;
    rep(i,1,n) val[i]=Y[i];tot=n;
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    rep(i,1,n) Y[i]=lower_bound(val+1,val+tot+1,Y[i])-val;
    rep(i,1,n) printf("%d %d\n",X[i],Y[i]);
    return 0;
}