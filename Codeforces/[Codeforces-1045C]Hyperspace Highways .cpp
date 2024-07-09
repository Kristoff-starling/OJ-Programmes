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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=1e6;

struct Edge
{
	int x,y;
	inline void input() {io.Get(x);io.Get(y);}
}edge[MAXN+48];

vector<int> v[MAXN+48];
vector<Pair> vv[MAXN+48];
int n,m,q;

int dfn[MAXN+48],low[MAXN+48],Index,ind;
stack<int> s;
vector<int> cir;

int val[MAXN+48];

inline bool check(int id,Pair E)
{
	if (edge[id].x==E.x && edge[id].y==E.y) return true;
	if (edge[id].x==E.y && edge[id].y==E.x) return true;
	return false;
}

inline void tarjan(int cur,int father)
{
	dfn[cur]=low[cur]=++Index;int id,x,u;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		register int y=(edge[v[cur][i]].x==cur?edge[v[cur][i]].y:edge[v[cur][i]].x);
		if (!dfn[y])
		{
			s.push(v[cur][i]);tarjan(y,cur);
			low[cur]=min(low[cur],low[y]);
			if (low[y]>=dfn[cur])
			{
				if (check(s.top(),mp(cur,y))) {vv[cur].pb(mp(y,1));vv[y].pb(mp(cur,1));s.pop();continue;}
				++ind;val[ind]=1;cir.clear();
				do
				{
					id=s.top();s.pop();	
					x=edge[id].x;u=edge[id].y;
					cir.pb(x);cir.pb(u);
				}
				while (!check(id,mp(cur,y)));
				sort(cir.begin(),cir.end());
				cir.resize(unique(cir.begin(),cir.end())-cir.begin());
				for (register int j=0;j<int(cir.size());j++) vv[ind].pb(mp(cir[j],0)),vv[cir[j]].pb(mp(ind,0));
			}
		}
		else if (y!=father && dfn[y]<dfn[cur])
		{
			s.push(v[cur][i]);
			low[cur]=min(low[cur],dfn[y]);
		}
	}
}

int sum[MAXN+48],anc[MAXN+48][21],depth[MAXN+48];
inline void dfs(int cur,int father)
{
	for (register int i=0;i<int(vv[cur].size());i++)
	{
		register int y=vv[cur][i].x;
		if (y!=father)
		{
			sum[y]=sum[cur]+vv[cur][i].y+val[y];
			depth[y]=depth[cur]+1;
			anc[y][0]=cur;
			for (register int j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
}

inline int get_lca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--)
		if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--)
		if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);io.Get(q);int x,y;
	for (register int i=1;i<=m;i++)
	{
		edge[i].input();
		v[edge[i].x].pb(i);v[edge[i].y].pb(i);
	}
	ind=n;tarjan(1,-1);
	sum[1]=val[1];depth[1]=1;dfs(1,-1);
	while (q--)
	{
		io.Get(x);io.Get(y);
		register int LCA=get_lca(x,y);
		io.Print(sum[x]+sum[y]-2*sum[LCA]+val[LCA],'\n');
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
