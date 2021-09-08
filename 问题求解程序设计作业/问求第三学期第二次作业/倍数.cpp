#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=(1<<20)-1;
const int INF=1e9;
vector<pair<int,int> > to[MAXN+48];
int q[MAXN<<2],head,tail,dist[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        int n;scanf("%d",&n);
        rep(i,0,MAXN) to[i].clear();
        rep(i,0,MAXN)
            to[i].pb(mp(i>>1,(i&1))),to[i].pb(mp((i+n)>>1,(i+n)&1));
        rep(i,0,MAXN) dist[i]=INF;
        dist[0]=0;head=tail=(MAXN<<1);q[head]=0;
        int ans=INF;
        while (head<=tail)
        {
            int cur=q[head++];
            for (auto item : to[cur])
            {
                if (item.y==0 && dist[cur]<dist[item.x]) dist[item.x]=dist[cur],q[--head]=item.x;
                if (item.y==1 && dist[cur]+1<dist[item.x]) dist[item.x]=dist[cur]+1,q[++tail]=item.x;
                if (cur && item.x==0) ans=min(ans,dist[cur]+item.y);
            }    
        }
        rep(i,1,MAXN) ans=min(ans,__builtin_popcount(i)+dist[i]);
        if (n==1) ans=1;
        printf("%d\n",ans);
    }
    return 0;
}