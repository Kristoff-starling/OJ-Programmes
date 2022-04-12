#include <bits/stdc++.h>
#define LL long long
#define Pair pair<LL,LL>
#define x first
#define y second
#define mp make_pair
#define rep(i,a,b) for (int i=(a);i<=(b);i++)
using namespace std;

const int MAXN=100000;
const LL LINF=2e18;
const int LIM=1e9+48;

int N=150,n=301;
vector<LL> ans;

namespace MinCostFlow
{
	inline Pair operator + (Pair x,Pair y) {return mp(x.x+y.x,x.y+y.y);}
	int head[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],cost[MAXN+48],tot;
	LL dist[MAXN+48],h[MAXN+48];
    int prevv[MAXN+48],preve[MAXN+48];
	inline void init() {tot=1;memset(head,0,sizeof(head));memset(h,0,sizeof(h));}
	inline void addedge(int s,int t,int cap,int cc)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
	}
	priority_queue<Pair> q;
	inline bool dijkstra()
	{
		rep(i,0,n) dist[i]=LINF;
		dist[0]=0;q.push(mp(0,0));
		while (!q.empty())
		{
			int cur=q.top().y;LL dd=-q.top().x;q.pop();
			if (dd>dist[cur]) continue;
			for (int i=head[cur];i;i=nxt[i])
			{
				int y=to[i];
				if (f[i] && dist[cur]+cost[i]+h[cur]-h[y]<dist[y])
				{
					dist[y]=dist[cur]+cost[i]+h[cur]-h[y];
					prevv[y]=cur;preve[y]=i;
					q.push(mp(-dist[y],y));
				}
			}
		}
		return dist[n]<LINF;
	}
	inline Pair min_cost_flow()
	{
		rep(i,0,n) h[i]+=dist[i];
		int minf=1;LL res;
		res=minf*h[n];
		for (int u=n;u!=0;u=prevv[u]) f[preve[u]]-=minf,f[preve[u]^1]+=minf;
		return mp(minf,res);
	}
	inline void Edmonds_Karp_dijkstra()
	{
		Pair res=mp(0,0);
		while (dijkstra())
        {
            res=res+min_cost_flow();
            ans.push_back(1ll*LIM*res.x-res.y);
        }
	}
}

int maxn[200][200];

int main ()
{
    int _n,x,y,z;
    scanf("%d",&_n);
    memset(maxn,0,sizeof(maxn));
    rep(i,1,_n) scanf("%d%d%d",&x,&y,&z),maxn[x][y]=max(maxn[x][y],z);
    MinCostFlow::init();
    rep(i,1,N) MinCostFlow::addedge(0,i,1,0);
    rep(i,1,N) MinCostFlow::addedge(N+i,n,1,0);
    rep(i,1,N) rep(j,1,N) if (maxn[i][j]>0) MinCostFlow::addedge(i,N+j,1,LIM-maxn[i][j]);
    ans.clear();
    MinCostFlow::Edmonds_Karp_dijkstra();
    printf("%d\n",int(ans.size()));
    for (LL val : ans) printf("%lld\n",val);
    return 0;
}