#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define ull unsigned long long
#define uint unsigned int
#define LD long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))
#define rep(i,a,b) for (register int i=a;i<=b;i++)
#define Rep(i,b,a) for (register int i=b;i>=a;i--)

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

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

int n,a[MAXN+48],fa[MAXN+48];
vector<int> v[MAXN+48];int anc[MAXN+48][21],depth[MAXN+48],top[MAXN+48],son[MAXN+48],sz[MAXN+48],in[MAXN+48],out[MAXN+48],seq[MAXN+48],tot;
int rt;

inline int jump(int x,int y)
{
	Rep(i,17,0) if (depth[anc[x][i]]>depth[y]) x=anc[x][i];
	return x;
}

inline void dfs1(int cur)
{
	sz[cur]=1;son[cur]=0;
	for (auto y : v[cur])
	{
		depth[y]=depth[cur]+1;anc[y][0]=cur;rep(i,1,17) anc[y][i]=anc[anc[y][i-1]][i-1];
		dfs1(y);sz[cur]+=sz[y];
		if (!son[cur] || sz[son[cur]]<sz[y]) son[cur]=y;
	}
}

inline void dfs2(int cur,int tp)
{
	in[cur]=++tot;seq[tot]=cur;top[cur]=tp;
	if (son[cur]) dfs2(son[cur],tp);
	for (auto y : v[cur]) if (y!=son[cur]) dfs2(y,y);
	out[cur]=tot;
}

namespace SegmentTree
{
	LL sum[MAXN*4],lazy[MAXN*4];int len[MAXN*4];
	inline void pushdown(int cur) {lazy[cur<<1]+=lazy[cur];lazy[cur<<1|1]+=lazy[cur];sum[cur<<1]+=lazy[cur]*len[cur<<1];sum[cur<<1|1]+=lazy[cur]*len[cur<<1|1];lazy[cur]=0;}
	inline void pushup(int cur) {sum[cur]=sum[cur<<1]+sum[cur<<1|1];}
	inline void build(int cur,int l,int r)
	{
		lazy[cur]=0;len[cur]=r-l+1;
		if (l==r) {sum[cur]=a[seq[l]];return;}
		int mid=(l+r)>>1;build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
		pushup(cur);
	}
	inline void modify(int cur,int left,int right,int delta,int l,int r)
	{
		if (left<=l && r<=right) {lazy[cur]+=delta;sum[cur]+=1ll*delta*len[cur];return;}
		int mid=(l+r)>>1;pushdown(cur);
		if (left<=mid) modify(cur<<1,left,right,delta,l,mid);
		if (mid+1<=right) modify(cur<<1|1,left,right,delta,mid+1,r);
		pushup(cur);
	}
	inline LL query(int cur,int left,int right,int l,int r)
	{
		if (left<=l && r<=right) return sum[cur];
		int mid=(l+r)>>1;pushdown(cur);LL res=0;
		if (left<=mid) res+=query(cur<<1,left,right,l,mid);
		if (mid+1<=right) res+=query(cur<<1|1,left,right,mid+1,r);
		pushup(cur);return res;
	}
}

inline bool intree(int x,int y) {return in[x]<=in[y] && in[y]<=out[x];}

inline void modify_chain(int u,int v,int delta)
{
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2]) swap(tp1,tp2),swap(u,v);
		SegmentTree::modify(1,in[tp1],in[u],delta,1,n);
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]>depth[v]) swap(u,v);
	SegmentTree::modify(1,in[u],in[v],delta,1,n);
}

inline void modify_subtree(int x,int delta)
{
	if (x==rt) {SegmentTree::modify(1,1,n,delta,1,n);return;}
	if (!intree(x,rt)) {SegmentTree::modify(1,in[x],out[x],delta,1,n);return;}
	SegmentTree::modify(1,1,n,delta,1,n);int pt=jump(rt,x);
	SegmentTree::modify(1,in[pt],out[pt],-delta,1,n);
}

inline LL query_chain(int u,int v)
{
	int tp1=top[u],tp2=top[v];LL res=0;
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2]) swap(tp1,tp2),swap(u,v);
		res+=SegmentTree::query(1,in[tp1],in[u],1,n);
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]>depth[v]) swap(u,v);
	res+=SegmentTree::query(1,in[u],in[v],1,n);
	return res;
}


inline LL query_subtree(int x)
{
	if (x==rt) return SegmentTree::query(1,1,n,1,n);
	if (!intree(x,rt)) return SegmentTree::query(1,in[x],out[x],1,n);
	int pt=jump(rt,x);return SegmentTree::query(1,1,n,1,n)-SegmentTree::query(1,in[pt],out[pt],1,n);
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	double T=clock();
	cerr<<"Running..."<<endl;
#endif
	Get(n);rep(i,1,n) Get(a[i]);rep(i,2,n) Get(fa[i]),v[fa[i]].pb(i);
	tot=0;depth[1]=1;dfs1(1);dfs2(1,1);SegmentTree::build(1,1,n);
	int q,op,x,y,c;Get(q);
	while (q--)
	{
		Get(op,x);
		if (op==1) {rt=x;continue;}
		if (op==2) Get(y,c),modify_chain(x,y,c);
		if (op==3) Get(c),modify_subtree(x,c);
		if (op==4) Get(y),printf("%lld\n",query_chain(x,y));
		if (op==5) printf("%lld\n",query_subtree(x));
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
