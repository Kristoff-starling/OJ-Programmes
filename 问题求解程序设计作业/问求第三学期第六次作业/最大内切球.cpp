#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define ld long double
using namespace std;

const int MAXN=500;
const ld eps=1e-9;
const ld inf=1e12;

int n;
ld A[MAXN+48],B[MAXN+48],C[MAXN+48],D[MAXN+48];

namespace Simplex
{
    // m个约束，n个变量
    // 第i个约束，sum(a[i][j]*x[j])+a[i][0]>=0
    // solve函数返回约束是否有解
    // 若有解，则使得目标函数 sum(a[0][j]*x[j]) 最大化
    int T;
    ld a[MAXN+48][MAXN+48];
    int n,m,id[MAXN+48],tp[MAXN+48],nn;
    void pivot(int r,int c)
    {
        swap(id[r+n],id[c]);
        ld t=-a[r][c];
        a[r][c]=-1;
        rep(i,0,n) a[r][i]/=t;
        rep(i,0,m)
        if (fabs(a[i][c])>eps && r!=i) {
            t=a[i][c];
            a[i][c]=0;
            rep(j,0,n) a[i][j]+=t*a[r][j];
        }
    }
    bool solve(ld x[],bool *isinf)
    {
        ld t;
        rep(i,1,n) id[i]=i;
        while (true)
        {
            int i=0,j=0; ld w=-eps;
            rep(k,1,m) if (a[k][0]<w) w=a[i=k][0];
            if (!i) break;
            rep(k,1,n) if (a[i][k]>eps) {j=k; break;}
            if (!j) return false;
            pivot(i,j);
        }
        while (true)
        {
            int i=0,j=0; ld w=eps;
            rep(k,1,n) if (a[0][k]>w) w=a[0][j=k];
            if (!j) break;
            w=inf;
            rep(k,1,m) if (a[k][j]<-eps&&(t=-a[k][0]/a[k][j])<w) w=t,i=k;
            if (!i) {*isinf=true;return true;}
            pivot(i,j);
        }
        rep(i,n+1,n+m) tp[id[i]]=i-n;
        rep(i,1,n) x[i]=tp[i]?a[tp[i]][0]:0;
        *isinf=false;return true;
    }
}

void init()
{
    rep(i,1,n)
    {
        ld div=sqrt(A[i]*A[i]+B[i]*B[i]+C[i]*C[i]);
        Simplex::a[i][1]=A[i];Simplex::a[i][2]=B[i];Simplex::a[i][3]=C[i];
        Simplex::a[i][0]=-D[i];Simplex::a[i][4]=-div;
    }
    Simplex::a[n+1][0]=0;Simplex::a[n+1][1]=1;Simplex::a[n+1][2]=0;Simplex::a[n+1][3]=0;Simplex::a[n+1][4]=-1;
    Simplex::a[n+2][0]=0;Simplex::a[n+2][1]=0;Simplex::a[n+2][2]=1;Simplex::a[n+2][3]=0;Simplex::a[n+2][4]=-1;
    Simplex::a[n+3][0]=0;Simplex::a[n+3][1]=0;Simplex::a[n+3][2]=0;Simplex::a[n+3][3]=1;Simplex::a[n+3][4]=-1;
    Simplex::a[0][1]=Simplex::a[0][2]=Simplex::a[0][3]=0;Simplex::a[0][4]=1;
}

int main ()
{
    int ca;scanf("%d",&ca);
    ld x[5];bool isinf;
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%Lf%Lf%Lf%Lf",A+i,B+i,C+i,D+i),A[i]=-A[i],B[i]=-B[i],C[i]=-C[i],D[i]=-D[i];
        Simplex::n=4;Simplex::m=n+3;ld ans;
        init();bool res=Simplex::solve(x,&isinf);
        if (!res) puts("0.0000");
        else
            if (isinf) puts("Infinity"); else printf("%.4Lf\n",x[4]);
    }
    return 0;
}