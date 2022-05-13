#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MOD=1e9+9;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,m,k,d;
int ga[48][48];

struct Matrix
{
    int b[48][48];
    void init() {memset(b,0,sizeof(b));}
    void init_I() {init();rep(i,1,n) b[i][i]=1;}
    int sum()
    {
        int res=0;
        rep(i,1,n) rep(j,1,n) Add(res,b[i][j]);
        return res;
    }
    Matrix operator + (Matrix other)
    {
        Matrix res;
        rep(i,1,n) rep(j,1,n) res.b[i][j]=add(b[i][j]+other.b[i][j]);
        return res;
    }
    Matrix operator * (Matrix other)
    {
        Matrix res;res.init();
        rep(i,1,n) rep(j,1,n) rep(k,1,n) Add(res.b[i][j],1ll*b[i][k]*other.b[k][j]%MOD);
        return res;
    }
}trans;

Matrix quick_pow(Matrix x,int y)
{
    Matrix res;res.init_I();
    while (y)
    {
        if (y&1) res=res*x;
        x=x*x;y>>=1;
    }
    return res;
}

bool check_valid(int x,int Mask)
{
    if (x>k) return true;
    if (Mask&(1<<(x-1))) return false;
    return true;
}

int main ()
{
    scanf("%d%d%d%d",&n,&m,&k,&d);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),ga[x][y]=ga[y][x]=1;
    if (d==1)
    {
        switch(k)
        {
            case 0:  printf("%d\n",n); break;
            case 1:  puts("1");        break;
            default: puts("0");        break;
        }
        return 0;
    }
    int ans=0;
    rep(Mask,0,(1<<k)-1)
    {
        trans.init();
        rep(i,1,n) rep(j,1,n)
            trans.b[i][j]=((check_valid(i,Mask) && check_valid(j,Mask))?ga[i][j]:0);
        int res=quick_pow(trans,d-1).sum();
        if (__builtin_popcount(Mask)&1) Sub(ans,res); else Add(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}