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
const LL LINf=2e16;
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

const int MAXN=800;
const int MAXM=2e5;

int n,e,k;

int ga[MAXN+48][MAXN+48],dist[MAXN+48][MAXN+48];
inline void floyd()
{
	int i,j,k;
	for (k=0;k<=n;k++)
	{
		for (i=0;i<=n;i++)
			for (j=0;j<=n;j++)
				if (i!=k && j!=k && i!=j)
					ga[i][j]=min(ga[i][j],ga[i][k]+ga[k][j]);
		for (i=0;i<=k-1;i++) dist[i][k]=ga[i][k];
	}
}

int head[MAXM+48],cur[MAXM+48],to[MAXM+48],nxt[MAXM+48],f[MAXM+48],cost[MAXM+48],tot=1;
inline void addedge(int s,int t,int cap,int cc)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
}

int maxflow,mincost,S,T;
int D[MAXN+48];bool visited[MAXN+48];

inline int aug(int x,int maxf)
{
	if (x==T)
	{
		maxflow+=maxf;
		mincost+=(-D[S])*maxf;
		return maxf;
	}
	visited[x]=true;int y,minf,now,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y] && f[i] && D[x]+cost[i]-D[y]==0)
		{
			minf=min(maxf-ans,f[i]);
			now=aug(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	return ans;
}

inline bool relabel()
{
	int cur,i,d=INF;
	for (cur=0;cur<=T;cur++)
		if (visited[cur])
			for (i=head[cur];i;i=nxt[i])
				if (!visited[to[i]] && f[i]) d=min(d,D[cur]+cost[i]-D[to[i]]);
	if (d==INF) return false;
	for (cur=0;cur<=T;cur++)
		if (visited[cur]) D[cur]-=d;
	return true;
}

inline void zkw()
{
	do
	{
		for (register int i=0;i<=T;i++) cur[i]=head[i];
		do
			memset(visited,false,sizeof(visited));
		while (aug(S,INF));
	}
	while (relabel());
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
	floyd();S=n*2+1;T=n*2+2;
	addedge(S,0,k,0);
	for (i=1;i<=n;i++) addedge(S,i,1,0);
	for (i=1;i<=n;i++) addedge(n+i,T,1,0);
	for (i=0;i<=n-1;i++)
		for (j=i+1;j<=n;j++)
			addedge(i,n+j,1,dist[i][j]);
	zkw();printf("%d\n",mincost);
	return 0;
}
