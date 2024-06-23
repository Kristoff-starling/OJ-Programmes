#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=1e9+7;

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

char s[100048];
int n,a[100048];

int main ()
{
    scanf("%s",s+1);int len=strlen(s+1);int rem=0;
    rep(i,1,len) rem=(1ll*rem*10+s[i]-'0')%(MOD-1);
    int ans=0,x;
    scanf("%d",&n);rep(i,1,n) scanf("%d",&x),ans=(ans+quick_pow(x,rem))%MOD;
    printf("%d\n",ans);return 0;
}