#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int INF=1e8;

template<typename T> void check_min(T &x,T y) {x=(x<y?x:y);}

int n,m;
int dist[201][201],ga[201][201];

int main ()
{
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		int x,y,c;
		rep(i,1,n) rep(j,1,n) if (i==j) dist[i][j]=0; else dist[i][j]=INF;
		rep(i,1,m) scanf("%d%d%d",&x,&y,&c),check_min(dist[x][y],c),check_min(dist[y][x],c);
		rep(i,1,n) rep(j,1,n) ga[i][j]=dist[i][j];
		int ans=INF;
		rep(k,1,n)
		{
			rep(i,1,k-2) rep(j,i+1,k-1) check_min(ans,ga[k][i]+dist[i][j]+ga[j][k]);
			rep(i,1,n) rep(j,1,n) if (i!=k && j!=k && i!=j) check_min(dist[i][j],dist[i][k]+dist[k][j]);
		}
		if (ans>=INF) puts("It's impossible."); else printf("%d\n",ans);
	}
	return 0;
}