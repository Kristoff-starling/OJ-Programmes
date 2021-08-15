#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=3000;
const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n;
int a[MAXN+48],b[MAXN+48],pos[MAXN+48];
bool mark[MAXN+48];
int A[MAXN+48],tot;
int cnt[MAXN+48][MAXN+48],dp[MAXN+48][MAXN+48];

int f[MAXN+48][MAXN+48][4][3];
int fac[MAXN+48];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);rep(i,1,n) scanf("%d",b+i);
    rep(i,1,n) pos[a[i]]=i;
    memset(mark,0,sizeof(mark));tot=0;
    rep(i,1,n) if (!mark[i])
    {
        int cur=i;++tot;A[tot]=0;
        do
        {
            mark[cur]=1;
            A[tot]++;
            cur=pos[b[cur]];
        }
        while (!mark[cur]);
    }
    f[1][0][0][0]=1;f[1][1][3][1]=1;f[1][1][3][2]=2;
    rep(i,2,n) f[i][i-1][1][0]=1,f[i][i-1][2][0]=i-1;
    rep(i,1,n-1) rep(j,0,i) rep(sta,0,3)
    {
        // 0
        Add(f[i+1][j][sta][0],f[i][j][sta][0]);
        Add(f[i+1][j+1][sta][1],f[i][j][sta][0]);
        Add(f[i+1][j+1][sta][2],add(f[i][j][sta][0]+f[i][j][sta][0]));
        // 1
        Add(f[i+1][j+1][sta][1],f[i][j][sta][1]);
        Add(f[i+1][j+1][sta][2],f[i][j][sta][1]);
        // 2
        Add(f[i+1][j][sta][0],f[i][j][sta][2]);
        Add(f[i+1][j+1][sta][2],f[i][j][sta][2]);
    }
    rep(i,0,n) rep(j,0,i)
    {
        Add(cnt[i][j],f[i][j][3][0]);
        Add(cnt[i][j],f[i][j][2][1]);
        Add(cnt[i][j],f[i][j][1][2]);
        Add(cnt[i][j],add(f[i][j][0][0]+f[i][j][0][2]));
    }
    rep(i,0,n) cnt[i][0]=1;
    cnt[1][1]=1;rep(i,2,n) cnt[i][i]=2;
    dp[0][0]=1;
    rep(i,0,tot-1) rep(j,0,n)
        rep(nxt,0,A[i+1]) Add(dp[i+1][j+nxt],1ll*dp[i][j]*cnt[A[i+1]][nxt]%MOD);
    fac[0]=1;rep(i,1,n) fac[i]=1ll*fac[i-1]*i%MOD;int ans=0;
    rep(i,0,n)
    {
        int cur=1ll*dp[tot][i]*fac[n-i]%MOD;
        if (i&1) Sub(ans,cur); else Add(ans,cur);
    }
    printf("%d\n",ans);
    return 0;
}