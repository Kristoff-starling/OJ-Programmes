#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MOD=998244353;

int n,k,D;

int C[148][148];

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int quick_pow(int x,int y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%MOD;
        x=1ll*x*x%MOD;y>>=1;
    }
    return res;
}

void init_C()
{
    C[0][0]=1;
    rep(i,1,50)
    {
        C[i][0]=C[i][i]=1;
        rep(j,1,i-1) C[i][j]=add(C[i-1][j-1]+C[i-1][j]);
    }
}

int dp[51][51*51];

int cc[2501][51];

void init_dp()
{
    int inv[100];
    rep(i,1,50) inv[i]=quick_pow(i,MOD-2);
    rep(i,0,n*k) rep(j,0,k-1)
    {
        if (D+k*n-i>=j)
        {
            if (!j) cc[i][j]=1; else
            {
                cc[i][j]=1;
                REP(m,D+k*n-i,D+k*n-i-j+1) cc[i][j]=1ll*cc[i][j]*m%MOD;
                rep(m,1,j) cc[i][j]=1ll*cc[i][j]*inv[m]%MOD;
            }
        }
    }
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    rep(i,1,n) rep(j,0,i*(k-1)) rep(cur,0,k-1) if (j-cur>=0) Add(dp[i][j],1ll*dp[i-1][j-cur]*cc[j-cur][cur]%MOD);
}

int main ()
{
    scanf("%d%d%d",&n,&k,&D);
    if (!k) {printf("%d\n",quick_pow(n,D));return 0;}
    init_C();init_dp();int ans=0;
    rep(i,0,n)
    {
        int res=0;
        rep(j,0,i*(k-1)) Add(res,1ll*C[n][i]*dp[i][j]%MOD*quick_pow(n-i,D+k*n-j)%MOD);
        if (i&1) Sub(ans,res); else Add(ans,res);
    }
    rep(i,D+1,D+k*n) ans=1ll*ans*quick_pow(i,MOD-2)%MOD;
    printf("%d\n",ans);
    return 0;
}