#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

const int MAXN=1e5;
const int MOD=1e9+7;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

int n;
string s[MAXN+48];

int dp[MAXN+48][8];

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) cin>>s[i];
        rep(i,1,n) rep(j,0,7) dp[i][j]=0;
        dp[1][4]=1;
        rep(i,1,n-1) rep(Mask,0,7) if (dp[i][Mask])
        {
            //last
            if (!(Mask&4)) {Add(dp[i+1][Mask<<1],dp[i][Mask]);continue;}
            //current
            if (!(Mask&2)) Add(dp[i+1][((Mask^4)<<1)|4],dp[i][Mask]);
            //next
            if ((!(Mask&1)) & ((Mask&2) || s[i+1]!=s[i])) Add(dp[i+1][((Mask^4)<<1)|2],dp[i][Mask]);
        }
        printf("%d\n",add(dp[n][4]+dp[n][2]));
    }
    return 0;
}