#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define pb push_back
using namespace std;

const int MAXN=2e5;
const int MOD=1e9+7;

char s[MAXN+48];int n;
vector<int> v[MAXN+48];

int dp[MAXN+48];

int main ()
{
    scanf("%s",s+1);n=strlen(s+1);
    rep(ch,1,26)
    {
        int nxt=n+1;
        REP(i,n,1)
        {
            if (i+2<=n && s[i+2]-'a'+1==ch) nxt=i+2;
            if (nxt<=n) v[nxt].pb(i);
        }
    }
    rep(ch,1,26)
        rep(i,1,n) if (s[i]-'a'+1==ch) {v[i].pb(0);break;}
    dp[0]=1;
    rep(i,1,n) for (auto pre : v[i]) dp[i]=(dp[i]+dp[pre])%MOD;
    int ans=0;
    rep(i,1,n) ans=(ans+dp[i])%MOD;
    printf("%d\n",ans);
    return 0;
}