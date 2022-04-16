#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MOD=998244353;
const int MAXN=2e5;

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

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,k;
int g[MAXN+48],f[MAXN+48];
int G[MAXN+48][21];

vector<int> facs[MAXN+48];

int c[48];

void init_c()
{
    c[1]=k;
    rep(i,2,20) c[i]=1ll*c[i-1]*(k-i+1)%MOD*quick_pow(i,MOD-2)%MOD;
}

int main ()
{
    scanf("%d%d",&n,&k);
    rep(i,1,n) scanf("%d",g+i);
    init_c();f[1]=1;
    rep(i,1,n) facs[i].clear();
    rep(i,2,n)
        for (int j=i+i;j<=n;j+=i)
            facs[j].push_back(i);
    G[1][1]=f[1];
    int lim=min(k,20);
    int inv=quick_pow(k,MOD-2);
    rep(i,2,n)
    {
        int coef=g[i];
        rep(j,2,lim)
        {
            G[i][j]=0;
            for (auto fac : facs[i])
                Add(G[i][j], 1ll*G[i/fac][j-1]*f[fac]%MOD);
            Sub(coef, 1ll*G[i][j]*c[j]%MOD);
        }
        f[i]=1ll*coef*inv%MOD;
        G[i][1]=f[i];
    }
    rep(i,1,n-1) printf("%d ",f[i]);
    printf("%d\n",f[n]);
    return 0;
}