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

int w,h,n,itot,ans=0;
struct node
{
	int x,y,ny;
}a[300048];

inline bool cmpy(node x,node y) {return x.y<y.y;}
int pos[300048];

namespace SegmentTree
{
	struct node
	{
		int left,right;
		int maxn,lazy;
	}tree[1200048];
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].maxn=tree[cur].lazy=0;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
	}
	inline void pushdown(int cur)
	{
		tree[cur<<1].lazy+=tree[cur].lazy;
		tree[cur<<1|1].lazy+=tree[cur].lazy;
		tree[cur].lazy=0;
	}
	inline void pushup(int cur)
	{
		tree[cur].maxn=max(tree[cur<<1].maxn+tree[cur<<1].lazy,tree[cur<<1|1].maxn+tree[cur<<1|1].lazy);
	}
	inline void update(int cur,int left,int right,int add)
	{
		if (left>right) return;
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			tree[cur].lazy+=add;
			return;
		}
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update(cur<<1,left,right,add);
		if (mid+1<=right) update(cur<<1|1,left,right,add);
		pushup(cur);
	}
	/*
	inline int query(int cur,int left,int right)
	{
		if (left>right) return 0;
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].maxn+tree[cur].lazy;
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1,res=-1;
		if (left<=mid) res=max(res,query(cur<<1,left,right));
		if (mid+1<=right) res=max(res,query(cur<<1|1,left,right));
		pushup(cur);
		return res;
	}*/
}

Pair s1[300048],s2[300048];
inline void solve()
{
	sort(a+1,a+n+1,cmpy);
	SegmentTree::build(1,1,n);
	int Mid=w/2,s1tot=0,s2tot=0,a1tot=0,a2tot=0,i,posleft,posright;
	for (i=n;i>=1;i--)
	{
		if (i!=n) SegmentTree::update(1,i+1,n,a[i+1].y-a[i].y);
		ans=max(ans,SegmentTree::tree[1].maxn*2);
		if (a[i].x>=Mid)
		{
			posleft=i+1;
			while (s1tot && s1[s1tot].x>a[i].x)
			{
				int delta=a[i].x-s1[s1tot].x;
				posright=s1[s1tot].y;s1tot--;
				SegmentTree::update(1,posleft,posright,delta);
				posleft=posright+1;
			}
			if (posleft!=i+1) s1[++s1tot]=mp(a[i].x,posleft-1);
		}
		else
		{
			posleft=i+1;
			while (s2tot && s2[s2tot].x<a[i].x)
			{
				int delta=s2[s2tot].x-a[i].x;
				posright=s2[s2tot].y;s2tot--;
				SegmentTree::update(1,posleft,posright,delta);
				posleft=posright+1;
			}
			if (posleft!=i+1) s2[++s2tot]=mp(a[i].x,posleft-1);
		}
		s1[++s1tot]=mp(w,i);s2[++s2tot]=mp(0,i);
		SegmentTree::update(1,i,i,w);
	}
}

int main ()
{
	int i;
	w=getint();h=getint();n=getint();
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint();
	a[++n]=node{0,0,0};a[++n]=node{w,h,0};
	solve();
	for (i=1;i<=n;i++) swap(a[i].x,a[i].y);
	swap(w,h);
	solve();
	printf("%d\n",ans);
	return 0;
}
