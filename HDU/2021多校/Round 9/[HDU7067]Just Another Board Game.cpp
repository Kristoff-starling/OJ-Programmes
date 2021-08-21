#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=1e5;

int n,m;LL k;
int a[MAXN+48];

int maxr[MAXN+48],minc[MAXN+48];
int maxn,minn;

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%lld",&n,&m,&k);
        rep(i,1,n*m) scanf("%d",a+i);
        rep(i,1,n) maxr[i]=-1;rep(i,1,m) minc[i]=1e9+1;
        rep(i,1,n) rep(j,1,m)
        {
            int id=(i-1)*m+j;
            maxr[i]=max(maxr[i],a[id]);
            minc[j]=min(minc[j],a[id]);
        }
        minn=maxr[1];rep(i,2,n) minn=min(minn,maxr[i]);
        maxn=minc[1];rep(i,2,m) maxn=max(maxn,minc[i]);
        if (k==1)
        {
            printf("%d\n",maxr[1]);
            continue;
        }
        if (k&1) printf("%d\n",max(a[1],minn)); else printf("%d\n",max(a[1],maxn));
    }
    return 0;
}