#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=800,MAXM=2e5;

int n,e,k;

int ga[MAXN+48][MAXN+48],dist[MAXN+48][MAXN+48];
inline void floyd()
{
	int i,j,k;
	for (k=0;k<=n;k++)
	{
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				if (i!=j && i!=k && j!=k)
					ga[i][j]=min(ga[i][j],ga[i][k]+ga[k][j]);
		for (i=0;i<=k-1;i++) dist[i][k]=ga[i][k];
	}
}

int head[MAXN+48],nxt[MAXM+48],to[MAXM+48],f[MAXM+48],cost[MAXM+48],tot=1;
int prevv[MAXN+48],preve[MAXN+48],S,T;
inline void addedge(int s,int t,int cap,int cc)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
}

priority_queue<Pair> q;int d[MAXN+18],h[MAXN+48];
inline bool dijkstra()
{
	int i,x,y,dd;
	for (i=0;i<=T;i++) d[i]=INF;
	d[S]=0;q.push(mp(0,S));
	while (!q.empty())
	{
		dd=-q.top().x;x=q.top().y;q.pop();
		if (dd>d[x]) continue;
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (f[i] && d[x]+cost[i]+h[x]-h[y]<d[y])
			{
				d[y]=d[x]+cost[i]+h[x]-h[y];
				prevv[y]=x;preve[y]=i;
				q.push(mp(-d[y],y));
			}
		}
	}
	if (d[T]>=INF) return false; else return true;
}

inline int min_cost_flow()
{
	int i,minf=INF,u,ans;
	for (i=0;i<=T;i++) h[i]+=d[i];
	for (u=T;u!=S;u=prevv[u]) minf=min(minf,f[preve[u]]);
	ans=h[T]*minf;
	for (u=T;u!=S;u=prevv[u])
	{
		f[preve[u]]-=minf;
		f[preve[u]^1]+=minf;
	}
	return ans;
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	n=getint();e=getint();k=getint();int i,j,x,y,c;
	for (i=0;i<=n;i++)
		for (j=0;j<=n;j++)
			ga[i][j]=INF;
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();c=getint();
		ga[x][y]=ga[y][x]=min(ga[x][y],c);
	}
	floyd();
	S=n*2+1;T=n*2+2;
	addedge(S,0,k,0);
	for (i=1;i<=n-1;i++) addedge(S,i,1,0);
	for (i=1;i<=n;i++) addedge(n+i,T,1,0);
	for (i=0;i<=n-1;i++)
		for (j=i+1;j<=n;j++)
			addedge(i,n+j,1,dist[i][j]);
	int ans=0;
	while (dijkstra()) ans+=min_cost_flow();
	printf("%d\n",ans);return 0;
}
