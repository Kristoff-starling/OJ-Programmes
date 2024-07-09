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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

const int MAXN=1e5;

int n,q;

inline LL Q(LL x)
{
	LL res=1;
	while (res<x) res*=42;
	return res;
}

namespace Treap
{
	struct node
	{
		LL val;int cnt,priority,left,right;
		LL nval,minn,lazy;int sz;
	}tree[MAXN*10];int tot,Root;
	inline void init() {tot=0;Root=0;tree[0].minn=LINF;tree[0].sz=0;}
	inline void pushdown(int cur)
	{
		if (tree[cur].lazy)
		{
			tree[tree[cur].left].lazy+=tree[cur].lazy;
			tree[tree[cur].left].val+=tree[cur].lazy;
			tree[tree[cur].left].minn-=tree[cur].lazy;
			tree[tree[cur].left].nval-=tree[cur].lazy;
			tree[tree[cur].right].lazy+=tree[cur].lazy;
			tree[tree[cur].right].val+=tree[cur].lazy;
			tree[tree[cur].right].minn-=tree[cur].lazy;
			tree[tree[cur].right].nval-=tree[cur].lazy;
			tree[cur].lazy=0;
		}
	}
	inline void pushup(int cur)
	{
		tree[cur].minn=tree[cur].nval;
		if (tree[cur].left) tree[cur].minn=min(tree[cur].minn,tree[tree[cur].left].minn);
		if (tree[cur].right) tree[cur].minn=min(tree[cur].minn,tree[tree[cur].right].minn);
		tree[cur].sz=tree[tree[cur].left].sz+tree[tree[cur].right].sz+tree[cur].cnt;
	}
	inline int Create(LL val,int cnt,int priority,int left,int right)
	{
		++tot;
		tree[tot].val=val;tree[tot].cnt=cnt;tree[tot].priority=priority;tree[tot].left=left;tree[tot].right=right;
		tree[tot].nval=Q(tree[tot].val)-tree[tot].val;
		pushup(tot);return tot;
	}
	inline Pair findnode(int root,LL k)
	{
		LL leftsz=tree[tree[root].left].sz;
		pushdown(root);Pair res;
		if (leftsz>=k) res=findnode(tree[root].left,k);
		else if (leftsz<k && leftsz+tree[root].cnt>=k) res=mp(root,k-leftsz);
		else res=findnode(tree[root].right,k-leftsz-tree[root].cnt);
		pushup(root);return res;
	}
	inline Pair split(int root,LL k)
	{
		if (!root) return mp(0,0);
		pushdown(root);
		LL leftsz=tree[tree[root].left].sz+tree[root].cnt;
		if (k>=leftsz)
		{
			Pair splitted=split(tree[root].right,k-leftsz);
			tree[root].right=splitted.x;pushup(root);
			return mp(root,splitted.y);
		}
		else
		{
			Pair splitted=split(tree[root].left,k);
			tree[root].left=splitted.y;pushup(root);
			return mp(splitted.x,root);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1^root2;
		if (tree[root1].priority<=tree[root2].priority)
		{
			pushdown(root1);
			tree[root1].right=merge(tree[root1].right,root2);
			pushup(root1);return root1;
		}
		else
		{
			pushdown(root2);
			tree[root2].left=merge(root1,tree[root2].left);
			pushup(root2);return root2;
		}
	}
	inline void update(int root)
	{
		if (tree[root].nval<0) tree[root].nval=Q(tree[root].val)-tree[root].val;
		pushdown(root);
		if (tree[root].left && tree[tree[root].left].minn<0) update(tree[root].left);
		if (tree[root].right && tree[tree[root].right].minn<0) update(tree[root].right);
		pushup(root);
	}
	inline void doit(int p)
	{
		if (!p) return;
		Pair res=findnode(Root,p);
		if (res.y!=tree[res.x].cnt)
		{
			int le=tree[res.x].cnt;LL va=tree[res.x].val;
			Pair splitted=split(Root,p-res.y);
			Pair splitted2=split(splitted.y,le);
			Root=merge(merge(splitted.x,Create(va,res.y,rand(),0,0)),merge(Create(va,le-res.y,rand(),0,0),splitted2.y));
		}
	}
	inline void modify(int L,int R,int delta)
	{
		doit(L-1);doit(R);
		Pair splitted=split(Root,L-1);
		Pair splitted2=split(splitted.y,R-L+1);
		tree[splitted2.x].lazy+=delta;tree[splitted2.x].val+=delta;tree[splitted2.x].nval-=delta;tree[splitted2.x].minn-=delta;
		Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
	}
	inline void Set(int L,int R,int nv)
	{
		doit(L-1);doit(R);
		Pair splitted=split(Root,L-1);
		Pair splitted2=split(splitted.y,R-L+1);
		Root=merge(merge(splitted.x,Create(nv,R-L+1,rand(),0,0)),splitted2.y);
	}
	inline LL query(int pos)
	{
		doit(pos-1);doit(pos);
		Pair splitted=split(Root,pos-1);
		Pair splitted2=split(splitted.y,1);
		LL res=tree[splitted2.x].val;
		Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
		return res;
	}
	inline void insert(LL val)
	{
		Root=merge(Root,Create(val,1,rand(),0,0));
	}
}

int main ()
{
	scanf("%d%d",&n,&q);
	int l,r,x,op;
	Treap::init();
	for (register int i=1;i<=n;i++) scanf("%d",&x),Treap::insert(x);
	while (q--)
	{
		assert(Treap::tot<=MAXN*10);
		scanf("%d",&op);
		if (op==1)
		{
			scanf("%d",&x);
			printf("%lld\n",Treap::query(x));
		}
		if (op==2)
		{
			scanf("%d%d%d",&l,&r,&x);
			Treap::Set(l,r,x);
		}
		if (op==3)
		{
			scanf("%d%d%d",&l,&r,&x);
			do
			{
				Treap::modify(l,r,x);
				Treap::update(Treap::Root);
			}
			while (Treap::tree[Treap::Root].minn==0);
		}
	}
	return 0;
}
