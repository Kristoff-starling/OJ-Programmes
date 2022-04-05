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
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
#define DEBUG(...)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
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
int a[100048];
int sz[100048],son[100048],depth[100048],top[100048],fa[100048];
int toind[100048],totree[100048],ind=0;

int head[100048],nxt[300048],to[300048],etot=1;
inline void addedge(int s,int t)
{
	to[++etot]=t;nxt[etot]=head[s];head[s]=etot;
}

namespace SegmentTree
{
	struct node
	{
		int left,right;
		LL lmax,rmax,maxn,sum,flushed;
	}tree[600048];
	inline void pushdown(int cur)
	{
		if (tree[cur].flushed!=INF)
		{
			tree[cur<<1].flushed=tree[cur].flushed;
			tree[cur<<1].lmax=tree[cur<<1].rmax=tree[cur<<1].maxn=(tree[cur].flushed>=0?tree[cur].flushed*(tree[cur<<1].right-tree[cur<<1].left+1):0);
			tree[cur<<1].sum=tree[cur<<1].flushed*(tree[cur<<1].right-tree[cur<<1].left+1);
			tree[cur<<1|1].flushed=tree[cur].flushed;
			tree[cur<<1|1].lmax=tree[cur<<1|1].rmax=tree[cur<<1|1].maxn=(tree[cur].flushed>=0?tree[cur].flushed*(tree[cur<<1|1].right-tree[cur<<1|1].left+1):0);
			tree[cur<<1|1].sum=tree[cur<<1|1].flushed*(tree[cur<<1|1].right-tree[cur<<1|1].left+1);
		}
	}
	inline void pushup(int cur)
	{
		tree[cur].lmax=max(tree[cur<<1].lmax,tree[cur<<1].sum+tree[cur<<1|1].lmax);
		tree[cur].rmax=max(tree[cur<<1|1].rmax,tree[cur<<1|1].sum+tree[cur<<1].rmax);
		tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
		tree[cur].maxn=max(max(tree[cur<<1].maxn,tree[cur<<1|1].maxn),tree[cur<<1].rmax+tree[cur<<1|1].lmax);
		if (tree[cur<<1].flushed!=INF && tree[cur<<1].flushed==tree[cur<<1|1].flushed) tree[cur].flushed=tree[cur<<1].flushed; else tree[cur].flushed=INF;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);
			build(cur<<1|1,mid+1,right);
			pushup(cur);
		}
		else
		{
			tree[cur].sum=a[toind[left]];
			tree[cur].lmax=tree[cur].rmax=tree[cur].maxn=max(a[toind[left]],0);
			tree[cur].flushed=a[toind[left]];
		}
	}
	inline void update(int cur,int left,int right,int newval)
	{
		if (tree[cur].right<left || tree[cur].left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			tree[cur].flushed=newval;
			tree[cur].sum=tree[cur].flushed*(tree[cur].right-tree[cur].left+1);
			tree[cur].lmax=tree[cur].rmax=tree[cur].maxn=(tree[cur].flushed>=0?tree[cur].flushed*(tree[cur].right-tree[cur].left+1):0);
			return;
		}
		pushdown(cur);
		update(cur<<1,left,right,newval);update(cur<<1|1,left,right,newval);
		pushup(cur);
	}
	inline node query(int cur,int left,int right)
	{
		node res,res1,res2;res.left=-1;
		if (tree[cur].right<left || tree[cur].left>right) return res;
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur];
		pushdown(cur);
		res1=query(cur<<1,left,right);res2=query(cur<<1|1,left,right);
		if (res1.left==-1) return res2;
		if (res2.left==-1) return res1;
		res.lmax=max(res1.lmax,res1.sum+res2.lmax);
		res.rmax=max(res2.rmax,res2.sum+res1.rmax);
		res.maxn=max(max(res1.maxn,res2.maxn),res1.rmax+res2.lmax);
		res.sum=res1.sum+res2.sum;
		res.left=1;
		pushup(cur);
		return res;
	}
};

inline void dfs1(int cur,int father)
{
	sz[cur]=1;fa[cur]=father;son[cur]=0;int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			dfs1(y,cur);
			sz[cur]+=sz[y];
			if (!son[cur] || sz[son[cur]]<sz[y]) son[cur]=y;
		}
	}
}

inline void dfs2(int cur,int tp)
{
	top[cur]=tp;toind[++ind]=cur;totree[cur]=ind;
	if (son[cur]) dfs2(son[cur],tp);
	for (int i=head[cur];i;i=nxt[i])
	{
		int	y=to[i];
		if (y!=fa[cur] && y!=son[cur]) dfs2(y,y);
	}
}

inline LL calc_query(int u,int v)
{
	typedef SegmentTree::node node;
	node resu,resv,curres,tmpres;resu.left=-1;resv.left=-1;
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
			swap(resu,resv);
		}
		curres=SegmentTree::query(1,totree[tp1],totree[u]);
		if (resu.left==-1) 
			resu=curres;
		else
		{
			tmpres.left=1;
			tmpres.sum=curres.sum+resu.sum;
			tmpres.lmax=max(curres.lmax,curres.sum+resu.lmax);
			tmpres.rmax=max(resu.rmax,resu.sum+curres.rmax);
			tmpres.maxn=max(max(curres.maxn,resu.maxn),curres.rmax+resu.lmax);
			resu=tmpres;
		}
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]<depth[v]) swap(u,v),swap(resu,resv);
	curres=SegmentTree::query(1,totree[v],totree[u]);
	swap(resu.lmax,resu.rmax);swap(curres.lmax,curres.rmax);
	if (resu.left==-1)
	{
		resu=curres;
		resu.left=1;
	}
	else
	{
		tmpres.lmax=max(resu.lmax,resu.sum+curres.lmax);
		tmpres.rmax=max(curres.rmax,curres.sum+resu.rmax);
		tmpres.sum=curres.sum+resu.sum;
		tmpres.maxn=max(max(curres.maxn,resu.maxn),resu.rmax+curres.lmax);
		resu=tmpres;
	}
	if (resv.left==-1) return resu.maxn;
	tmpres.maxn=max(max(resu.maxn,resv.maxn),resu.rmax+resv.lmax);
	return tmpres.maxn;
}

inline void calc_update(int u,int v,int c)
{
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
		}
		SegmentTree::update(1,totree[tp1],totree[u],c);
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]<depth[v]) swap(u,v);
	SegmentTree::update(1,totree[v],totree[u],c);
}

int main ()
{
	int i,x,y,type,c;
	n=getint();for (i=1;i<=n;i++) a[i]=getint();
	memset(head,0,sizeof(head));
	for (i=1;i<=n-1;i++) x=getint(),y=getint(),addedge(x,y),addedge(y,x);
	depth[1]=1;dfs1(1,-1);dfs2(1,1);
	SegmentTree::build(1,1,n);
	q=getint();
	while (q--)
	{
		type=getint();x=getint();y=getint();if (type==2) c=getint();
		if (type==1) printf("%lld\n",calc_query(x,y)); else calc_update(x,y,c);
	}
	return 0;
}
