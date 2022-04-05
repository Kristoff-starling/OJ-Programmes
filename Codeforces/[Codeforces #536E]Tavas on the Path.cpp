#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int 
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
// #define LOCAL true

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

int n,q,f[MAXN+48],ans[MAXN+48];
vector<Pair> v[MAXN+48];

struct Query
{
	int u,v,l,ind;
	inline void input(int _i) {Get(u);Get(v);Get(l);ind=_i;}
	inline bool operator < (const Query &other) const {return l>other.l;}
}Q[MAXN+48];

struct Edge
{
	int x,y,c;
	inline void input() {Get(x);Get(y);Get(c);v[x].pb(mp(y,c));v[y].pb(mp(x,c));}
	inline bool operator < (const Edge &other) {return c>other.c;}
}edge[MAXN+48];

int depth[MAXN+48],son[MAXN+48],sz[MAXN+48],top[MAXN+48],fa[MAXN+48],pos[MAXN+48],tot;

inline void dfs1(int cur,int father)
{
	son[cur]=0;sz[cur]=1;fa[cur]=father;
	for (auto item : v[cur])
	{
		int y=item.x;
		if (y!=father)
		{
			depth[y]=depth[cur]+1;dfs1(y,cur);
			if (!son[cur] || sz[son[cur]]<sz[y]) son[cur]=y;
			sz[cur]+=sz[y];
		}
	}
}

inline void dfs2(int cur,int tp)
{
	top[cur]=tp;pos[cur]=++tot;
	if (son[cur]) dfs2(son[cur],tp);
	for (auto item : v[cur])
	{
		int y=item.x;
		if (y!=fa[cur] && y!=son[cur]) dfs2(y,y);
	}
}

struct DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);if (x==y) return;pre[x]=y;}
}dsu1,dsu2;

namespace BIT
{
	int c[MAXN+48];
	inline void init() {memset(c,0,sizeof(c));}
	inline void modify(int x,int delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
	inline int calc(int left,int right) {return query(right)-query(left-1);}
}

bool visited[MAXN+48];int down[MAXN+48],len[MAXN+48];

inline void add(int x)
{
	visited[x]=true;
	dsu1.update(x,fa[x]);dsu2.update(x,son[x]);int tp=top[x];
	if (visited[fa[x]])
	{
		int ed=dsu1.find_anc(fa[x]);
		if (depth[ed]>=depth[tp]) BIT::modify(pos[fa[x]],-f[len[fa[x]]]),len[fa[x]]=0;
	}
	if (son[x] && visited[son[x]])
	{
		int ed=fa[dsu2.find_anc(son[x])];
		if (depth[ed]<depth[down[tp]] && ed!=0) BIT::modify(pos[ed],-f[len[ed]]),len[ed]=0;
	}
	int L=(dsu2.find_anc(x)==0?down[top[x]]:fa[dsu2.find_anc(x)]),R=son[dsu1.find_anc(x)];
	if (depth[down[tp]]>depth[L] && depth[R]>depth[tp]) len[L]=depth[L]-depth[R]+1,BIT::modify(pos[L],f[len[L]]);
}

inline int getlca(int u,int v)
{
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2]) swap(tp1,tp2),swap(u,v);
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]>depth[v]) swap(u,v);return u;
}

int left1,left2;

inline int solve(int u,int tar,int &Left)
{
	int tp=top[u],lft=0,res=0;
	while (tp!=top[tar])
	{
		int ed=dsu2.find_anc(tp);
		if (!ed || depth[ed]>depth[u]) {lft+=depth[u]-depth[tp]+1;u=fa[tp];tp=top[u];continue;}
		int L=dsu1.find_anc(u),R=dsu2.find_anc(tp);
		res+=f[lft+depth[u]-depth[L]]+BIT::calc(pos[R],pos[L]);lft=depth[R]-depth[tp];
		u=fa[tp];tp=top[u];
	}
	if (u==tar) {Left=lft;return res;}
	int ed=dsu2.find_anc(son[tar]);
	if (!ed || depth[ed]>depth[u]) {Left=lft+depth[u]-depth[tar];return res;}
	int L=dsu1.find_anc(u),R=dsu2.find_anc(son[tar]);
	res+=f[lft+depth[u]-depth[L]]+BIT::calc(pos[R],pos[L]);lft=depth[R]-depth[son[tar]];
	Left=lft;return res;
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
#endif
	Get(n);Get(q);
	for (register int i=1;i<=n-1;i++) Get(f[i]);
	for (register int i=1;i<=n-1;i++) edge[i].input();
	for (register int i=1;i<=q;i++) Q[i].input(i);
	depth[1]=1;dfs1(1,-1);dfs2(1,1);
	for (register int i=1;i<=n;i++)
	{
		int tp=top[i];
		if (!down[tp] || depth[down[tp]]<depth[i]) down[tp]=i;
	}
	sort(Q+1,Q+q+1);sort(edge+1,edge+n);int pt=0;
	for (register int i=1;i<=n-1;i++) if (depth[edge[i].x]<depth[edge[i].y]) swap(edge[i].x,edge[i].y);
	dsu1.init();dsu2.init();
	for (register int i=1;i<=q;i++)
	{
		while (pt<n-1 && edge[pt+1].c>=Q[i].l) add(edge[++pt].x);
		int LCA=getlca(Q[i].u,Q[i].v);left1=left2=0;
		ans[Q[i].ind]=solve(Q[i].u,LCA,left1)+solve(Q[i].v,LCA,left2);ans[Q[i].ind]+=f[left1+left2];
	}
	for (register int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
