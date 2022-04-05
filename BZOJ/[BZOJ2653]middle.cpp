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
#define pLL pair<LL,LL>
#define pii pair<double,double>
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
  
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
struct node
{
	int val;
	int nx,ind;
	inline bool operator < (const node &x) const {return val<x.val;}
}a[100048];int itot=0;
int table[100048];

int root[100048],tot;
namespace SegmentTree
{
	struct node
	{
		int left,right,lson,rson;
		int sum,lmax,rmax;
	}tree[2000048];
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].sum=tree[cur].lmax=tree[cur].rmax=right-left+1;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			tree[cur].lson=++tot;build(tot,left,mid);
			tree[cur].rson=++tot;build(tot,mid+1,right);
		}
		else
			tree[cur].lson=tree[cur].rson=0;
	}
	inline void pushup(int cur)
	{
		tree[cur].sum=tree[tree[cur].lson].sum+tree[tree[cur].rson].sum;
		tree[cur].lmax=max(tree[tree[cur].lson].lmax,tree[tree[cur].lson].sum+tree[tree[cur].rson].lmax);
		tree[cur].rmax=max(tree[tree[cur].rson].rmax,tree[tree[cur].rson].sum+tree[tree[cur].lson].rmax);
	}
	inline void update(int last,int cur,int pos)
	{
		tree[cur]=tree[last];
		if (tree[cur].left==tree[cur].right)
		{
			tree[cur].sum=-1;
			tree[cur].lmax=tree[cur].rmax=0;
			return;
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid)
		{
			tree[cur].lson=++tot;
			update(tree[last].lson,tree[cur].lson,pos);
		}
		else
		{
			tree[cur].rson=++tot;
			update(tree[last].rson,tree[cur].rson,pos);
		}
		pushup(cur);
	}
	inline int query_sum(int cur,int left,int right)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
		int mid=(tree[cur].left+tree[cur].right)>>1,res=0;
		if (left<=mid) res+=query_sum(tree[cur].lson,left,right);
		if (mid+1<=right) res+=query_sum(tree[cur].rson,left,right);
		return res;
	}
	inline Pair query_lmax(int cur,int left,int right)
	{
		if (left>right) return mp(0,0);
		if (left<=tree[cur].left && tree[cur].right<=right) return mp(tree[cur].lmax,tree[cur].sum);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (right<=mid) return query_lmax(tree[cur].lson,left,right);
		if (left>=mid+1) return query_lmax(tree[cur].rson,left,right);
		Pair res1=query_lmax(tree[cur].lson,left,right),res2=query_lmax(tree[cur].rson,left,right);
		return mp(max(res1.x,res1.y+res2.x),res1.y+res2.y);
	}
	inline Pair query_rmax(int cur,int left,int right)
	{
		if (left>right) return mp(0,0);
		if (left<=tree[cur].left && tree[cur].right<=right) return mp(tree[cur].rmax,tree[cur].sum);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (right<=mid) return query_rmax(tree[cur].lson,left,right);
		if (left>=mid+1) return query_rmax(tree[cur].rson,left,right);
		Pair res1=query_rmax(tree[cur].lson,left,right),res2=query_rmax(tree[cur].rson,left,right);
		return mp(max(res2.x,res2.y+res1.x),res1.y+res2.y);
	}
}

int main ()
{
	int i,q[10],qnum;n=getint();
	for (i=1;i<=n;i++) a[i].val=getint(),a[i].ind=i;
	sort(a+1,a+n+1);
	for (i=1;i<=n;i++)
	{
		if (i==1 || a[i-1].val!=a[i].val) ++itot;
		a[i].nx=itot;table[itot]=a[i].val;
	}
	root[0]=++tot;SegmentTree::build(root[0],1,n);
	int pt=1,pre;
	for (i=1;i<=itot;i++)
	{
		root[i]=root[i-1];
		while (pt<=n && a[pt].nx<i)
		{
			pre=root[i];root[i]=++tot;
			SegmentTree::update(pre,root[i],a[pt].ind);
			pt++;
		}
	}
	int l,r,mid,lastans=0;qnum=getint();
	while (qnum--)
	{
		for (i=1;i<=4;i++) q[i]=(getint()+lastans)%n;
		sort(q+1,q+5);
		for (i=1;i<=4;i++) q[i]++;
		l=1;r=itot;int ans;
		while (l<=r)
		{
			mid=(l+r)>>1;
			int val=SegmentTree::query_sum(root[mid],q[2],q[3])+SegmentTree::query_rmax(root[mid],q[1],q[2]-1).x+SegmentTree::query_lmax(root[mid],q[3]+1,q[4]).x;
			if (val>=0) ans=mid,l=mid+1; else r=mid-1;
		}
		printf("%d\n",table[ans]);
		lastans=table[ans];
	}
	return 0;
}
