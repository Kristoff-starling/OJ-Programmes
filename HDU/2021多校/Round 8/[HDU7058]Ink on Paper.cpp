#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
using namespace std;

const int MAXN=5000;

int n;
int X[MAXN+48],Y[MAXN+48];
LL ga[MAXN+48][MAXN+48];
LL dist[MAXN+48];bool visited[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d%d",X+i,Y+i);
        rep(i,1,n) rep(j,1,n) ga[i][j]=1ll*(X[i]-X[j])*(X[i]-X[j])+1ll*(Y[i]-Y[j])*(Y[i]-Y[j]);
        LL ans=0;rep(i,1,n) visited[i]=false;int cur=1;
        rep(i,2,n) dist[i]=8e18;dist[1]=0;
        rep(i,1,n)
        {
            visited[cur]=true;
            rep(j,1,n) if (!visited[j] && ga[cur][j]<dist[j]) dist[j]=ga[cur][j];
            LL minn=8e18;
            rep(j,1,n) if (!visited[j] && dist[j]<minn) minn=dist[j],cur=j;
            if (i!=n) ans=max(ans,minn);
        }
        printf("%lld\n",ans);
    }
}