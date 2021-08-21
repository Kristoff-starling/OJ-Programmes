#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=2e5;

int n;
LL a[MAXN+48],b[MAXN+48];

LL myabs(LL x) {return x>0?x:-x;}
LL mygcd(LL x,LL y) {return y==0?x:mygcd(y,x%y);}

LL ST[MAXN+48][21];
int Log[MAXN+48];

void init_ST()
{
    rep(i,1,n-1) ST[i][0]=b[i];
    rep(j,1,20) rep(i,1,n-1)
    {
        ST[i][j]=ST[i][j-1];
        if (i+(1<<(j-1))<=n-1) ST[i][j]=mygcd(ST[i][j],ST[i+(1<<(j-1))][j-1]);
    }
    Log[1]=0;rep(i,2,n) Log[i]=Log[i>>1]+1;
}

LL query_ST(int l,int r)
{
    int k=r-l+1;
    return mygcd(ST[l][Log[k]],ST[r-(1<<Log[k])+1][Log[k]]);
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%lld",a+i);
        if (n==1) {printf("1\n");continue;}
        rep(i,1,n-1) b[i]=myabs(a[i+1]-a[i]);
        init_ST();int ans=1;int r=1;LL g=b[1];
        if (g!=1) while (r<n-1 && mygcd(g,b[r+1])!=1) r++,g=mygcd(g,b[r]);
        if (g!=1) ans=max(ans,r+1);
        rep(i,2,n-1)
        {
            if (r<i) r=i,g=b[i]; else g=query_ST(i,r);
            if (g==1) continue;
            while (r<n-1 && mygcd(g,b[r+1])!=1) r++,g=mygcd(g,b[r]);
            ans=max(ans,r-i+2);
        }
        printf("%d\n",ans);
    }
    return 0;
}