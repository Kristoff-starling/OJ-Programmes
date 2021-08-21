#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;
const int MOD=1000000007;

char s[MAXN+48];

int quick_pow(int x,int y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%MOD;
        x=1ll*x*x%MOD;y>>=1;
    }
    return res;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        int n;scanf("%d",&n);scanf("%s",s+1);
        int cnt=1;while (cnt<n && s[cnt+1]==s[cnt]) cnt++;
        printf("%d\n",quick_pow(2,cnt-1));
    }
    return 0;
}