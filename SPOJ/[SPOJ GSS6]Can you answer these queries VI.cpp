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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,q;

struct Treap
{
	int left,right,priority,sz;
	LL lmax,rmax,sum,maxn,val;
}tree[1000048];int Root,tot=0;

inline void update(int cur)
{
	int lson=tree[cur].left,rson=tree[cur].right;
	tree[cur].sz=(lson!=-1?tree[lson].sz:0)+(rson!=-1?tree[rson].sz:0)+1;
	tree[cur].sum=(lson!=-1?tree[lson].sum:0)+(rson!=-1?tree[rson].sum:0)+tree[cur].val;
	tree[cur].lmax=max(max((lson!=-1?tree[lson].lmax:-LINF),(lson!=-1?tree[lson].sum:0)+tree[cur].val),(lson!=-1?tree[lson].sum:0)+tree[cur].val+(rson!=-1?tree[rson].lmax:0));
	tree[cur].rmax=max(max((rson!=-1?tree[rson].rmax:-LINF),(rson!=-1?tree[rson].sum:0)+tree[cur].val),(rson!=-1?tree[rson].sum:0)+tree[cur].val+(lson!=-1?tree[lson].rmax:0));
	tree[cur].maxn=max(max(max((lson!=-1?tree[lson].maxn:-LINF),(rson!=-1?tree[rson].maxn:-LINF)),tree[cur].val),max(max(tree[cur].val+(lson!=-1?tree[lson].rmax:0),tree[cur].val+(rson!=-1?tree[rson].lmax:0)),tree[cur].val+(lson!=-1?tree[lson].rmax:0)+(rson!=-1?tree[rson].lmax:0)));
}

inline int Create(int val,int priority,int left,int right)
{
	int res=++tot;tree[res].sz=1;
	tree[res].val=tree[res].lmax=tree[res].rmax=tree[res].sum=tree[res].maxn=val;
	tree[res].priority=priority;
	tree[res].left=left;tree[res].right=right;
	return res;
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
	if (LeftSize(root)>key)
	{
		Pair splitted=split(tree[root].left,key);
		tree[root].left=splitted.y;update(root);
		return mp(splitted.x,root);
	}
	else
	{
		Pair splitted=split(tree[root].right,key-LeftSize(root));
		tree[root].right=splitted.x;update(root);
		return mp(root,splitted.y);
	}
}

inline int merge(int root1,int root2)
{
	if (root1==-1) return root2;
	if (root2==-1) return root1;
	if (tree[root1].priority<=tree[root2].priority)
	{
		tree[root1].right=merge(tree[root1].right,root2);
		update(root1);
		return root1;
	}
	else
	{
		tree[root2].left=merge(root1,tree[root2].left);
		update(root2);
		return root2;
	}
}

inline void treap_insert(int pos,int val)
{
	Pair splitted=split(Root,pos-1);
	Root=merge(merge(splitted.x,Create(val,rand(),-1,-1)),splitted.y);
}

inline void treap_delete(int pos)
{
	Pair splitted=split(Root,pos-1);Pair splitted2=split(splitted.y,1);
	Root=merge(splitted.x,splitted2.y);
}

inline void treap_replace(int pos,int newval)
{
	Pair splitted=split(Root,pos-1);Pair splitted2=split(splitted.y,1);
	Root=merge(merge(splitted.x,Create(newval,rand(),-1,-1)),splitted2.y);
}

inline LL treap_query(int left,int right)
{
	Pair splitted=split(Root,left-1);Pair splitted2=split(splitted.y,right-left+1);
	LL res=tree[splitted2.x].maxn;
	Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
	return res;
}

int main ()
{
	int i;char type[5];int x,y;
	n=getint();x;Root=-1;
	for (i=1;i<=n;i++) x=getint(),Root=merge(Root,Create(x,rand(),-1,-1));
	q=getint();
	while (q--)
	{
		scanf("%s",type+1);x=getint();if (type[1]!='D') y=getint();
		if (type[1]=='I') treap_insert(x,y);
		if (type[1]=='D') treap_delete(x);
		if (type[1]=='R') treap_replace(x,y);
		if (type[1]=='Q') printf("%lld\n",treap_query(x,y));
	}
	return 0;
}
