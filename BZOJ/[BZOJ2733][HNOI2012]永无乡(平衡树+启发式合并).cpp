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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const long double pi=acos(-1);
const int G=3;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline char GetChar()
{
	char ch;
	while (!isalpha(ch=getchar())) {}
	return ch;
}

int n,m,q;
int a[100048],root[100048];
int toind[100048];

namespace DSU
{
	int pre[100048],rnk[100048];
	inline void init() {for (register int i=1;i<=n+10;i++) pre[i]=i,rnk[i]=1;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[y]=x;rnk[x]+=rnk[y];}
}

namespace Treap
{
	struct Treap
	{
		int left,right,sz;
		int val,priority;
	}tree[5000048];int tot=0;
	inline void update(int cur) {tree[cur].sz=1+tree[tree[cur].left].sz+tree[tree[cur].right].sz;}
	inline int Create(int val,int priority,int left,int right)
	{
		tree[++tot]=Treap{left,right,1,val,priority};
		update(tot);return tot;
	}
	inline void init() {tree[0].sz=0;}
	inline void print(int root)
	{
		if (tree[root].left) print(tree[root].left);
		printf("%d ",tree[root].val);
		if (tree[root].right) print(tree[root].right);
	}
	inline Pair split1(int root,int key)
	{
		if (!root) return mp(0,0);
		if (tree[tree[root].left].sz+1>key)
		{
			Pair splitted=split1(tree[root].left,key);
			tree[root].left=splitted.y;
			update(root);return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split1(tree[root].right,key-tree[tree[root].left].sz-1);
			tree[root].right=splitted.x;
			update(root);return mp(root,splitted.y);
		}
	}
	inline Pair split2(int root,int key)
	{
		if (!root) return mp(0,0);
		if (tree[root].val>key)
		{
			Pair splitted=split2(tree[root].left,key);
			tree[root].left=splitted.y;
			update(root);return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split2(tree[root].right,key);
			tree[root].right=splitted.x;
			update(root);return mp(root,splitted.y);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1+root2;
		if (tree[root1].priority<tree[root2].priority)
		{
			tree[root1].right=merge(tree[root1].right,root2);
			update(root1);return root1;
		}
		else
		{
			tree[root2].left=merge(root1,tree[root2].left);
			update(root2);return root2;
		}
	}
	inline void treap_insert(int ind,int val)
	{
		Pair splitted=split2(root[ind],val);
		root[ind]=merge(merge(splitted.x,Create(val,rand(),0,0)),splitted.y);
	}
	inline void Insert(int ind1,int ind2)
	{
		int rt=root[ind2];
		treap_insert(ind1,tree[rt].val);
		if (tree[rt].left) Insert(ind1,tree[rt].left);
		if (tree[rt].right) Insert(ind1,tree[rt].right);
	}
	inline int treap_query(int ind,int key)
	{
		if (tree[root[ind]].sz<key) return -1;
		int &rt=root[ind];
		Pair splitted=split1(rt,key-1);Pair splitted2=split1(splitted.y,1);
		int res=toind[tree[splitted2.x].val];
		rt=merge(merge(splitted.x,splitted2.x),splitted2.y);
		return res;
	}
}


int main ()
{
	int i,x,y;char type;
	n=getint();m=getint();
	memset(root,0,sizeof(root));Treap::init();
	for (i=1;i<=n;i++) a[i]=getint(),toind[a[i]]=i,Treap::treap_insert(i,a[i]);
	DSU::init();
	while (m--)
	{
		x=getint();y=getint();
		x=DSU::find_anc(x);y=DSU::find_anc(y);
		if (x==y) continue;
		if (DSU::rnk[x]<DSU::rnk[y]) swap(x,y);
		Treap::Insert(x,y);DSU::update(x,y);
	}
	q=getint();
	while (q--)
	{
		type=GetChar();x=getint();y=getint();
		if (type=='B')
		{
			x=DSU::find_anc(x);y=DSU::find_anc(y);
			if (x==y) continue;
			if (DSU::rnk[x]<DSU::rnk[y]) swap(x,y);
			Treap::Insert(x,y);DSU::update(x,y);
		}
		else
		{
			x=DSU::find_anc(x);
			printf("%d\n",Treap::treap_query(x,y));
		}
	}
	return 0;
}
