#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

int n,m;
int out1[48],out2[48],popcount[1100048],d[48];
int dp[1100048],dp2[1100048];LL c[2][1100048],DP[2][1100048];

LL ans1[1100048],ans2[1100048],ans3[1100048],ans4[1100048];

namespace FWT
{
    void poly_fwt(LL c[],int len,int fl)
    {
        int clen,j,k;
        for (clen=2;clen<=len;clen<<=1)
            for (j=0;j<len;j+=clen)
                for (k=j;k<j+(clen>>1);k++)
                {
                    LL tmp1=c[k],tmp2=c[k+(clen>>1)];
                    if (fl==1) c[k]=tmp1+tmp2; else c[k]=tmp1-tmp2;
                }
    }
    void poly_mul(LL A[],LL B[],LL C[],int n)
    {
        poly_fwt(A,1<<n,1);poly_fwt(B,1<<n,1);
        for (int i=0;i<=(1<<n)-1;i++) C[i]=A[i]*B[i];
        poly_fwt(C,1<<n,-1);
    }
}

int main ()
{
    scanf("%d%d",&n,&m);int x,y;
    popcount[0]=0;rep(i,1,(1<<20)-1) popcount[i]=popcount[i>>1]+(i&1);
    int N=(n+1)/2,M=n-N;
    rep(i,1,m)
    {
        scanf("%d%d",&x,&y);
        if (y<=N) out1[x]|=(1<<(y-1)); else out2[x]|=(1<<(y-N-1));
        if (x<=N) out1[y]|=(1<<(x-1)); else out2[y]|=(1<<(x-N-1));
    }
    rep(i,1,n) d[i]=popcount[out1[i]]+popcount[out2[i]];
    dp[0]=0;
    rep(Mask,1,(1<<N)-1)
    {
        int pt=1;while (~Mask&(1<<(pt-1))) pt++;
        dp[Mask]=(dp[Mask^(1<<(pt-1))]^(d[pt]&1)^(popcount[out1[pt]&Mask]&1));
    }
    dp2[0]=0;DP[0][0]=1;
    rep(Mask,1,(1<<M)-1)
    {
        int pt=1;while (~Mask&(1<<(pt-1))) pt++;
        dp2[Mask]=(dp2[Mask^(1<<(pt-1))]^(d[N+pt]&1)^(popcount[out2[N+pt]&Mask]&1));
        DP[dp2[Mask]][Mask]=1;
    }
    rep(Mask,0,(1<<N)-1)
    {
        int toMask=0;
        rep(i,1,N) if (Mask&(1<<(i-1))) toMask^=out2[i];
        c[dp[Mask]][toMask]++;
    }
    FWT::poly_fwt(c[0],1<<M,1);FWT::poly_fwt(c[1],1<<M,1);FWT::poly_fwt(DP[0],1<<M,1);FWT::poly_fwt(DP[1],1<<M,1);
    rep(i,0,(1<<M)-1) ans1[i]=c[0][i]*DP[0][i],ans2[i]=c[1][i]*DP[1][i],ans3[i]=c[0][i]*DP[1][i],ans4[i]=c[1][i]*DP[0][i];
    FWT::poly_fwt(ans1,1<<M,-1);FWT::poly_fwt(ans2,1<<M,-1);FWT::poly_fwt(ans3,1<<M,-1);FWT::poly_fwt(ans4,1<<M,-1);
    LL ans=0;
    rep(Mask,0,(1<<M)-1) if (~popcount[Mask]&1) ans+=ans1[Mask]+ans2[Mask]; else ans+=ans3[Mask]+ans4[Mask];
    printf("%lld\n",ans);return 0;
}