#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

int n;
LL a[1100048];

void poly_fwt(LL c[],int len)
{
    for (int clen=2;clen<=len;clen<<=1)
        for (int j=0;j<len;j+=clen)
            for (int k=j;k<j+(clen>>1);k++)
            {
                LL tmp1=c[k],tmp2=c[k+(clen>>1)];
                c[k]=tmp1+tmp2;c[k+(clen>>1)]=tmp1-tmp2;
            }
}

int main ()
{
    scanf("%d",&n);LL sum=0;
    rep(i,0,(1<<n)-1) scanf("%lld",a+i),sum+=a[i];
    poly_fwt(a,(1<<n));
    rep(i,0,(1<<n)-1) printf("%lld ",(sum-a[i])/2);
    puts("");return 0;
}