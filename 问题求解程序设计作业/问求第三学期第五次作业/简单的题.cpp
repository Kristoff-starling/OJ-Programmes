#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e9;

void check_min(int &x,int y) {x=min(x,y);}

int val[1048],tot;

struct Matrix
{
    int b[201][201];
    Matrix () {memset(b,0,sizeof(b));}
    void init_I() {rep(i,1,tot) rep(j,1,tot) b[i][j]=(i==j?0:INF);}
    Matrix operator * (Matrix other)
    {
        Matrix res;rep(i,1,tot) rep(j,1,tot) res.b[i][j]=INF;
        rep(i,1,tot) rep(j,1,tot) rep(k,1,tot) check_min(res.b[i][j],b[i][k]+other.b[k][j]);
        return res;
    }
}edge;

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

int n,t,s,e;
int X[1000],Y[1000],c[1000];

int main ()
{
    scanf("%d%d%d%d",&n,&t,&s,&e);
    rep(i,1,t) scanf("%d%d%d",c+i,X+i,Y+i),val[++tot]=X[i],val[++tot]=Y[i];
    sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
    rep(i,1,tot) rep(j,1,tot) edge.b[i][j]=INF;
    rep(i,1,t) X[i]=lower_bound(val+1,val+tot+1,X[i])-val,Y[i]=lower_bound(val+1,val+tot+1,Y[i])-val,check_min(edge.b[X[i]][Y[i]],c[i]),check_min(edge.b[Y[i]][X[i]],c[i]);
    s=lower_bound(val+1,val+tot+1,s)-val;e=lower_bound(val+1,val+tot+1,e)-val;
    edge=quick_pow(edge,n);
    printf("%d\n",edge.b[s][e]);return 0;
}