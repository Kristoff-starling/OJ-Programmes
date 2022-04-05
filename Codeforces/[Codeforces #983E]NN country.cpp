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
using namespace std;
 
const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,q;
vector<int> v[200048];
vector<int> vv[200048];
vector<Pair> qq[200048];
int bef[200048];
int ans[200048];
Pair a[200048];

int seq[200048],pos[200048],ind=0;
int L[200048],R[200048],depth[200048];
int anc[200048][21];Pair jump[200048][21];

inline void dfs(int cur,int father)
{
	seq[++ind]=cur;pos[cur]=ind;L[cur]=ind;
	int i,j,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
	R[cur]=ind;
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

namespace SegmentTree
{
	struct node
	{
		int left,right;
		int minn,minind;
	}tree[1000048];
	inline void pushup(int cur)
	{
		if (tree[cur<<1].minn<=tree[cur<<1|1].minn)
		{
			tree[cur].minn=tree[cur<<1].minn;
			tree[cur].minind=tree[cur<<1].minind;
		}
		else
		{
			tree[cur].minn=tree[cur<<1|1].minn;
			tree[cur].minind=tree[cur<<1|1].minind;
		}
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
			pushup(cur);
		}
		else
		{
			tree[cur].minn=depth[seq[left]];
			tree[cur].minind=seq[left];
		}
	}
	inline void update(int cur,int pos,int newval,int newind)
	{
		if (tree[cur].left==tree[cur].right)
		{
			if (newval<tree[cur].minn)
			{
				tree[cur].minn=newval;
				tree[cur].minind=newind;
			}
			return;
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) update(cur<<1,pos,newval,newind); else update(cur<<1|1,pos,newval,newind);
		pushup(cur);
	}
	inline Pair query(int cur,int left,int right)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) return mp(tree[cur].minn,tree[cur].minind);
		int mid=(tree[cur].left+tree[cur].right)>>1;Pair res1=mp(INF,INF),res2=mp(INF,INF);
		if (left<=mid) res1=query(cur<<1,left,right);
		if (mid+1<=right) res2=query(cur<<1|1,left,right);
		return min(res1,res2);
	}
}

namespace BIT
{
	int c[400048];
	inline void init() {memset(c,0,sizeof(c));}
	inline void update(int x,int delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
	inline int calc(int left,int right) {return query(right)-query(left-1);}
}

inline void Dfs(int cur,int father)
{
	int i,y;
	for (i=0;i<int(qq[cur].size());i++)
		bef[qq[cur][i].y]=BIT::calc(L[qq[cur][i].x],R[qq[cur][i].x]);
	for (i=0;i<int(vv[cur].size());i++)
		BIT::update(pos[vv[cur][i]],1);
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father) Dfs(y,cur);
	}
	for (i=0;i<int(qq[cur].size());i++)
		if (BIT::calc(L[qq[cur][i].x],R[qq[cur][i].x])!=bef[qq[cur][i].y] || (getlca(cur,qq[cur][i].x)==cur && jump[qq[cur][i].x][0].x<=depth[cur])) ans[qq[cur][i].y]++; else ans[qq[cur][i].y]+=2;
}

int main ()
{
	int i,j,x,y,LCA;n=getint();
	for (i=2;i<=n;i++)
	{
		x=getint();
		v[x].pb(i);v[i].pb(x);
	}
	depth[1]=1;dfs(1,-1);
	SegmentTree::build(1,1,n);
	m=getint();
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();
		vv[x].pb(y);vv[y].pb(x);
		LCA=getlca(x,y);
		SegmentTree::update(1,pos[x],depth[LCA],LCA);
		SegmentTree::update(1,pos[y],depth[LCA],LCA);
	}
	for (i=1;i<=n;i++) jump[i][0]=SegmentTree::query(1,L[i],R[i]);
	for (j=1;j<=20;j++)
		for (i=1;i<=n;i++)
			jump[i][j]=jump[jump[i][j-1].y][j-1];
	q=getint();
	int cur,cnt1,cnt2,pt1,pt2;
	for (register int qnum=1;qnum<=q;qnum++)
	{
		x=getint();y=getint();LCA=getlca(x,y);
		cnt1=0;cur=x;
		for (i=20;i>=0;i--)
			if (jump[cur][i].x>depth[LCA]) cnt1+=(1<<i),cur=jump[cur][i].y;
		if (jump[cur][0].x>depth[LCA]) {ans[qnum]=-1;continue;}
		pt1=cur;
		cnt2=0;cur=y;
		for (i=20;i>=0;i--)
			if (jump[cur][i].x>depth[LCA]) cnt2+=(1<<i),cur=jump[cur][i].y;
		if (jump[cur][0].x>depth[LCA]) {ans[qnum]=-1;continue;}
		pt2=cur;
		if (depth[pt1]>depth[pt2]) swap(pt1,pt2);
		ans[qnum]=cnt1+cnt2;a[qnum]=mp(pt1,pt2);
		qq[pt1].pb(mp(pt2,qnum));
	}
	BIT::init();
	Dfs(1,-1);
	for (i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
