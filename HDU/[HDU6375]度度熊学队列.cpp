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

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=5e5;

int n,q;

int root[MAXN+48];
namespace Treap
{
	struct node
	{
		int val,priority,left,right;
		int sz,flip;
		node () {}
		inline node (int vv,int pp,int ll,int rr,int ss,int ff)
		{
			val=vv;priority=pp;left=ll;right=rr;sz=ss;flip=ff;
		}
	}tree[MAXN*2];int tot;
	inline void init() {tot=0;for (register int i=1;i<=n;i++) root[i]=0;}
	inline void pushdown(int cur)
	{
		if (tree[cur].flip)
		{
			tree[tree[cur].left].flip^=1;
			tree[tree[cur].right].flip^=1;
			swap(tree[cur].left,tree[cur].right);
			tree[cur].flip=0;
		}
	}
	inline void pushup(int cur)
	{
		tree[cur].sz=tree[tree[cur].left].sz+tree[tree[cur].right].sz+1;
	}
	inline int Create(int left,int right,int val,int priority)
	{
		++tot;
		tree[tot]=node(val,priority,left,right,1,0);
		return tot;
	}
	inline Pair split(int root,int k)
	{
		if (!root) return mp(0,0);
		pushdown(root);
		int leftsz=tree[tree[root].left].sz+1;
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
		if (!root1 || !root2) return root1+root2;
		pushdown(root1);pushdown(root2);
		if (tree[root1].priority<tree[root2].priority)
		{
			tree[root1].right=merge(tree[root1].right,root2);
			pushup(root1);return root1;
		}
		else
		{
			tree[root2].left=merge(root1,tree[root2].left);
			pushup(root2);return root2;
		}
	}
	inline void insert_head(int &root,int val)
	{
		root=merge(Create(0,0,val,rand()),root);
	}
	inline void insert_tail(int &root,int val)
	{
		root=merge(root,Create(0,0,val,rand()));
	}
	inline int query_head(int &root)
	{
		if (tree[root].sz==0) return -1;
		Pair splitted=split(root,1);
		root=splitted.y;return tree[splitted.x].val;
	}
	inline int query_tail(int &root)
	{
		int Sz=tree[root].sz;
		if (!Sz) return -1;
		Pair splitted=split(root,Sz-1);
		root=splitted.x;return tree[splitted.y].val;
	}
	inline void Reverse(int root) {tree[root].flip^=1;}
}

int main ()
{
	int op,u,w,v;
	while (scanf("%d%d",&n,&q)!=EOF)
	{
		Treap::init();
		while (q--)
		{
			op=getint();
			if (op==1)
			{
				u=getint();w=getint();v=getint();
				if (!w) Treap::insert_head(root[u],v); else Treap::insert_tail(root[u],v);
			}
			if (op==2)
			{
				u=getint();w=getint();
				if (!w) printf("%d\n",Treap::query_head(root[u])); else printf("%d\n",Treap::query_tail(root[u]));
			}
			if (op==3)
			{
				u=getint();v=getint();w=getint();
				if (w) Treap::Reverse(root[v]);
				root[u]=Treap::merge(root[u],root[v]);
				root[v]=0;
			}
		}
	}
	return 0;
}
