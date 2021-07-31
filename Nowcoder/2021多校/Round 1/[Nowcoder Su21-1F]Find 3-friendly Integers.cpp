#include <bits/stdc++.h>
#define LL long long
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

int b[48];
LL dp[20][2][8];

void doit(LL lim) {REP(i,19,1) b[i]=lim%10,lim/=10;}

LL solve(LL lim)
{
    doit(lim);memset(dp,0,sizeof(dp));
    dp[0][0][0]=1;
    rep(i,0,18)
    {
        rep(sta,0,7) rep(nxt,0,b[i+1]) if (dp[i][0][sta])
        {
            int tolim=((nxt==b[i+1])?0:1),type=nxt%3;
            if ((nxt==0 && sta==0) || sta==1) {dp[i+1][tolim][sta]+=dp[i][0][sta];continue;}
            if (!type || (type==1 && sta>=4) || (type==2 && sta&2)) {dp[i+1][tolim][1]+=dp[i][0][sta];continue;}
            if (type==1)
            {
                int tosta=((sta&2)?6:2);
                dp[i+1][tolim][tosta]+=dp[i][0][sta];
            }
            else
            {
                int tosta=((sta&4)?6:4);
                dp[i+1][tolim][tosta]+=dp[i][0][sta];
            }
        }
        rep(sta,0,7) rep(nxt,0,9) if (dp[i][1][sta])
        {
            int type=nxt%3;
            if ((nxt==0 && sta==0) || sta==1) {dp[i+1][1][sta]+=dp[i][1][sta];continue;}
            if (!type || (type==1 && sta>=4) || (type==2 && sta&2)) {dp[i+1][1][1]+=dp[i][1][sta];continue;}
            if (type==1)
            {
                int tosta=((sta&2)?6:2);
                dp[i+1][1][tosta]+=dp[i][1][sta];
            }
            else
            {
                int tosta=((sta&4)?6:4);
                dp[i+1][1][tosta]+=dp[i][1][sta];
            }
        }
    }
    return dp[19][0][1]+dp[19][1][1];
}

int main ()
{
#ifndef ONLINE_JUDGE
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
#endif
    int ca;scanf("%d",&ca);
    LL L,R;
    while (ca--)
    {
        scanf("%lld%lld",&L,&R);
        printf("%lld\n",solve(R)-solve(L-1));
    }
    return 0; 
}