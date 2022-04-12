#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=2e5;
const int MOD=998244353;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
int a[MAXN+48],b[MAXN+48];

int n;

namespace DSU
{
    int pre[MAXN+48],sz[MAXN+48];
    void init() {rep(i,1,n) pre[i]=i,sz[i]=1;}
    int find_anc(int x) {if (x!=pre[x]) pre[x]=find_anc(pre[x]);return pre[x];}
    void update(int x,int y)
    {
        x=find_anc(x);y=find_anc(y);
        if (x!=y) sz[y]+=sz[x],pre[x]=y;
    }
    int querysz(int x) {if (x==find_anc(x)) return sz[x]; else return 0;}
}

int dp[MAXN+48][2],DP[MAXN+48][2];

int main ()
{
    scanf("%d",&n);DSU::init();
    rep(i,1,n) scanf("%d",a+i);rep(i,1,n) scanf("%d",b+i);
    rep(i,1,n) DSU::update(a[i],b[i]);
    dp[1][0]=1;dp[1][1]=1;DP[1][0]=0;DP[1][1]=1;
    rep(i,1,n-1)
    {
        dp[i+1][0]=dp[i][1];dp[i+1][1]=add(dp[i][0]+dp[i][1]);
        DP[i+1][0]=DP[i][1];DP[i+1][1]=add(DP[i][0]+DP[i][1]);
    }
    int ans=1;
    rep(i,1,n)
    {
        int sz=DSU::querysz(i);
        if (sz>1) ans=1ll*ans*add(add(dp[sz-1][0]+dp[sz-1][1])+DP[sz-1][1])%MOD;
    }
    printf("%d\n",ans);
    return 0;
}