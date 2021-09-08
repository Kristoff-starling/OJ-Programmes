#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,m;
int dist[500][500];
int ans[200048];

int main ()
{
    scanf("%d%d",&n,&m);int x,y;
    rep(i,1,n) rep(j,1,n) dist[i][j]=m+1;rep(i,1,n) dist[i][i]=0;
    rep(i,1,m) scanf("%d%d",&x,&y),dist[x][y]=i;
    rep(k,1,n) rep(i,1,n) rep(j,1,n) dist[i][j]=min(dist[i][j],max(dist[i][k],dist[k][j]));
    rep(i,1,n) rep(j,1,n) if (i!=j) ans[dist[i][j]]++;
    rep(i,1,m) ans[i]+=ans[i-1],printf("%d ",ans[i]);
    puts("");return 0;
}