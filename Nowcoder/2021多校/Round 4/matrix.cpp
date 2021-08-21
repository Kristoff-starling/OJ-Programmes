#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

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

struct Matrix
{
    int b[101][101],n;
    Matrix () {memset(b,0,sizeof(b));}
    void init_I() {rep(i,1,n) b[i][i]=1;}
    Matrix operator + (Matrix other)
    {
        Matrix res;
        rep(i,1,n) rep(j,1,n) res.b[i][j]=add(b[i][j]+other.b[i][j]);
        return res;
    }
    Matrix operator - (Matrix other)
    {
        Matrix res;
        rep(i,1,n) rep(j,1,n) res.b[i][j]=sub(b[i][j]-other.b[i][j]);
        return res;
    }
    Matrix operator * (Matrix other)
    {
        Matrix res;
        rep(i,1,n) rep(j,1,n) rep(k,1,n) Add(res.b[i][j],1ll*b[i][k]*other.b[k][j]%MOD);
        return res;
    }
    Matrix inv()
    {
        Matrix res;res.n=n;res.init_I();
        int a[101][101];rep(i,1,n) rep(j,1,n) a[i][j]=b[i][j];
        rep(i,1,n)
        {
            int pt=i;while (pt<=n && a[pt][i]==0) pt++;
            rep(j,1,n) swap(a[i][j],a[pt][j]),swap(res.b[i][j],res.b[pt][j]);
            rep(j,1,n) if (j!=i && a[j][i])
            {
                int t=1ll*a[i][i]*quick_pow(a[j][i],MOD-2)%MOD;
                rep(k,1,n) a[j][k]=1ll*a[j][k]*t%MOD,res.b[j][k]=1ll*res.b[j][k]*t%MOD;
                rep(k,1,n) Sub(a[j][k],a[i][k]),Sub(res.b[j][k],res.b[i][k]);
            }
        }
        rep(i,1,n)
        {
            int t=quick_pow(a[i][i],MOD-2);
            rep(j,1,n) a[i][j]=1ll*a[i][j]*t%MOD,res.b[i][j]=1ll*res.b[i][j]*t%MOD;
        }
        return res;
    }
};

int main ()
{
    Matrix b;
    scanf("%d",&b.n);
    rep(i,1,b.n) rep(j,1,b.n) scanf("%d",&b.b[i][j]);
    Matrix inv=b.inv();
    rep(i,1,3)
    {
        rep(j,1,3)
            printf("%d ",inv.b[i][j]);
        puts("");
    }
    return 0;
}