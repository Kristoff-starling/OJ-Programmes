#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e5;

namespace flow
{
	int head[800048],cur[800048],to[800048],nxt[800048],f[800048],tot=1,t;
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	int q[800048],depth[800048],Head,Tail;
	inline bool bfs()
	{
		for (register int i=0;i<=t;i++) depth[i]=-1;
		depth[0]=0;q[1]=0;Head=1;Tail=1;
		while (Head<=Tail)
		{
			int x=q[Head++];
			for (register int i=head[x];i;i=nxt[i])
			{
				int y=to[i];
				if (depth[y]==-1 && f[i])
				{
					depth[y]=depth[x]+1;
					q[++Tail]=y;
				}
			}
		}
		if (depth[t]==-1) return false; else return true;
	}
	inline int dfs(int x,int maxf)
	{
		if (x==t || !maxf) return maxf;
		int y,minf,now,ans=0;
		for (register int &i=cur[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);
				now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
				if (ans>=maxf) break;
			}
		}
		if (!ans) depth[x]=0;
		return ans;
	}
	inline int dinic()
	{
		int res=0;
		while (bfs())
		{
			for (register int i=0;i<=t;i++) cur[i]=head[i];
			res+=dfs(0,INF);
		}
		return res;
	}
}

int n,m1,m2;

vector<int> v[MAXN+48];
Pair path1[MAXN+48];int h1[MAXN+48];
Pair path2[MAXN+48];int h2[MAXN+48];
int LCA1[MAXN+48],LCA2[MAXN+48];

int depth[MAXN+48],fa[MAXN+48],anc[MAXN+48][21];
inline void dfs(int cur,int father)
{
	fa[cur]=father;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			anc[y][0]=cur;for (register int j=1;j<=17;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
}

inline int query_lca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=17;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=17;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return fa[u];
}

inline int jump(int u,int v)
{
	for (register int i=17;i>=0;i--)
		if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	return u;
}

inline bool on_list(int x,int u,int LCA)
{
	if (depth[x]>depth[u] || depth[x]<depth[LCA]) return false;
	u=jump(u,x);if (u!=x) return false; else return true;
}

inline bool on_path(int x,int u,int v,int LCA)
{
	return on_list(x,u,LCA) || on_list(x,v,LCA);
}

inline bool crossing(int x,int y)
{
	return on_path(LCA1[x],path2[y].x,path2[y].y,LCA2[y]) || on_path(LCA2[y],path1[x].x,path1[x].y,LCA1[x]);
}

int main ()
{
	scanf("%d%d%d",&n,&m1,&m2);int x,y;
	for (register int i=1;i<=n-1;i++) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
	depth[1]=1;dfs(1,-1);
	for (register int i=1;i<=m1;i++) scanf("%d%d%d",&path1[i].x,&path1[i].y,h1+i),LCA1[i]=query_lca(path1[i].x,path1[i].y);
	for (register int i=1;i<=m2;i++) scanf("%d%d%d",&path2[i].x,&path2[i].y,h2+i),LCA2[i]=query_lca(path2[i].x,path2[i].y);
	flow::t=m1+m2+1;
	for (register int i=1;i<=m1;i++) flow::addedge(0,i,h1[i]);
	for (register int i=1;i<=m2;i++) flow::addedge(m1+i,flow::t,h2[i]);
	for (register int i=1;i<=m1;i++)
		for (register int j=1;j<=m2;j++)
			if (crossing(i,j)) flow::addedge(i,m1+j,INF);
	int ans=0;
	for (register int i=1;i<=m1;i++) ans+=h1[i];
	for (register int i=1;i<=m2;i++) ans+=h2[i];
	ans-=flow::dinic();
	printf("%d\n",ans);
	return 0;
}
