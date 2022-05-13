#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;

int n,q,a[MAXN+48],pos[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&q);int x;
    rep(i,1,n) a[i]=pos[i]=i;
    while (q--)
    {
        scanf("%d",&x);
        int cur=pos[x],nxt=(cur==n?n-1:cur+1),xx=a[nxt];
        swap(pos[x],pos[xx]);swap(a[cur],a[nxt]);
    }
    rep(i,1,n-1) printf("%d ",a[i]);
    printf("%d\n",a[n]);
    return 0;
}