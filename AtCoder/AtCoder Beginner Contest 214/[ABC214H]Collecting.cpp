#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define pb push_back
#define Pair pair<LL,LL>
#define x first
#define y second
#define mp make_pair
using namespace std;

const int MAXN=4e6;
const LL LINF=8e18;

int n,m,k;
vector<int> v[MAXN+48],vv[MAXN+48];
int w[MAXN+48];

LL X[MAXN+48];LL sum[MAXN+48];
int dfn[MAXN+48],low[MAXN+48],bel[MAXN+48],ind,tot;bool visited[MAXN+48];
int sta[MAXN+48],stot;


void tarjan(int cur)
{
    dfn[cur]=low[cur]=++ind;sta[++stot]=cur;visited[cur]=true;
    for (auto to : v[cur])
    {
        if (!dfn[to])
        {
            tarjan(to);
            low[cur]=min(low[cur],low[to]);
        }
        else if (visited[to]) low[cur]=min(low[cur],dfn[to]);
    }
    if (dfn[cur]==low[cur])
    {
        ++tot;X[tot]=0;int curv;
        do
        {
            curv=sta[stot--];
            visited[curv]=false;
            bel[curv]=tot;X[tot]+=w[curv];
        }
        while (curv!=cur);
    }
}

void FindSCC()
{
    tot=stot=ind=0;rep(i,1,n) dfn[i]=low[i]=0,visited[i]=false;
    rep(i,1,n) if (!dfn[i]) tarjan(i);
}

int d[MAXN+48],seq[MAXN+48],pos[MAXN+48];
int head,tail,q[MAXN+48];

namespace flow
{
	inline Pair operator + (Pair x,Pair y) {return mp(x.x+y.x,x.y+y.y);}
	LL head[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],tot;LL cost[MAXN+48];
	LL dist[MAXN+48],h[MAXN+48],prevv[MAXN+48],preve[MAXN+48],T;
	inline void init() {tot=1;memset(head,0,sizeof(head));memset(h,0,sizeof(h));}
	inline void addedge(int s,int t,int cap,LL cc)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
	}
	priority_queue<Pair> q;
	inline bool dijkstra()
	{
		rep(i,0,T) dist[i]=LINF;
		dist[0]=0;q.push(mp(0,0));
		while (!q.empty())
		{
			LL cur=q.top().y,dd=-q.top().x;q.pop();
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
		return dist[T]<LINF;
	}
	inline Pair min_cost_flow()
	{
		rep(i,0,T) h[i]+=dist[i];
		LL minf=LINF,res;
		for (int u=T;u;u=prevv[u]) minf=min(minf,f[preve[u]]);
		res=minf*h[T];
		for (int u=T;u;u=prevv[u]) f[preve[u]]-=minf,f[preve[u]^1]+=minf;
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
    scanf("%d%d%d",&n,&m,&k);int x,y;
    rep(i,1,m) scanf("%d%d",&x,&y),v[x].pb(y);
    rep(i,1,n) scanf("%d",w+i);
    FindSCC();
    rep(i,1,n) for (auto j : v[i]) if (bel[i]!=bel[j]) vv[bel[i]].pb(bel[j]),d[bel[j]]++;
    head=1;tail=0;rep(i,1,tot) if (!d[i]) q[++tail]=i;
    for (int cnt=1;head<=tail;cnt++)
    {
        int cur=q[head++];seq[cnt]=cur;pos[cur]=cnt;
        for (auto y : vv[cur])
        {
            d[y]--;
            if (d[y]==0) q[++tail]=y;
        }
    }
    sum[1]=X[seq[1]];rep(i,2,tot) sum[i]=sum[i-1]+X[seq[i]];
    flow::T=tot*2+1;flow::init();
    rep(i,1,tot) flow::addedge(i,tot+i,1,0),flow::addedge(i,tot+i,k,X[seq[i]]);
    rep(i,1,tot)
    {
        int xx=seq[i],yy;
        for (auto item : vv[xx])
        {
            yy=pos[item];
            flow::addedge(tot+i,yy,k,sum[yy-1]-sum[i]);
        }
    }
    flow::addedge(0,pos[bel[1]],k,0);
    rep(i,1,tot) flow::addedge(tot+i,flow::T,k,sum[tot]-sum[i]);
    Pair res=flow::Edmonds_Karp_dijkstra();
    assert(res.x==k);
    printf("%lld\n",(sum[tot]-sum[pos[bel[1]]-1])*k-res.y);
    return 0;
}