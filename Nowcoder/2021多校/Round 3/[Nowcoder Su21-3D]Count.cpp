#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=10007;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,K,m,X[48],Y[48];

int cntbit[1048],C[1100][1100];

void init()
{
    C[0][0]=1;
    rep(i,1,1050)
    {
        C[i][0]=C[i][i]=1;
        rep(j,1,i-1) C[i][j]=add(C[i-1][j-1]+C[i-1][j]);
    }
    cntbit[0]=0;rep(i,1,500) cntbit[i]=cntbit[i>>1]+(i&1);
}

int cntx[48],cnty[48];
int dp[20][40][40][70];

int solve(bool f0,bool f1,int cntban)
{
    memset(dp[0],0,sizeof(dp[0]));dp[0][0][0][0]=1;int lim=(n+1)>>1,S=0;
    rep(p,1,lim)
    {
        memset(dp[p],0,sizeof(dp[p]));
        rep(i,0,S) rep(j,0,S) rep(k,0,S*2) if (dp[p-1][i][j][k])
        {
            if (p!=n+1-p)
                rep(sta1,cntx[p],1) rep(sta2,cntx[n+1-p],1) rep(sta3,cnty[p],1) rep(sta4,cnty[n+1-p],1)
                {
                    int nxti=i+sta1+sta2,nxtj=j+sta3+sta4,nxtk=k;
                    if (f0 && sta1 && sta3) nxtk++;
                    if (f0 && sta2 && sta4) nxtk++;
                    if (f1 && sta1 && sta4) nxtk++;
                    if (f1 && sta2 && sta3) nxtk++;
                    Add(dp[p][nxti][nxtj][nxtk],dp[p-1][i][j][k]);
                }
            else
                rep(sta1,cntx[p],1) rep(sta2,cnty[p],1)
                {
                    int nxti=i+sta1,nxtj=j+sta2,nxtk=k;
                    if ((f0 || f1) && sta1 && sta2) nxtk++;
                    Add(dp[p][nxti][nxtj][nxtk],dp[p-1][i][j][k]);
                }
        }
        if (p!=n+1-p) S+=2; else S++;
    }
    int res=0;
    rep(i,0,S) rep(j,0,S) rep(k,0,S*2) if (dp[lim][i][j][k] && i*j-k-cntban>=m)
    {
        int cc=n-i+n-j;
        if (cc&1) Sub(res,1ll*dp[lim][i][j][k]*C[i*j-k-cntban][m]%MOD);
        else Add(res,1ll*dp[lim][i][j][k]*C[i*j-k-cntban][m]%MOD);
    }
    return res;
}

int main ()
{
    scanf("%d%d%d",&n,&K,&m);rep(i,1,K) scanf("%d%d",X+i,Y+i);int ans=0;
    init();
    rep(Mask,0,(1<<K)-1)
    {
        m-=cntbit[Mask];
        rep(i,1,n) cntx[i]=cnty[i]=0;
        bool f0=false,f1=false;int res=0;
        rep(i,1,K) if (Mask&(1<<(i-1)))
        {
            cntx[X[i]]=cnty[Y[i]]=1;
            if (X[i]==Y[i]) f0=true;
            if (X[i]+Y[i]==n+1) f1=true;
        }
        res=solve(false,false,cntbit[Mask]);
        if (!f0) Sub(res,solve(true,false,cntbit[Mask]));
        if (!f1) Sub(res,solve(false,true,cntbit[Mask]));
        if (!f0 && !f1) Add(res,solve(true,true,cntbit[Mask]));
        if (cntbit[Mask]&1) Sub(ans,res); else Add(ans,res);
        m+=cntbit[Mask];
    }
    printf("%d\n",ans);return 0;
}