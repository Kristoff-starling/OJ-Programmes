#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=1e9+7;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int N=2;

struct Matrix
{
    int b[20][20];
    Matrix () {memset(b,0,sizeof(b));}
    void init_I() {rep(i,1,N) b[i][i]=1;}
    Matrix operator + (Matrix other)
    {
        Matrix res;
        rep(i,1,N) rep(j,1,N) res.b[i][j]=add(b[i][j]+other.b[i][j]);
        return res;
    }
    Matrix operator - (Matrix other)
    {
        Matrix res;
        rep(i,1,N) rep(j,1,N) res.b[i][j]=sub(b[i][j]-other.b[i][j]);
        return res;
    }
    Matrix operator * (Matrix other)
    {
        Matrix res;
        rep(i,1,N) rep(j,1,N) rep(k,1,N) Add(res.b[i][j],1ll*b[i][k]*other.b[k][j]%MOD);
        return res;
    }
};

Matrix quick_pow(Matrix x,long long y)
{
    Matrix res;res.init_I();
    while (y)
    {
        if (y&1) res=res*x;
        x=x*x;y>>=1;
    }
    return res;
}

int main ()
{
    long long n;scanf("%lld",&n);
    if (n==1) {puts("1");return 0;}
    Matrix trans,st;
    trans.b[1][1]=4;trans.b[1][2]=1;trans.b[2][1]=2;trans.b[2][2]=1;
    st.b[1][1]=1;st.b[2][1]=1;
    trans=quick_pow(trans,n-1);st=trans*st;
    printf("%d\n",st.b[1][1]);return 0;
}