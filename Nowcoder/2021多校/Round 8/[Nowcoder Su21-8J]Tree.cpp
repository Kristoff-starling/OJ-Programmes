#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MAXN=5e5;

int n,S,T;
int mark[MAXN+48];
vector<int> v[MAXN+48];
int fa[MAXN+48],depth[MAXN+48],maxdepth[MAXN+48];
int val[MAXN+48];
int a[MAXN+48],tot;
int sa[MAXN+48],sb[MAXN+48],dp[MAXN+48];

void dfs(int cur,int father)
{
    fa[cur]=father;depth[cur]=depth[father]+1;
    maxdepth[cur]=0;
    for (auto y : v[cur]) if (y!=father) dfs(y,cur),maxdepth[cur]=max(maxdepth[cur],maxdepth[y]);
    maxdepth[cur]++;
}

struct ST
{
    int ST[MAXN+48][21],Log[MAXN+48];
    void init_ST(int A[])
    {
        Log[1]=0;rep(i,2,tot) Log[i]=Log[i>>1]+1;
        rep(i,1,tot) ST[i][0]=A[i];
        rep(j,1,20) rep(i,1,n)
        {
            ST[i][j]=ST[i][j-1];
            if (i+(1<<(j-1))<=n) ST[i][j]=max(ST[i][j],ST[i+(1<<(j-1))][j-1]);
        }
    }
    int query_ST(int l,int r)
    {
        int k=r-l+1;
        return max(ST[l][Log[k]],ST[r-(1<<Log[k])+1][Log[k]]);
    }
}st1,st2;

int main ()
{
    scanf("%d%d%d",&n,&S,&T);int x,y;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    depth[0]=0;dfs(T,0);
    int tmp=S;while (tmp) mark[tmp]=1,a[++tot]=tmp,tmp=fa[tmp];
    rep(i,1,tot)
    {
        int cur=a[i];val[i]=0;
        for (auto y : v[cur]) if (!mark[y]) val[i]=max(val[i],maxdepth[y]);
    }
    rep(i,1,tot) sa[i]=i-1+val[i];
    for (int i=tot,j=0;i>=1;i--,j++) sb[i]=val[i]+j;
    st1.init_ST(sa);st2.init_ST(sb);
    int N=tot/2;if (~tot&1) dp[N]=sa[N]-sb[N+1]; else dp[N]=max(sa[N]-max(sb[N+1],sb[N+2]),sa[N+1]-sb[N+2]);
    REP(i,N-1,1) dp[i]=max(sa[i]-st2.query_ST(i+1,tot+1-i),min(dp[i+1],st1.query_ST(i+1,tot-i)-sb[tot+1-i]));
    printf("%d\n",dp[1]);
    return 0;
}