#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<LL,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,q;
int head[2000048],to[2000048],nxt[2000048],tot=1;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
}

int virlist[1000048],vtot=0;
vector<Pair> v[1000048];
int depth[1000048];
int seq[1000048],pos[1000048],ind=0;
int num,a[1000048];
int anc[1000048][21];
bool isreal[1000048],isvir[1000048];

inline void dfs(int cur,int father)
{
	int i,j,y;
	seq[++ind]=cur;pos[cur]=ind;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
}

inline bool cmp(int x,int y)
{
	return pos[x]<pos[y];
}

namespace VirtualTree
{
	vector<Pair> rev;stack<int> s;
	inline void clear()
	{
		int i;
		for (i=1;i<=vtot;i++) isvir[virlist[i]]=false,isreal[virlist[i]]=false,v[virlist[i]].clear();
		vtot=0;
	}
	inline int getlca(int u,int v)
	{
		int i;
		if (depth[u]<depth[v]) swap(u,v);
		for (i=20;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
		if (u==v) return u;
		for (i=20;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
		return anc[u][0];
	}
	inline bool cmp(int x,int y) {return pos[x]<pos[y];}
	inline void construct_edge()
	{
		int i;
		for (i=int(rev.size())-1;i>0;i--)
		{
			v[rev[i].x].pb(mp(rev[i-1].x,rev[i].y));
			if (!isvir[rev[i].x]) isvir[rev[i].x]=true,virlist[++vtot]=rev[i].x;
			if (!isvir[rev[i-1].x]) isvir[rev[i-1].x]=true,virlist[++vtot]=rev[i-1].x;
			v[rev[i-1].x].pb(mp(rev[i].x,rev[i].y));
		}
	}
	inline void construct_vir()
	{
		int i,lca;Pair ins;
		for (i=1;i<=num;i++) v[a[i]].clear(),isreal[a[i]]=true;
		sort(a+1,a+num+1,cmp);
		for (i=1;i<=num;i++)
		{
			if (s.empty()) {s.push(a[i]);continue;}
			lca=getlca(s.top(),a[i]);rev.clear();
			while (!s.empty() && depth[lca]<depth[s.top()])
			{
				ins.x=s.top();if (!rev.empty()) ins.y=depth[rev.back().x]-depth[ins.x]; else ins.y=-1;
				rev.pb(ins);s.pop();
			}
			if (int(rev.size())) ins.x=lca,ins.y=depth[rev.back().x]-depth[lca],rev.pb(ins),construct_edge();
			if (s.empty() || s.top()!=lca) s.push(lca);
			s.push(a[i]);
		}
		rev.clear();
		while (!s.empty())
		{
			ins.x=s.top();if (!rev.empty()) ins.y=depth[rev.back().x]-depth[ins.x]; else ins.y=-1;
			rev.pb(ins);s.pop();
		}
		construct_edge();
	}
	inline void print(int cur,int father)
	{
		int i;
		cout<<cur<<":";
		for (i=0;i<int(v[cur].size());i++) cout<<v[cur][i].x<<' '<<v[cur][i].y<<"        ";
		cout<<endl;
		for (i=0;i<int(v[cur].size());i++) if (v[cur][i].x!=father) print(v[cur][i].x,cur);
	}
}

namespace answer
{
	int sz[1000048];LL sum[1000048],dp[1000048],g[1000048];
	LL anssum=0,ansmax=-LINF,ansmin=LINF;
	inline void dfs(int cur,int father)
	{
		int i,y;
		sz[cur]=(isreal[cur]?1:0);
		for (i=0;i<int(v[cur].size());i++)
		{
			y=v[cur][i].x;
			if (y!=father)
			{
				sum[y]=sum[cur]+v[cur][i].y;
				dfs(y,cur);
				sz[cur]+=sz[y];
				anssum+=(long long)(v[cur][i].y)*(long long)(sz[y])*(num-sz[y]);
			}
		}
	}
	inline void find_dia(int cur,int father)
	{
		int i,y;
		for (i=0;i<int(v[cur].size());i++)
		{
			y=v[cur][i].x;
			if (y!=father)
			{
				sum[y]=sum[cur]+v[cur][i].y;
				find_dia(y,cur);
			}
		}
	}
	inline void calc_min(int cur,int father)
	{
		int i,y;
		dp[cur]=LINF;g[cur]=LINF;
		for (i=0;i<int(v[cur].size());i++)
		{
			y=v[cur][i].x;
			if (y!=father) calc_min(y,cur);
		}
		if (isreal[cur])
		{
			for (i=0;i<int(v[cur].size());i++)
				dp[cur]=min(dp[cur],g[v[cur][i].x]+v[cur][i].y);
			g[cur]=0;
		}
		else
		{
			LL fmin=LINF,smin=LINF;
			for (i=0;i<int(v[cur].size());i++)
			{
				if (g[v[cur][i].x]+v[cur][i].y<fmin) {smin=fmin;fmin=g[v[cur][i].x]+v[cur][i].y;continue;}
				if (g[v[cur][i].x]+v[cur][i].y<smin) {smin=g[v[cur][i].x]+v[cur][i].y;continue;}
			}
			dp[cur]=fmin+smin;g[cur]=fmin;
		}
	}		
	inline void solve()
	{
		int i;
		anssum=0ll;sum[1]=0ll;dfs(virlist[1],-1);
		LL curmax=-1;int maxpos;
		for (i=1;i<=vtot;i++) if (sum[virlist[i]]>curmax) curmax=sum[virlist[i]],maxpos=virlist[i];
		sum[maxpos]=0;find_dia(maxpos,-1);
		ansmax=-1;for (i=1;i<=vtot;i++) if (sum[virlist[i]]>ansmax) ansmax=sum[virlist[i]];
		ansmin=LINF;calc_min(virlist[1],-1);for (i=1;i<=vtot;i++) ansmin=min(ansmin,dp[virlist[i]]);
		printf("%lld %lld %lld\n",anssum,ansmin,ansmax);
	}
}
int main ()
{
	int i,x,y;
	n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		addedge(x,y);addedge(y,x);
	}
	depth[1]=1;dfs(1,-1);
	q=getint();
	while (q--)
	{
		VirtualTree::clear();
		num=getint();
		for (i=1;i<=num;i++) a[i]=getint();
		if (num==0 || num==1)
		{
			printf("0 0 0\n");
			continue;
		}
		VirtualTree::construct_vir();
		answer::solve();
	}
	return 0;
}
