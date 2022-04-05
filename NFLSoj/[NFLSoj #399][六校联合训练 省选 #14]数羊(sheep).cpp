#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
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

template<typename T1,typename ...T2> inline void Get(T1 &x,T2&...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

int n,k;
int type[MAXN+48],val[MAXN+48];
vector<Pair> v[MAXN+48];

int ans=-1;

bool visited[MAXN+48];int sz[MAXN+48];

const int Base=1e5;
int rt[2][MAXN*3+48];

namespace Trie
{
	int maxn[MAXN*48],nxt[MAXN*48][2],tot;
	inline int Create() {++tot;maxn[tot]=-1;nxt[tot][0]=nxt[tot][1]=0;return tot;}
	inline void init(int Sz) {tot=0;for (register int i=Base-Sz;i<=Base+Sz;i++) rt[0][i]=Create(),rt[1][i]=Create();}
	inline void insert(int root,int val,int sumk)
	{
		int cur=root;check_max(maxn[cur],sumk);
		for (register int i=30;i>=1;i--)
		{
			int w=((val&(1<<(i-1)))?1:0);
			if (!nxt[cur][w]) nxt[cur][w]=Create();
			cur=nxt[cur][w];check_max(maxn[cur],sumk);
		}
	}
	inline int query(int root,int val,int sumk)
	{
		int need=max(k-sumk,0),cur=root,res=0;
		if (maxn[cur]<need) return -1;
		for (register int i=30;i>=1;i--)
		{
			int w=((val&(1<<(i-1)))?0:1);
			if (!nxt[cur][w] || maxn[nxt[cur][w]]<need) w^=1; else res|=(1<<(i-1));
			cur=nxt[cur][w];
		}
		return res;
	}
}

inline bool check_good(int minn,int mincnt,int maxn,int maxcnt,int curval)
{
	if (curval==minn && mincnt==1) return false;
	if (curval==maxn && maxcnt==1) return false;
	return true;
}

inline void update_min(int nv,int &nmin,int &nmincnt,int minn,int mincnt)
{
	nmin=minn;nmincnt=mincnt;
	if (nv<nmin) nmin=nv,nmincnt=1;
	else if (nv==nmin) nmincnt++;
}

inline void update_max(int nv,int &nmax,int &nmaxcnt,int maxn,int maxcnt)
{
	nmax=maxn;nmaxcnt=maxcnt;
	if (nv>nmax) nmax=nv,nmaxcnt=1;
	else if (nv==nmax) nmaxcnt++;
}

inline void dfs1(int cur,int father)
{
	sz[cur]=1;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i].x;
		if (y!=father && !visited[y]) dfs1(y,cur),sz[cur]+=sz[y];
	}
}

inline int getroot(int cur,int father,int Sz)
{
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i].x;
		if (y!=father && !visited[y] && sz[y]>Sz/2) return getroot(y,cur,Sz);
	}
	return cur;
}

inline void dfs2(int cur,int father,int minn,int mincnt,int maxn,int maxcnt,int curval,int sumk,int xsum)
{
	check_max(ans,Trie::query(rt[0][Base-curval],xsum,sumk));
	if (check_good(minn,mincnt,maxn,maxcnt,curval)) check_max(ans,Trie::query(rt[1][Base-curval],xsum,sumk));
	int nmin,nmincnt,nmax,nmaxcnt,nv;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i].x;
		if (y!=father && !visited[y])
		{
			nv=curval+(v[cur][i].y==0?-1:1);
			update_min(nv,nmin,nmincnt,minn,mincnt);
			update_max(nv,nmax,nmaxcnt,maxn,maxcnt);
			dfs2(y,cur,nmin,nmincnt,nmax,nmaxcnt,nv,sumk+type[y],xsum^val[y]);
		}
	}
}

inline void dfs3(int cur,int father,int minn,int mincnt,int maxn,int maxcnt,int curval,int sumk,int xsum)
{
	if (check_good(minn,mincnt,maxn,maxcnt,curval)) Trie::insert(rt[0][Base+curval],xsum,sumk);
	else Trie::insert(rt[1][Base+curval],xsum,sumk);
	int nmin,nmincnt,nmax,nmaxcnt,nv;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i].x;
		if (y!=father && !visited[y])
		{
			nv=curval+((v[cur][i].y==0)?-1:1);
			update_min(nv,nmin,nmincnt,minn,mincnt);
			update_max(nv,nmax,nmaxcnt,maxn,maxcnt);
			dfs3(y,cur,nmin,nmincnt,nmax,nmaxcnt,nv,sumk+type[y],xsum^val[y]);
		}
	}
}

inline void dfs4(int cur,int father,int curval,int xsum,int sumk,int zerocnt)
{
	if (curval==0) zerocnt++;
	if (curval==0 && zerocnt>=3 && sumk>=k) check_max(ans,xsum);
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i].x;
		if (y!=father && !visited[y]) dfs4(y,cur,curval+(v[cur][i].y==0?(-1):1),xsum^val[y],sumk+type[y],zerocnt);
	}
}

inline void solve(int cur)
{
	dfs1(cur,-1);int root=getroot(cur,-1,sz[cur]);
	Trie::init(sz[cur]);
	for (register int i=0;i<int(v[root].size());i++)
	{
		int y=v[root][i].x;
		if (!visited[y])
		{
			int edge=((v[root][i].y==0)?-1:1);
			if (edge==-1) dfs2(y,root,-1,1,0,1,edge,type[y]+type[root],val[y]^val[root]); else dfs2(y,root,0,1,1,1,edge,type[y],val[y]^val[root]);
			if (edge==-1) dfs3(y,root,-1,1,0,1,edge,type[y],val[y]); else dfs3(y,root,0,1,1,1,edge,type[y],val[y]);
		}
	}
	dfs4(root,-1,0,val[root],type[root],0);
	visited[root]=true;
	for (register int i=0;i<int(v[root].size());i++)
	{
		int y=v[root][i].x;
		if (!visited[y]) solve(y);
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n,k);int x,y,c;
	for (register int i=1;i<=n;i++) Get(type[i]);
	for (register int i=1;i<=n;i++) Get(val[i]);
	for (register int i=1;i<=n-1;i++)
	{
		Get(x,y,c);
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	solve(1);printf("%d\n",ans);
	return 0;
}
