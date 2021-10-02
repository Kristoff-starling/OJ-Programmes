#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;
const int MAXN=1e5;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}

int a[MAXN+48],n;
int dp[MAXN+48][10];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
    memset(dp,0,sizeof(dp));dp[1][a[1]]=1;
    rep(i,1,n-1) rep(num,0,9)
    {
        Add(dp[i+1][(num+a[i+1])%10],dp[i][num]);
        Add(dp[i+1][(num*a[i+1])%10],dp[i][num]);
    }
    rep(i,0,9) printf("%d\n",dp[n][i]);
    return 0;
}