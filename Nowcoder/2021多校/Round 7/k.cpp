#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=2e5;
const int MAGIC=450;
const LL LINF=1e17;

int n,m,a[MAXN+48],d1[MAXN+48],d2[MAXN+48];
int lim;

template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}

struct node
{
    int l,r,k,id;
    void input(int _id) {scanf("%d%d%d",&l,&r,&k);id=_id;}
    bool operator < (const node &other) const {return k<other.k;}
}q[MAXN+48];

LL DP[500][500][2][2],dp[500][500][2][2];
int pt[500][2][2];

LL ans[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&m);rep(i,1,n) scanf("%d",a+i);
    rep(i,1,n) d1[i]=max(a[i]-a[i-1],0);
    rep(i,1,n) d2[i]=max(a[i-1]-a[i],0);
    rep(i,1,m) q[i].input(i);
    sort(q+1,q+m+1);
    int lim=n/MAGIC;if (n%MAGIC) lim++;
    int tmp=q[1].k;
    rep(block,1,lim)
    {
        int L=(block-1)*MAGIC+1,R=min(block*MAGIC,n);
        rep(i,1,MAGIC) rep(j,1,MAGIC) rep(sta1,0,1) rep(sta2,0,1) dp[i][j][sta1][sta2]=LINF;
        dp[1][0][0][0]=a[L];dp[1][1][1][1]=tmp-a[L];
        rep(i,L+1,R) rep(j,0,i-L+1) rep(sta,0,1)
        {
            check_min(dp[i-L+1][j][sta][0],dp[i-L][j][sta][0]+d1[i]);
            check_min(dp[i-L+1][j][sta][0],dp[i-L][j][sta][1]+a[i]);
            check_min(dp[i-L+1][j][sta][1],dp[i-L][j][sta][1]+d2[i]);
            if (j) check_min(dp[i-L+1][j][sta][1],dp[i-L][j-1][sta][0]+(tmp-a[i])); 
        }
        rep(j,0,R-L+1) rep(sta1,0,1) rep(sta2,0,1) DP[block][j][sta1][sta2]=dp[R-L+1][j][sta1][sta2];
        
    }
    rep(i,1,m)
    {
        if (q[i].k>tmp)
        {
            rep(block,1,lim) rep(sta1,0,1) rep(sta2,0,1);
        }
    }
    rep(i,1,m) printf("%lld\n",ans[i]);
    return 0;
}