#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;

int n,m;

int dp[1000048],cnt[1000048],b[1000048];
int pw[1000048];

int ga[20][20];

int main ()
{
    scanf("%d%d",&n,&m);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),ga[x][y]=ga[y][x]=1;
    rep(i,1,n) dp[1<<(i-1)]=1;
    pw[0]=1;rep(i,1,n*n) pw[i]=(pw[i-1]+pw[i-1])%MOD;
    rep(Mask,1,(1<<n)-1)
    {
        cnt[Mask]=0;
        rep(i,1,n) rep(j,i+1,n) if (Mask&(1<<(i-1)) && Mask&(1<<(j-1)) && ga[i][j]) cnt[Mask]++;
    }
    b[0]=0;rep(i,1,(1<<n)-1) b[i]=b[i>>1]+(i&1);
    rep(Mask,2,(1<<n)-1) if (b[Mask]>1)
    {
        dp[Mask]=pw[cnt[Mask]];
        int lo=0;while (!(Mask&(1<<lo))) lo++;
        for (int x=((Mask-1)&Mask);x;x=(x-1)&Mask) if (x&(1<<lo)) dp[Mask]=(dp[Mask]-1ll*dp[x]*pw[cnt[Mask^x]]%MOD+MOD)%MOD;
    }    
    rep(i,2,n)
    {
        int ans=0;
        rep(Mask,1,(1<<n)-1)
            if (Mask&1 && Mask&(1<<(i-1))) ans=(ans+1ll*dp[Mask]*pw[cnt[((1<<n)-1)^Mask]]%MOD)%MOD;
        printf("%d\n",ans);
    }
    return 0;

}