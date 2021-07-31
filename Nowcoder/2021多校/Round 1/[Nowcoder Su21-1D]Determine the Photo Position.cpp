#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=2000;

int n,m;
char s[2001][2001];int sum[2001][2001];

int main ()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%s",s[i]+1);
    rep(i,1,n)
    {
        sum[i][0]=0;
        rep(j,1,n) sum[i][j]=sum[i][j-1]+(s[i][j]=='1');
    }
    int ans=0;
    rep(i,1,n) rep(j,1,n-m+1)
        if (sum[i][j+m-1]-sum[i][j-1]==0) ans++;
    printf("%d\n",ans);return 0;
}