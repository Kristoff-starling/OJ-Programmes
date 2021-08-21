#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const int MAXN=5000;
const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,m;
char s1[MAXN+48],s2[MAXN+48];

int fac[MAXN*2+48],ifac[MAXN*2+48];

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

void init()
{
    fac[0]=1;rep(i,1,MAXN*2) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[MAXN*2]=quick_pow(fac[MAXN*2],MOD-2);
    REP(i,MAXN*2-1,0) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int C(int x,int y)
{
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

int dp[MAXN+48][MAXN+48];

int main ()
{
    init();scanf("%s%s",s1+1,s2+1);n=strlen(s1+1);m=strlen(s2+1);
    rep(i,0,m) dp[0][i]=1;rep(i,1,n) dp[i][0]=1;
    rep(i,1,n) rep(j,1,m)
    {
        dp[i][j]=add(dp[i][j-1]+dp[i-1][j]);
        if (s1[i]!=s2[j]) Sub(dp[i][j],dp[i-1][j-1]);
    }
    int ans=0;
    rep(i,1,n) rep(j,1,m) if (s1[i]<s2[j]) Add(ans,1ll*dp[i-1][j-1]*C(n-i+m-j,m-j)%MOD);
    printf("%d\n",ans);return 0;
}