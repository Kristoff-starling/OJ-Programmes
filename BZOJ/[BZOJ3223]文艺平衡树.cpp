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

int n,m;

struct Treap
{
	int left,right;
	int val,priority;
	int flip;int sz;
}tree[300048];int tot=0,Root=0;

inline void pushdown(int cur)
{
	if (tree[cur].flip)
	{
		if (tree[cur].left!=-1) tree[tree[cur].left].flip^=1;
		if (tree[cur].right!=-1) tree[tree[cur].right].flip^=1;
		tree[cur].flip^=1;swap(tree[cur].left,tree[cur].right);
	}
}

inline void update(int cur)
{
	tree[cur].sz=1;
	if (tree[cur].left!=-1) tree[cur].sz+=tree[tree[cur].left].sz;
	if (tree[cur].right!=-1) tree[cur].sz+=tree[tree[cur].right].sz;
}

inline void print(int cur)
{
	if (cur==-1) return;
	pushdown(cur);
	if (tree[cur].left!=-1) print(tree[cur].left);
	printf("%d ",tree[cur].val);
	if (tree[cur].right!=-1) print(tree[cur].right);
}

inline int Create(int val,int priority,int left,int right)
{
	++tot;tree[tot]=Treap{left,right,val,priority,false,1};
	return tot;
}

inline int LeftSize(int cur)
{
	int res=1;
	if (tree[cur].left!=-1) res+=tree[tree[cur].left].sz;
	return res;
}

inline Pair split(int root,int key)
{
	if (root==-1) return mp(-1,-1);
	pushdown(root);
	if (LeftSize(root)>key)
	{
		Pair splitted=split(tree[root].left,key);
		tree[root].left=splitted.y;update(root);
		return mp(splitted.x,root);
	}
	else
	{
		Pair splitted=split(tree[root].right,key-LeftSize(root));
		tree[root].right=splitted.x,update(root);
		return mp(root,splitted.y);
	}
}

inline int merge(int root1,int root2)
{
	if (root1==-1) return root2;
	if (root2==-1) return root1;
	if (tree[root1].priority<tree[root2].priority)
	{
		pushdown(root1);
		tree[root1].right=merge(tree[root1].right,root2);
		update(root1);
		return root1;
	}
	else
	{
		pushdown(root2);
		tree[root2].left=merge(root1,tree[root2].left);
		update(root2);
		return root2;
	}
}

inline void treap_insert(int val)
{
	Root=merge(Root,Create(val,rand(),-1,-1));
}

inline void treap_reverse(int left,int right)
{
	Pair splitted=split(Root,left-1);
	Pair splitted2=split(splitted.y,right-left+1);
	tree[splitted2.x].flip^=1;Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
}

int main ()
{
	int i,l,r;n=getint();m=getint();Root=-1;
	for (i=1;i<=n;i++) treap_insert(i);
	while (m--)
	{
		l=getint();r=getint();
		treap_reverse(l,r);
	}
	print(Root);return 0;
}

