#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define LL long long
#define pb push_back
using namespace std;

const int MAXN=1000;
const LL LINF=1e18;

int n,m;
int sl[MAXN+48],sr[MAXN+48],c[MAXN+48];
int L[MAXN+48],R[MAXN+48],tot;

pair<int,int> val[MAXN*5+48];int vtot;
vector<int> seg[MAXN+48];

LL dp[MAXN+48];

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
}