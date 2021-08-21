#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MOD=998244353;
const int MAXN=5e5;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,p,x,pw[MAXN+48];
int f[MAXN+48][2],F[MAXN+48][2],g[MAXN+48],h[MAXN+48];
vector<int> v[MAXN+48];

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

void dfs(int cur)
{
    for (auto y : v[cur]) dfs(y);
    // no cur
    f[cur][0]=0;
    for (auto y : v[cur]) Add(f[cur][0],add(f[y][0]+f[y][1]));
    if (cur!=1) f[cur][0]=1ll*f[cur][0]*p%MOD;
    // cur, no child
    f[cur][1]=0;g[cur]=h[cur]=0;int ans=0,pans=1;
    for (auto y : v[cur]) Add(ans,f[y][0]),pans=1ll*pans*F[y][0]%MOD;
    Add(f[cur][1],add(ans+1ll*(1-p+MOD)%MOD)*pans%MOD);
    Add(g[cur],1ll*(1-p+MOD)%MOD*pans%MOD);Add(h[cur],g[cur]);
    // cur, one child
    for (auto y : v[cur])
    {
        int tmp=pans;tmp=1ll*tmp*quick_pow(F[y][0],MOD-2)%MOD;tmp=1ll*tmp*F[y][1]%MOD;
        int tmpans=ans;Sub(tmpans,F[y][0]);Add(tmpans,F[y][1]);
    }
}

int main ()
{
    scanf("%d%d",&n,&p);pw[0]=1;rep(i,1,p) pw[i]=1ll*pw[i-1]*p%MOD;
    rep(i,2,n) scanf("%d",&x),v[x].pb(i);
    dfs(1);printf("%d\n",f[1][0]);
    return 0;
}