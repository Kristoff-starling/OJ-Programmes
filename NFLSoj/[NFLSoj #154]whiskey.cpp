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

int n,p,q,r;

struct node
{
	int a,b,c;
	inline bool operator < (const node &x) const {return a<x.a;}
}a[500048];

int sufbmax[500048],sufcmax[500048];

namespace SegmentTree
{
	struct node
	{
		int left,right,len;
		int maxn,flushed;
		LL sum;
	}tree[2000048];
	inline void pushdown(int cur)
	{
		if (tree[cur].flushed)
		{
			tree[cur<<1].flushed=tree[cur].flushed;
			tree[cur<<1].maxn=tree[cur].flushed;
			tree[cur<<1].sum=(long long)(r-tree[cur].flushed+1)*tree[cur<<1].len;
			tree[cur<<1|1].flushed=tree[cur].flushed;
			tree[cur<<1|1].maxn=tree[cur].flushed;
			tree[cur<<1|1].sum=(long long)(r-tree[cur].flushed+1)*tree[cur<<1|1].len;
			tree[cur].flushed=0;
		}
	}
	inline void pushup(int cur)
	{
		tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
		tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;tree[cur].len=right-left+1;
		tree[cur].maxn=1;tree[cur].flushed=0;
		tree[cur].sum=(long long)r*tree[cur].len;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
	}
	inline int query_pos(int cur,int left,int right,int cmp)
	{
		if (left>right) return -1;
		if (tree[cur].left==tree[cur].right)
		{
			if (tree[cur].maxn>=cmp) return -1; else return tree[cur].left;
		}
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1,res;
		if (right<=mid)
		{
			res=query_pos(cur<<1,left,right,cmp);
			pushup(cur);return res;
		}
		if (left>=mid+1)
		{
			res=query_pos(cur<<1|1,left,right,cmp);
			pushup(cur);return res;
		}
		if (tree[cur<<1|1].maxn>cmp)
		{
			res=query_pos(cur<<1|1,left,right,cmp);
			pushup(cur);return res;
		}
		res=query_pos(cur<<1,left,right,cmp);
		if (res==-1) res=mid+1;
		pushup(cur);return res;
	}
	inline void update(int cur,int left,int right,int newval)
	{
		if (left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			tree[cur].maxn=tree[cur].flushed=newval;
			tree[cur].sum=(long long)(r-tree[cur].flushed+1)*tree[cur].len;
			return;
		}
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update(cur<<1,left,right,newval);
		if (mid+1<=right) update(cur<<1|1,left,right,newval);
		pushup(cur);
	}
	inline LL query(int cur,int left,int right)
	{
		if (left>right) return 0;
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		LL res=0;
		if (left<=mid) res+=query(cur<<1,left,right);
		if (mid+1<=right) res+=query(cur<<1|1,left,right);
		pushup(cur);
		return res;
	}
}

int main ()
{
	int i,pt=0;LL ans=0;n=getint();p=getint();q=getint();r=getint();
	for (i=1;i<=n;i++) a[i].a=getint(),a[i].b=getint(),a[i].c=getint();
	sort(a+1,a+n+1);
	sufbmax[n]=a[n].b;sufcmax[n]=a[n].c;
	for (i=n-1;i>=1;i--) sufbmax[i]=max(sufbmax[i+1],a[i].b),sufcmax[i]=max(sufcmax[i+1],a[i].c);
	SegmentTree::build(1,1,q);
	for (i=1;i<=p;i++)
	{
		while (pt<n && a[pt+1].a<i)
		{
			pt++;
			int pos=SegmentTree::query_pos(1,1,a[pt].b,a[pt].c+1);
			if (pos!=-1) SegmentTree::update(1,pos,a[pt].b,a[pt].c+1);
		}
		int pos=SegmentTree::query_pos(1,sufbmax[pt+1]+1,q,sufcmax[pt+1]+1);
		if (pos==-1) pos=q+1;
		ans+=SegmentTree::query(1,sufbmax[pt+1]+1,pos-1);
		pos=max(pos,sufbmax[pt+1]+1);
		ans+=(long long)(q-pos+1)*(r-(sufcmax[pt+1]+1)+1);
	}
	printf("%lld\n",ans);
	return 0;
}
