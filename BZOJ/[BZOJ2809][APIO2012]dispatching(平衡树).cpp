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
 
const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;
const int lim=1e9;
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m;
vector<int> v[100048];
int c[100048],L[100048];

int root[100048],tot=0;
namespace Treap
{
	struct Treap
	{
		int left,right,val,priority;
		int sz;LL sum;
		Treap () {}
		inline Treap(int x1,int x2,int x3,int x4,int x5,int x6)
		{
			left=x1;right=x2;val=x3;priority=x4;sz=x5;sum=x6;
		}
	}tree[1000048];
	inline int Create(int val,int priority,int left,int right)
	{
		++tot;tree[tot]=Treap(left,right,val,priority,1,val);
		return tot;
	}
	inline void update(int cur)
	{
		tree[cur].sz=tree[tree[cur].left].sz+tree[tree[cur].right].sz+1;
		tree[cur].sum=tree[tree[cur].left].sum+tree[tree[cur].right].sum+tree[cur].val;
	}
	inline Pair split(int root,int key)
	{
		if (!root) return mp(0,0);
		LL lsum=tree[tree[root].left].sum+tree[root].val;
		if (lsum>key)
		{
			Pair splitted=split(tree[root].left,key);
			tree[root].left=splitted.y;update(root);
			return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split(tree[root].right,key-lsum);
			tree[root].right=splitted.x;update(root);
			return mp(root,splitted.y);
		}
	}
	inline Pair split2(int root,int key)
	{
		if (!root) return mp(0,0);
		if (tree[root].val>=key)
		{
			Pair splitted=split2(tree[root].left,key);
			tree[root].left=splitted.y;update(root);
			return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split2(tree[root].right,key);
			tree[root].right=splitted.x;update(root);
			return mp(root,splitted.y);
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
	inline int Insert(int root1,int root2)
	{
		Pair splitted=split2(root1,tree[root2].val);
		return merge(merge(splitted.x,root2),splitted.y);
	}
	inline void Merge(int ind,int root2)
	{
		//root[ind]=Insert(root[ind],root2);
		if (tree[root2].left) Merge(ind,tree[root2].left);
		if (tree[root2].right) Merge(ind,tree[root2].right);
		tree[root2].left=tree[root2].right=0;tree[root2].sz=1;tree[root2].sum=tree[root2].val;
		root[ind]=Insert(root[ind],root2);
	}
}

LL ans=0;

inline void dfs(int cur,int father)
{
	if (int(v[cur].size())==1 && father)
	{
		root[cur]=Treap::Create(c[cur],rand(),0,0);
		if (c[cur]<=m) ans=max(ans,(long long)L[cur]);
		return;
	}
	int i,y,maxsz=0,maxind;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			dfs(y,cur);
			if (Treap::tree[root[y]].sz>maxsz)
			{
				maxsz=Treap::tree[root[y]].sz;
				maxind=y;
			}
		}
	}
	root[cur]=Treap::Create(c[cur],rand(),0,0);
	root[cur]=Treap::Insert(root[maxind],root[cur]);
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father && y!=maxind) Treap::Merge(cur,root[y]);
	}
	Pair splitted=Treap::split(root[cur],m);root[cur]=splitted.x;
	ans=max(ans,(long long)L[cur]*Treap::tree[root[cur]].sz);
}

int main ()
{
	int i,x;n=getint();m=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();c[i]=getint();L[i]=getint();
		if (x) v[i].pb(x),v[x].pb(i);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
