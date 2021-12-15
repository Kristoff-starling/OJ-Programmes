#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=1e9+7;

int N,k,p;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

struct Matrix
{
    int b[100][100];
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
    scanf("%d%d",&k,&p);
    N=k+1;Matrix trans,st;
    rep(i,1,k-1) trans.b[i][i+1]=1;
    trans.b[k+1][k+1]=trans.b[k][k+1]=1;
    scanf("%d",&st.b[N][1]);rep(i,1,k) scanf("%d",&trans.b[k][k+1-i]);
    rep(i,1,k) scanf("%d",&st.b[i][1]);
    if (p<=k-1) printf("%d\n",st.b[p+1][1]);
    trans=quick_pow(trans,p-k+1);st=trans*st;
    printf("%d\n",st.b[k][1]);return 0;
}