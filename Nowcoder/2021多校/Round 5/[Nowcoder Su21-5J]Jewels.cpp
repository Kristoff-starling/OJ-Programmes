#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<long long,long long>
#define x first
#define y second
#define LL long long
#define pb push_back
#define mp make_pair
using namespace std;

const LL INF=1e14;
const int MAXN=1e6;

template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}

LL sq(LL x) {return x*x;}

int n;
LL X[1000],Y[1000],Z[1000],V[1000];

namespace Flow
{
    int N;
	inline Pair operator + (Pair x,Pair y) {return mp(x.x+y.x,x.y+y.y);}
	LL head[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],cost[MAXN+48],tot;
	LL dist[MAXN+48],h[MAXN+48],prevv[MAXN+48],preve[MAXN+48];
	inline void init() {tot=1;memset(head,0,sizeof(head));memset(h,0,sizeof(h));}
	inline void addedge(int s,int t,int cap,LL cc)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
	}
    bool visited[MAXN+48];
	inline bool dijkstra()
	{
		rep(i,0,N) dist[i]=INF;
		dist[0]=0;
        rep(i,0,N) visited[i]=false;
        for (;;)
        {
            LL md=INF,cur=-1;
            rep(i,0,N) if (dist[i]<md && !visited[i]) md=dist[i],cur=i;
            if (cur==-1) break;
            visited[cur]=true;
            for (int i=head[cur];i;i=nxt[i])
            {
                int y=to[i];
                assert(!f[i] || cost[i]+h[cur]-h[y]>=0);
                // if (visited[y]) assert(dist[cur]+cost[i]+h[cur]-h[y]>=dist[y]);
                if (f[i] && dist[cur]+cost[i]+h[cur]-h[y]<dist[y])
                {
                    dist[y]=dist[cur]+cost[i]+h[cur]-h[y];
					prevv[y]=cur;preve[y]=i;
                }
            }
        }
		return dist[N]<INF;
	}
	inline Pair min_cost_flow()
	{
		rep(i,0,N) h[i]+=dist[i];
		LL minf=INF,res;
		for (int u=N;u;u=prevv[u]) check_min(minf,f[preve[u]]);
		res=minf*h[N];
		for (int u=N;u;u=prevv[u]) f[preve[u]]-=minf,f[preve[u]^1]+=minf;
		return mp(minf,res);
	}
	inline Pair Edmonds_Karp_dijkstra()
	{
		Pair res=mp(0,0);
		while (dijkstra()) res=res+min_cost_flow();
		return res;
	}
}

int main ()
{
    scanf("%d",&n);rep(i,1,n) scanf("%lld%lld%lld%lld",X+i,Y+i,Z+i,V+i);
    Flow::N=n*2+1;Flow::init();
    rep(i,1,n) Flow::addedge(0,i,1,0),Flow::addedge(n+i,n*2+1,1,0);
    rep(i,1,n) rep(j,1,n) Flow::addedge(i,n+j,1,X[j]*X[j]+Y[j]*Y[j]+sq(Z[j]+1ll*(i-1)*V[j]));
    Pair res=Flow::Edmonds_Karp_dijkstra();
    printf("%lld\n",res.y);
    return 0;
}