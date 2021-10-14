#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
#define pb push_back
using namespace std;

const int MAXN=2000;
const LL LINF=1e18;

int n,m;
int sl[MAXN+48],sr[MAXN+48],c[MAXN+48];
int L[MAXN+48],R[MAXN+48],tot;

pair<int,int> val[MAXN*5+48];int vtot;
vector<int> seg[MAXN+48];

LL dp[MAXN+48][MAXN+48],minn[MAXN+48];

void check_min(LL &x,LL y) {x=min(x,y);}

int main ()
{
    scanf("%d%d",&n,&m);rep(i,1,n) scanf("%d%d%d",sl+i,sr+i,c+i);
    rep(i,1,n) val[++vtot]=make_pair(sl[i],0),val[++vtot]=make_pair(sr[i],1);
    sort(val+1,val+vtot+1);int cnt=0;
    if (val[1].first!=0) L[++tot]=0,R[tot]=val[1].first;
    rep(i,1,vtot)
    {
        if (!val[i].second) ++cnt; else --cnt;
        if (cnt==0 && i!=vtot && val[i].first!=val[i+1].first) L[++tot]=val[i].first,R[tot]=val[i+1].first;
    }
    if (val[vtot].first<m) L[++tot]=val[vtot].first,R[tot]=m;
    rep(i,1,n)
    {
        if (sr[i]<=L[1]) seg[0].pb(i);
        else if (sl[i]>=R[tot]) seg[tot].pb(i);
        else
            rep(j,1,tot-1) if (sl[i]>=R[j] && sr[i]<=L[j+1]) seg[j].pb(i);
    }
    minn[1]=LINF;
    rep(j,0,tot)
    {
        for (auto id : seg[j])
        {
            if (sl[id]>=R[1]) dp[1][id]=1ll*c[id]*(sl[id]-L[1]); else dp[1][id]=1ll*c[id]*(R[1]-sr[id]);
            check_min(minn[1],dp[1][id]);
        }
    }
    rep(i,2,tot)
    {
        minn[i]=LINF;
        rep(j,0,i-2)
        {
            for (auto id : seg[j])
            {
                dp[i][id]=dp[i-1][id]+1ll*c[id]*(R[i]-R[i-1]);
                check_min(dp[i][id],minn[i-1]+1ll*c[id]*(R[i]-sr[id]));
                check_min(minn[i],dp[i][id]);
            }
        }
        for (auto id : seg[i-1])
        {
            dp[i][id]=dp[i-1][id]+1ll*c[id]*(R[i]-sr[id]);
            check_min(dp[i][id],minn[i-1]+1ll*c[id]*(R[i]-sr[id]));
            check_min(minn[i],dp[i][id]);
        } 
        rep(j,i,tot)
        {
            for (auto id : seg[j])
            {
                dp[i][id]=dp[i-1][id];
                check_min(dp[i][id],minn[i-1]+1ll*c[id]*(sl[id]-L[i]));
                check_min(minn[i],dp[i][id]);
            }
        }
    }
    LL ans=LINF;rep(i,1,n) check_min(ans,dp[tot][i]);
    printf("%lld\n",ans);
    return 0;
}