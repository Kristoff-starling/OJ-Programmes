#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
using namespace std;

const int MAXN=2e5;

int n;
LL a[MAXN+48],b[MAXN+48],c[MAXN+48];
LL pb[MAXN+48],pc[MAXN+48],sb[MAXN+48],sc[MAXN+48];
int pcntpos[MAXN+48],pcntneg[MAXN+48],scntpos[MAXN+48],scntneg[MAXN+48];
LL bpos[MAXN+48],bneg[MAXN+48],cpos[MAXN+48],cneg[MAXN+48];

template<typename T> T myabs(T x) {return (x>=0)?x:-x;}

int bsearch(LL val,LL A[])
{
    if (A[n]<=val) return n+1;
    int l=1,r=n,res,mid;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (A[mid]>val) res=mid,r=mid-1; else l=mid+1;
    }
    return res;
}

int bsearch2(LL val,LL A[])
{
    if (A[n]<val) return n+1;
    int l=1,r=n,res,mid;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (A[mid]>=val) res=mid,r=mid-1; else l=mid+1;
    }
    return res;
}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%lld",a+i);
    LL baseans=0;rep(i,1,n) baseans+=myabs(a[i]);
    pcntpos[0]=pcntneg[0]=0;
    rep(i,1,n)
    {
        pcntpos[i]=pcntpos[i-1];pcntneg[i]=pcntneg[i-1];
        if (a[i]>=0) pcntpos[i]++; else pcntneg[i]++;
    }
    scntpos[n+1]=scntneg[n+1]=0;
    REP(i,n,1)
    {
        scntpos[i]=scntpos[i+1];scntneg[i]=scntneg[i+1];
        if (a[i]>=0) scntpos[i]++; else scntneg[i]++;
    }
    rep(i,1,n)
    {
        b[i]=c[i]=0;
        if (a[i+1]>a[i]) b[i]=a[i+1]-a[i]; else c[i]=a[i]-a[i+1];
    }
    pb[1]=pc[1]=0;rep(i,2,n) pb[i]=pb[i-1]+b[i-1],pc[i]=pc[i-1]+c[i-1];
    bneg[0]=0;
    rep(i,1,n)
    {
        bneg[i]=bneg[i-1];
        if (a[i]>=0) bneg[i]+=pb[i]*2;
    }
    bpos[n+1]=0;
    REP(i,n,1)
    {
        bpos[i]=bpos[i+1];
        if (a[i]<0) bpos[i]+=pb[i]*2;
    }
    cpos[0]=0;
    rep(i,1,n)
    {
        cpos[i]=cpos[i-1];
        if (a[i]<0) cpos[i]+=pc[i]*2;
    }
    cneg[n+1]=0;
    REP(i,n,1)
    {
        cneg[i]=cneg[i+1];
        if (a[i]>=0) cneg[i]+=pc[i]*2;
    }
    LL ans=5e18;
    rep(i,1,n)
    {
        if (i!=1 && pb[i]==pb[i-1]) continue;
        LL ib=-pb[i],ic=a[1]-ib;int pos;
        if (ic<=0) pos=1; else pos=bsearch(ic,pc);
        LL curans=baseans;
        curans+=bpos[i];curans-=pb[i]*2*scntneg[i];
        if (i>1)
        {
            curans+=pb[i]*2*pcntpos[i-1];
            curans-=bneg[i-1];
        }
        if (pos>1)
        {
            curans+=ic*2*pcntneg[pos-1];
            curans-=cpos[pos-1];
        }
        if (pos<=n)
        {
            curans+=cneg[pos];
            curans-=(ic)*2*scntpos[pos];
        }
        ans=min(ans,curans);
    }
    rep(i,1,n)
    {
        if (i!=1 && pc[i]==pc[i+1]) continue;
        LL ic=pc[i],ib=a[1]-ic;int pos;
        if (ib>=0) pos=1; else pos=bsearch2(-ib,pb);
        LL curans=baseans;
        curans+=ic*2*pcntneg[i];curans-=cpos[i];
        if (i<=n-1)
        {
            curans+=cneg[i+1];
            curans-=ic*2*scntpos[i+1];
        }
        if (pos>1)
        {
            curans+=(-ib)*2*pcntpos[pos-1];
            curans-=bneg[pos-1];
        }
        if (pos<=n)
        {
            curans+=bpos[pos];
            curans-=(-ib)*2*scntneg[pos];
        }
        ans=min(ans,curans);
    }
    printf("%lld\n",ans);
    return 0;
}