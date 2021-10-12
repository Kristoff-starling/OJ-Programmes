#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;
const int MAXN=5000;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,m;
int sum[MAXN+48][MAXN+48];
int dp[MAXN+48][MAXN+48];

int calc(int j,int l,int r) {int res=sum[r][j];if (l>0) Sub(res,sum[l-1][j]);return res;}

int main ()
{
    scanf("%d%d",&n,&m);
    dp[0][0]=1;sum[0][0]=1;
    rep(i,1,n) rep(j,i,n)
    {
        int L=max(i-m,0),R=min(j-i,i);
        if (L<=R) dp[i][j]=calc(j-i,L,R);
        sum[i][j]=add(sum[i-1][j]+dp[i][j]);
    }
    rep(i,1,n) printf("%d\n",dp[i][n]);
    return 0;
}