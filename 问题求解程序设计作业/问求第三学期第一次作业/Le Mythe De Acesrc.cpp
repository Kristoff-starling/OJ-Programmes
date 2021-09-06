#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int n,a[10048];
int q[100048];int head,tail;
int dist[20048];

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%d",a+i); 
    rep(i,1,a[n]) dist[i]=1e9;dist[0]=0;head=tail=50000;q[head]=0;
    while (head<=tail)
    {
        int cur=q[head++];
        rep(i,1,n-1)
        {
            int to=cur+a[i];
            if (to<a[n] && dist[cur]<dist[to])
            {
                dist[to]=dist[cur];
                q[--head]=to;
            }
            else if (to>=a[n] && dist[to-a[n]]>dist[cur]+1)
            {
                dist[to-a[n]]=dist[cur]+1;
                q[++tail]=to-a[n];
            }
        }
    }
    int q;scanf("%d",&q);int x;
    while (q--)
    {
        scanf("%d",&x);
        int type=x%a[n],step=x/a[n];
        if (dist[type]<=step) puts("Acesrc!"); else puts("Acesrc?");
    }
    return 0;
}