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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,L,R,q;
struct Update
{
	int type;
	LL a;
}u[100048];

struct Query
{
	LL val;
	int ind;
	inline bool operator < (const Query &x) const {return val<x.val;}
}a[100048];

int ans[100048];

namespace SegmentTree
{
	struct node
	{
		int left,right;
		LL minn,maxn;
		LL lazysum,lazypro,lazyk;
		LL flushed;
	}tree[400048];
	inline LL calc_min(int cur) {return tree[cur].minn*tree[cur].lazypro+tree[cur].lazysum+tree[cur].lazyk*a[tree[cur].left].val;}
	inline LL calc_max(int cur) {return tree[cur].maxn*tree[cur].lazypro+tree[cur].lazysum+tree[cur].lazyk*a[tree[cur].right].val;}
	inline void pushup(int cur)
	{
		tree[cur].minn=calc_min(cur<<1);
		tree[cur].maxn=calc_max(cur<<1|1);
	}
	inline void pushdown(int cur)
	{
		if (tree[cur].flushed)
		{
			tree[cur<<1].flushed=tree[cur].flushed;
			tree[cur<<1|1].flushed=tree[cur].flushed;
			tree[cur<<1].minn=tree[cur<<1].maxn=tree[cur<<1|1].minn=tree[cur<<1|1].maxn=tree[cur].flushed;
			tree[cur<<1].lazypro=tree[cur<<1|1].lazypro=tree[cur].lazypro;
			tree[cur<<1].lazysum=tree[cur<<1|1].lazysum=tree[cur].lazysum;
			tree[cur<<1].lazyk=tree[cur<<1|1].lazyk=tree[cur].lazyk;
			tree[cur].lazypro=1;tree[cur].lazysum=tree[cur].lazyk=0;tree[cur].flushed=0;
			return;
		}
		tree[cur<<1].lazypro*=tree[cur].lazypro;tree[cur<<1].lazysum*=tree[cur].lazypro;tree[cur<<1].lazyk*=tree[cur].lazypro;
		tree[cur<<1].lazysum+=tree[cur].lazysum;tree[cur<<1].lazyk+=tree[cur].lazyk;
		tree[cur<<1|1].lazypro*=tree[cur].lazypro;tree[cur<<1|1].lazysum*=tree[cur].lazypro;tree[cur<<1|1].lazyk*=tree[cur].lazypro;
		tree[cur<<1|1].lazysum+=tree[cur].lazysum;tree[cur<<1|1].lazyk+=tree[cur].lazyk;
		tree[cur].lazypro=1;tree[cur].lazyk=tree[cur].lazysum=0;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].lazysum=tree[cur].lazyk=tree[cur].flushed=0;tree[cur].lazypro=1;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
			pushup(cur);
		}
		else
			tree[cur].minn=tree[cur].maxn=a[left].val;
	}
	inline void update_add(int cur,int left,int right,int delta)
	{
		if (left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right) {tree[cur].lazysum+=delta;return;}
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update_add(cur<<1,left,right,delta);
		if (mid+1<=right) update_add(cur<<1|1,left,right,delta);
		pushup(cur);
	}
	inline void update_k(int cur,int left,int right,int delta)
	{
		if (left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right) {tree[cur].lazyk+=delta;return;}
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update_k(cur<<1,left,right,delta);
		if (mid+1<=right) update_k(cur<<1|1,left,right,delta);
		pushup(cur);
	}
	inline void update_mul(int cur,int left,int right,int delta)
	{
		if (left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right) {tree[cur].lazysum*=delta;tree[cur].lazyk*=delta;tree[cur].lazypro*=delta;return;}
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update_mul(cur<<1,left,right,delta);
		if (mid+1<=right) update_mul(cur<<1|1,left,right,delta);
		pushup(cur);
	}
	inline void update_flush(int cur,int left,int right,int fnum)
	{
		if (left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			tree[cur].lazysum=tree[cur].lazyk=0;tree[cur].lazypro=1;
			tree[cur].flushed=fnum;tree[cur].minn=tree[cur].maxn=fnum;
			return;
		}
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update_flush(cur<<1,left,right,fnum);
		if (mid+1<=right) update_flush(cur<<1|1,left,right,fnum);
		pushup(cur);
	}
	inline int query_pos(int cur,int cmp)
	{
		if (tree[cur].left==tree[cur].right)
			if (calc_min(cur)<=cmp) return tree[cur].left; else return -1;
		int res;pushdown(cur);
		if (calc_max(cur<<1)<=cmp) res=max(tree[cur<<1].right,query_pos(cur<<1|1,cmp));
		else res=query_pos(cur<<1,cmp);
		pushup(cur);return res;
	}
	inline int query(int cur,int pos)
	{
		if (tree[cur].left==tree[cur].right) return calc_min(cur);
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1,res;
		if (pos<=mid) res=query(cur<<1,pos); else res=query(cur<<1|1,pos);
		pushup(cur);return res;
	}
}

int main ()
{
	char tt[10];int i;
	n=getint();L=getint();R=getint();
	for (i=1;i<=n;i++)
	{
		scanf("%s%d",tt+1,&u[i].a);
		if (tt[1]=='+') u[i].type=1;
		if (tt[1]=='-') u[i].type=2;
		if (tt[1]=='*') u[i].type=3;
		if (tt[1]=='@') u[i].type=4;
	}
	q=getint();
	for (i=1;i<=q;i++) a[i].val=getint(),a[i].ind=i;
	sort(a+1,a+q+1);
	SegmentTree::build(1,1,q);
	for (i=1;i<=n;i++)
	{
		if (u[i].type==1)
		{
			int pos=SegmentTree::query_pos(1,R-u[i].a);
			if (pos==-1) SegmentTree::update_flush(1,1,q,R);
			else {SegmentTree::update_add(1,1,pos,u[i].a);SegmentTree::update_flush(1,pos+1,q,R);}
		}
		if (u[i].type==2)
		{
			int pos=SegmentTree::query_pos(1,L+u[i].a);
			if (pos==-1) SegmentTree::update_add(1,1,q,-u[i].a);
			else {SegmentTree::update_flush(1,1,pos,L);SegmentTree::update_add(1,pos+1,q,-u[i].a);}
		}
		if (u[i].type==3)
		{
			int pos=SegmentTree::query_pos(1,R/u[i].a);
			if (pos==-1) SegmentTree::update_flush(1,1,q,R);
			else {SegmentTree::update_mul(1,1,pos,u[i].a);SegmentTree::update_flush(1,pos+1,q,R);}
		}
		if (u[i].type==4)
		{
			SegmentTree::update_k(1,1,q,u[i].a);
			int pos=SegmentTree::query_pos(1,R);
			if (pos!=-1) SegmentTree::update_flush(1,pos+1,q,R);
		}
	}
	for (i=1;i<=q;i++) ans[a[i].ind]=SegmentTree::query(1,i);
	for (i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
