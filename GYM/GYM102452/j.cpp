#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

string L,R;int m,n;

int addm(int x) {if (x>=m) x-=m;return x;}
int subm(int x) {if (x<0) x+=m;return x;}

int dp[5010][61][61][2],pw[5010];

int solve(string lim)
{
    rep(i,0,n) rep(j,0,m-1) rep(k,0,m-1) rep(sta,0,1) dp[i][j][k][sta]=0;
    dp[0][0][0][0]=1;
    rep(i,0,n-1) rep(j,0,m-1) rep(k,0,m-1)
    {
        if (dp[i][j][k][0])
        {
            int w=lim[i]-'0';
            rep(d,0,w-1)
                Add(dp[i+1][addm(j+d%m)][subm(addm(k+j*d%m)-d*pw[n-i-1]%m)][1],dp[i][j][k][0]);
            Add(dp[i+1][addm(j+w%m)][subm(addm(k+j*w%m)-w*pw[n-i-1]%m)][0],dp[i][j][k][0]);
        }
        if (dp[i][j][k][1])
        {
            rep(d,0,9)
                Add(dp[i+1][addm(j+d%m)][subm(addm(k+j*d%m)-d*pw[n-i-1]%m)][1],dp[i][j][k][1]);
        }
    }
    int res=0;
    rep(j,0,m-1) Add(res,dp[n][j][0][0]),Add(res,dp[n][j][0][1]);
    return res;
}

bool check(string s)
{
    int res1=0,l=int(s.size());
    rep(i,0,l-1) res1=(res1*10+(s[i]-'0'))%m;
    int res2=0;
    rep(i,0,l-2) rep(j,i+1,l-1) res2=(res2+(s[i]-'0')*(s[j]-'0')%m)%m;
    return res1==res2;
}

int main ()
{
    ios::sync_with_stdio(false);
    int ca;cin>>ca;
    while (ca--)
    {
        cin>>L>>R>>m;n=int(R.size());
        int delta=n-int(L.size());while (delta--) L="0"+L;
        pw[0]=1;rep(i,1,n) pw[i]=1ll*pw[i-1]*10%m;
        int ans=sub(solve(R)-solve(L));
        if (check(L)) Add(ans,1);
        printf("%d\n",ans);
    }
    return 0;
}