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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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
		for (;ch>32;ch=Getchar()) *++s=ch;
		*(s+1)='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=1e5;

int n,q;
int id;

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

struct Edge
{
	int u,v,c;
	inline void input () {io.Get(u);io.Get(v);io.Get(c);}
}edge[MAXN+48];

vector<Pair> v[MAXN+48];

int anc[MAXN+48][21];
int depth[MAXN+48],L[MAXN+48],R[MAXN+48],pos[MAXN+48],ti;LL sum[MAXN+48];
inline void dfs(int cur,int father)
{
	L[cur]=++ti;pos[ti]=cur;int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			sum[y]=sum[cur]+v[cur][i].y;
			anc[y][0]=cur;
			for (register int j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
	R[cur]=ti;
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

namespace BIT
{
	#define LOWBIT(x) x & (-x)
	LL c[MAXN+48];
	inline void update(int x,LL delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
	inline LL query(int x) {LL res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
	inline void clear() {memset(c,0,sizeof(c));}
	inline void init() {for (register int i=1;i<=n;i++) update(i,sum[pos[i]]),update(i+1,-sum[pos[i]]);}
}

inline LL getdist(int u,int v)
{
	int LCA=getlca(u,v);
	return BIT::query(L[u])+BIT::query(L[v])-2ll*BIT::query(L[LCA]);
}

inline void Clear()
{
	for (register int i=1;i<=n;i++) v[i].clear();
	DSU::init();ti=0;BIT::clear();
}

int main ()
{
//	freopen ("k.in","r",stdin);
//	freopen ("k.out","w",stdout);
	int ca,op,x,y;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(q);Clear();
		for (register int i=1;i<=n;i++)
		{
			edge[i].input();
			if (DSU::find_anc(edge[i].u)==DSU::find_anc(edge[i].v)) {id=i;continue;}
			DSU::update(edge[i].u,edge[i].v);
			v[edge[i].u].pb(mp(edge[i].v,edge[i].c));v[edge[i].v].pb(mp(edge[i].u,edge[i].c));
		}
		depth[1]=1;sum[1]=0;dfs(1,-1);
		BIT::init();
		while (q--)
		{
			io.Get(op);io.Get(x);io.Get(y);
			if (!op)
			{
				if (x==id) {edge[x].c=y;continue;}
				int u=(depth[edge[x].u]<depth[edge[x].v]?edge[x].v:edge[x].u);
				BIT::update(L[u],-edge[x].c);BIT::update(R[u]+1,edge[x].c);
				edge[x].c=y;
				BIT::update(L[u],edge[x].c);BIT::update(R[u]+1,-edge[x].c);
			}
			else
			{
				io.Print(min(getdist(x,y),min(getdist(x,edge[id].u)+getdist(edge[id].v,y),getdist(x,edge[id].v)+getdist(edge[id].u,y))+edge[id].c));
			}
		}
	}
	io.flush();return 0;
}
