#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

int n,a[1100048];
LL b[1100048],c[1100048];

void solve(int l,int r)
{
    if (l==r) {b[l]=0;c[l]=a[l];return;}
    int mid=(l+r)>>1,len=r-mid;
    solve(l,mid);solve(mid+1,r);
    rep(i,l,mid)
    {
        LL b0=b[i]+b[i+len],c0=c[i]+c[i+len];
        LL b1=b[i]+c[i+len],c1=c[i]+b[i+len];
        b[i]=b0;c[i]=c0;b[i+len]=b1;c[i+len]=c1;
    }
}

int main ()
{
    scanf("%d",&n);rep(i,0,(1<<n)-1) scanf("%d",a+i);
    solve(0,(1<<n)-1);
    rep(i,0,(1<<n)-2) printf("%lld ",b[i]);
    printf("%lld\n",b[(1<<n)-1]);return 0;
}