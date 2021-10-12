#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e6;

int n,a[MAXN+48],val[MAXN+48];
map<int,int> M;

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i),val[i]=a[i];
    sort(val+1,val+n+1);
    rep(i,1,n)
    {
        int w=a[i];
        a[i]=(lower_bound(val+1,val+n+1,w)-val)+M[w];
        M[w]++;
    }
    int maxn=0,ans=0;
    rep(i,1,n)
    {
        maxn=max(maxn,a[i]);
        if (maxn<=i) ans++;
    }
    printf("%d\n",ans);return 0;
}