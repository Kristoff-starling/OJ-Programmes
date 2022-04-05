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
#define LOWBIT(x) ((x) & (-x))
// #define LOCAL true

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
template<typename T> inline T myabs(T x) {return (x>0)?x:(-x);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}

const int MAXN=3e5;

int n,q;

int head[MAXN+48],to[MAXN*2+48],nxt[MAXN*2+48],tot=0;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

int sz[MAXN+48],anc[MAXN+48][21],depth[MAXN+48],dfn[MAXN+48],ind;
inline void dfs(int cur,int father)
{
	sz[cur]=1;dfn[cur]=++ind;
	for (register int i=head[cur];i;i=nxt[i])
	{
		int y=to[i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;anc[y][0]=cur;
			for (register int j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);sz[cur]+=sz[y];
		}
	}
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline int jump(int u,int dist)
{
	for (register int i=20;i>=0;i--)
		if (dist>=(1<<i)) dist-=(1<<i),u=anc[u][i];
	return u;
}

bool isreal[MAXN+48];
int htot,h[MAXN+48],ans[MAXN+48];

namespace VirtualTree
{
	bool isvir[MAXN+48];int virlist[MAXN+48],vtot,root;
	int sta[MAXN+48],stot;int hh[MAXN+48];
	vector<int> v[MAXN+48],rev;int fa[MAXN+48];
	int dp_down[MAXN+48],dp_down_id[MAXN+48],dp_up[MAXN+48],dp_up_id[MAXN+48];
	inline bool cmp(int x,int y) {return dfn[x]<dfn[y];}
	inline void clear()
	{
		for (register int i=1;i<=vtot;i++)
		{
			int cur=virlist[i];
			v[cur].clear();isvir[cur]=false;ans[cur]=0;fa[cur]=0;
		}
		vtot=0;
	}
	inline void check_add(int x)
	{
		if (!isvir[x]) isvir[x]=true,virlist[++vtot]=x;
	}
	inline void construct_edge()
	{
		if (int(rev.size())==1) check_add(rev[0]);
		for (register int i=int(rev.size())-1;i;i--)
		{
			v[rev[i]].pb(rev[i-1]);fa[rev[i-1]]=rev[i];
			check_add(rev[i]);check_add(rev[i-1]);
		}
	}
	inline void build()
	{
		clear();memcpy(hh,h,sizeof(h));
		sort(hh+1,hh+htot+1,cmp);stot=0;
		for (register int i=1;i<=htot;i++)
		{
			if (!stot) {sta[++stot]=hh[i];continue;}
			int LCA=getlca(hh[i],sta[stot]);rev.clear();
			while (stot && depth[LCA]<depth[sta[stot]]) rev.pb(sta[stot--]);
			if (int(rev.size())) rev.pb(LCA),construct_edge();
			if (!stot || sta[stot]!=LCA) sta[++stot]=LCA;
			sta[++stot]=hh[i];
		}
		rev.clear();while (stot) rev.pb(sta[stot--]);
		if (int(rev.size())) construct_edge();
		for (register int i=1;i<=vtot;i++) if (!fa[virlist[i]]) root=virlist[i];
	}
	inline void dfs_down(int cur)
	{
		dp_down[cur]=INF;dp_down_id[cur]=0;
		if (isreal[cur]) dp_down[cur]=0,dp_down_id[cur]=cur;
		for (register int i=0;i<int(v[cur].size());i++)
		{
			int y=v[cur][i];
			dfs_down(y);
			if (dp_down[y]+depth[y]-depth[cur]<dp_down[cur] || (dp_down[y]+depth[y]-depth[cur]==dp_down[cur] && dp_down_id[y]<dp_down_id[cur]))
				dp_down[cur]=dp_down[y]+depth[y]-depth[cur],dp_down_id[cur]=dp_down_id[y];
		}
	}
	inline void update(Pair &x,Pair y)
	{
		if (y.x<x.x || (y.x==x.x && y.y<x.y)) x=y;
	}
	inline void dfs_up(int cur,int minn,int minid)
	{
		dp_up[cur]=minn;dp_up_id[cur]=minid;
		if (isreal[cur]) dp_up[cur]=0,dp_up_id[cur]=cur;
		vector<Pair> pre,suf;pre.clear();suf.clear();
		for (register int i=0;i<int(v[cur].size());i++)
		{
			int y=v[cur][i];Pair ins=(i==0)?mp(INF,0):pre[i-1];
			update(ins,mp(dp_down[y]+depth[y]-depth[cur],dp_down_id[y]));
			pre.pb(ins);
		}
		for (register int i=int(v[cur].size())-1;i>=0;i--)
		{
			int y=v[cur][i];Pair ins=(i==int(v[cur].size())-1)?mp(INF,0):suf[i+1];
			update(ins,mp(dp_down[y]+depth[y]-depth[cur],dp_down_id[y]));
			suf.pb(ins);
		}
		Pair res,res1,res2,res3;res3=mp(minn,minid);
		for (register int i=0;i<int(v[cur].size());i++)
		{
			int y=v[cur][i];
			res1=(i==0)?mp(INF,0):pre[i-1];res2=(i==int(v[cur].size())-1)?mp(INF,0):suf[i+1];
			res=res1;update(res,res2);update(res,res3);
			if (isreal[cur]) res.x=0,res.y=cur;
			dfs_up(y,res.x+depth[y]-depth[cur],res.y);
		}
	}
	inline void judge_edge()
	{
		for (register int i=1;i<=vtot;i++)
		{
			int cur=virlist[i];
			if (cur==root) continue;
			int pt1=dp_down_id[cur],pt2=dp_up_id[fa[cur]],tmp=jump(cur,depth[cur]-depth[fa[cur]]-1);
			if (!pt1 || !pt2)
			{
				if (!pt1) swap(pt1,pt2);
				ans[pt1]+=sz[tmp]-sz[cur];
				continue;
			}
			int d=dp_down[cur]+dp_up[fa[cur]]+depth[cur]-depth[fa[cur]],mid;
			if (d&1) mid=(d>>1);
			else if (dp_down_id[cur]<dp_up_id[fa[cur]]) mid=(d>>1); else mid=(d>>1)-1;
			if (mid<=dp_down[cur]) mid=dp_down[cur];
			if (mid>=dp_down[cur]+depth[cur]-depth[fa[cur]]-1) mid=dp_down[cur]+depth[cur]-depth[fa[cur]]-1;
			int mm=jump(cur,mid-dp_down[cur]);
			ans[dp_down_id[cur]]+=sz[mm]-sz[cur];
			ans[dp_up_id[fa[cur]]]+=sz[tmp]-sz[mm];
		}
	}
	inline void judge_node()
	{
		for (register int i=1;i<=vtot;i++)
		{
			int cur=virlist[i],cnt=sz[cur];
			for (register int j=0;j<int(v[cur].size());j++)
			{
				int y=v[cur][j],tmp=jump(y,depth[y]-depth[cur]-1);
				cnt-=sz[tmp];
			}
			if (cur==root) cnt+=n-sz[cur];
			Pair res1=mp(dp_down[cur],dp_down_id[cur]),res2=mp(dp_up[cur],dp_up_id[cur]);
			update(res1,res2);ans[res1.y]+=cnt;
		}
	}
}

int main ()
{
#ifdef LOCAL
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);int x,y;
	for (register int i=1;i<=n-1;i++) Get(x),Get(y),addedge(x,y);
	depth[1]=1;dfs(1,-1);
	Get(q);
	while (q--)
	{
		Get(htot);for (register int i=1;i<=htot;i++) Get(h[i]),isreal[h[i]]=true;
		VirtualTree::build();
		VirtualTree::dfs_down(VirtualTree::root);
		VirtualTree::dfs_up(VirtualTree::root,INF,0);
		VirtualTree::judge_edge();VirtualTree::judge_node();
		for (register int i=1;i<=htot;i++) printf("%d ",ans[h[i]]);puts("");
		for (register int i=1;i<=htot;i++) isreal[h[i]]=false;
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
