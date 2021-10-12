#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,p,N;
long long m;

int add(int x) {if (x>=p) x-=p;return x;}
int sub(int x) {if (x<0) x+=p;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

struct Matrix
{
    int b[48][48];
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
        rep(i,1,N) rep(j,1,N) rep(k,1,N) Add(res.b[i][j],1ll*b[i][k]*other.b[k][j]%p);
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
    scanf("%d%lld%d",&n,&m,&p);
    if (n==1) {puts(m&1?"0":"1");return 0;}
    if (n==2)
    {
        if (m==1) {puts("1");return 0;}
        N=2;Matrix trans,st;
        trans.b[1][1]=0;trans.b[1][2]=trans.b[2][1]=trans.b[2][2]=1;
        st.b[1][1]=1;st.b[2][1]=2;st.b[1][2]=st.b[2][2]=0;
        trans=quick_pow(trans,m-2);st=trans*st;
        printf("%d\n",st.b[2][1]);return 0;
    }
    N=8;Matrix trans;
    trans.b[1][8]=1;trans.b[1][2]=1;trans.b[1][5]=1;
    trans.b[2][7]=1;trans.b[2][1]=1;
    trans.b[3][6]=1;
    trans.b[4][5]=1;
    trans.b[5][1]=1;trans.b[5][4]=1;
    trans.b[6][3]=1;
    trans.b[7][2]=1;
    trans.b[8][1]=1;
    trans=quick_pow(trans,m);
    Matrix st;st.b[1][1]=1;
    st=trans*st;printf("%d\n",st.b[1][1]);
    return 0;
}