#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=5000;
const LL LINF=2e16;

int n,m;
int X[MAXN+48],Y[MAXN+48],w[MAXN+48];
LL dist[MAXN+48];

int main ()
{
    scanf("%d%d",&n,&m);rep(i,1,m) scanf("%d%d%d",X+i,Y+i,w+i);
    rep(i,1,n) dist[i]=LINF;dist[1]=0;
    rep(_,1,n) rep(i,1,m) if (dist[X[i]]+w[i]<dist[Y[i]]) dist[Y[i]]=dist[X[i]]+w[i];
    rep(i,1,n) printf("%lld ",dist[i]);
    puts("");return 0;
}