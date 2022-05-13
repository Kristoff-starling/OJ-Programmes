#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=1e5;

int n,m;
int a[MAXN+48];

set<int> s;
int maxn[MAXN+48];
long long dp[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d",a+i);
    s.insert(0);dp[0]=0;
    rep(i,1,n)
    {
        if (maxn[a[i]]!=0) s.erase(-maxn[a[i]]);
        maxn[a[i]]=i;s.insert(-i);int cnt=0;dp[i]=1e16;
        for (set<int>::iterator iter=s.begin();cnt*cnt<n && iter!=s.end();iter++,cnt++)
        {
            // if (i==1) cerr<<-*iter<<"!"<<' '<<cnt<<endl;
            if (-*iter==i) continue;
            dp[i]=min(dp[i],dp[-*iter]+1ll*cnt*cnt);
        }
    }
    printf("%lld\n",dp[n]);
    return 0;
}