#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
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

const int MAXN=5e4;

int n,m,q,ind,Index;
vector<int> v[MAXN+48];
int dfn[MAXN+48],low[MAXN+48];
stack<int> s;
bool type[MAXN+48];vector<Pair> vv[MAXN+48];
vector<Pair> cir[MAXN+48];vector<int> presum[MAXN+48];int pos[MAXN+48];int sum[MAXN+48];

struct Edge
{
	int x,y,c;
	inline void input() {x=getint();y=getint();c=getint();}
}edge[MAXN+48];

inline bool check(int id,Pair E)
{
	if (edge[id].x==E.x && edge[id].y==E.y) return true;
	if (edge[id].x==E.y && edge[id].y==E.x) return true;
	return false;
}

inline void tarjan(int cur,int father)
{
	dfn[cur]=low[cur]=++Index;int i,j,x,y,id,u;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=(edge[v[cur][i]].x==cur?edge[v[cur][i]].y:edge[v[cur][i]].x);
		if (!dfn[y])
		{
			s.push(v[cur][i]);tarjan(y,cur);
			low[cur]=min(low[cur],low[y]);
			if (low[y]>=dfn[cur])
			{
				if (check(s.top(),mp(cur,y))) {vv[cur].pb(mp(y,edge[v[cur][i]].c));vv[y].pb(mp(cur,edge[v[cur][i]].c));s.pop();continue;}
				++ind;type[ind]=true;int pre=cur;
				do
				{
					id=s.top();s.pop();	
					x=edge[id].x;u=edge[id].y;
					if (x==pre) swap(x,u);
					cir[ind].pb(mp(x,edge[id].c));
					pre=x;
				}
				while (!check(id,mp(cur,y)));
				for (j=0;j<int(cir[ind].size());j++)
				{
					sum[ind]+=cir[ind][j].y;presum[ind].pb(sum[ind]);
					if (j!=int(cir[ind].size())-1) pos[cir[ind][j].x]=j;
				}
				for (j=0;j<int(cir[ind].size());j++)
					if (j!=int(cir[ind].size())-1)
					{
						int cc=min(presum[ind][j],sum[ind]-presum[ind][j]);
						vv[ind].pb(mp(cir[ind][j].x,cc));vv[cir[ind][j].x].pb(mp(ind,cc));
					}
					else
						vv[ind].pb(mp(cir[ind][j].x,0)),vv[cir[ind][j].x].pb(mp(ind,0));
			}
		}
		else if (y!=father && dfn[y]<dfn[cur])
		{
			s.push(v[cur][i]);
			low[cur]=min(low[cur],dfn[y]);
		}
	}
}

int depth[MAXN+48],anc[MAXN+48][21],dist[MAXN+48][21];
inline void dfs(int cur,int father)
{
	int i,j,y;
	for (i=0;i<int(vv[cur].size());i++)
	{
		y=vv[cur][i].x;
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			anc[y][0]=cur;dist[y][0]=vv[cur][i].y;		
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1],dist[y][j]=dist[y][j-1]+dist[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--)
		if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--)
		if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline Pair jump(int u,int dep)
{
	int res=0;
	for (register int i=20;i>=0;i--)
		if (dep>=(1<<i)) dep-=(1<<i),res+=dist[u][i],u=anc[u][i];
	return mp(u,res);
}

int main ()
{
	//freopen ("1.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i,x,y,c,LCA;
	n=getint();m=getint();q=getint();
	for (i=1;i<=m;i++) edge[i].input(),v[edge[i].x].pb(i),v[edge[i].y].pb(i);
	for (i=1;i<=n;i++) type[i]=false;
	memset(pos,-1,sizeof(pos));
	ind=n;Index=0;tarjan(1,-1);
	dfs(1,-1);int ans=0;
	while (q--)
	{
		x=getint();y=getint();LCA=getlca(x,y);
		if (!type[LCA]) printf("%d\n",jump(x,depth[x]-depth[LCA]).y+jump(y,depth[y]-depth[LCA]).y);
		else
		{
			ans=0;
			Pair res=jump(x,depth[x]-depth[LCA]-1);x=res.x;ans+=res.y;
			res=jump(y,depth[y]-depth[LCA]-1);y=res.x;ans+=res.y;
			assert(x!=y);
			x=pos[x];y=pos[y];if (x>y) swap(x,y);
			ans+=min(presum[LCA][y]-presum[LCA][x],sum[LCA]-(presum[LCA][y]-presum[LCA][x]));
			printf("%d\n",ans);
		}
	}
	return 0;
}
