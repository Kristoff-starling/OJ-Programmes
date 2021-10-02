#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e6;
const int MOD=998244353;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}

int n,d;
int f[MAXN+48],pw[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&d);f[1]=0;int ans=0;
    pw[0]=1;rep(i,1,n) pw[i]=add(pw[i-1]+pw[i-1]);
    rep(i,2,n)
    {
        f[i]=f[i-1];
        if (i-1<=d && (i-1)*2>=d)
        {
            int cnt1=pw[i-2],cnt2;
            int tmp=d-(i-1);
            if (!tmp) cnt2=1; else cnt2=pw[tmp-1];
            if ((i-1)*2!=d) cnt2=1ll*cnt2*2%MOD;
            Add(f[i],1ll*cnt1*cnt2%MOD);
        }
        Add(ans,1ll*f[i]*pw[n-i]%MOD);
    }
    printf("%d\n",add(ans+ans));return 0;
}