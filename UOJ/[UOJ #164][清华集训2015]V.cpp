#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <list>
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

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
LL val[MAXN+48];

namespace SegmentTree
{
	struct node
	{
		int left,right;
		LL A,B;
		LL hA,hB;
	}tree[MAXN*4];
	inline void update(int cur)
	{
		tree[cur].hA=max(tree[cur].hA,tree[cur].A+tree[cur>>1].hA);
		tree[cur].hB=max(max(tree[cur].hB,tree[cur>>1].hB),tree[cur].B+tree[cur>>1].hA);
		tree[cur].A=max(tree[cur].A+tree[cur>>1].A,-LINF);
		tree[cur].B=max(tree[cur].B+tree[cur>>1].A,tree[cur>>1].B);
	}
	inline void pushdown(int cur)
	{
		update(cur<<1);update(cur<<1|1);
		tree[cur].A=tree[cur].hA=0;tree[cur].B=tree[cur].hB=0;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].A=tree[cur].hA=0;tree[cur].B=tree[cur].hB=0;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);
			build(cur<<1|1,mid+1,right);
		}
	}
	inline void update(int cur,int left,int right,LL addA,LL addB)
	{
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			tree[cur].hA=max(tree[cur].hA,tree[cur].A+addA);
			tree[cur].hB=max(max(tree[cur].hB,addB),tree[cur].B+addA);
			tree[cur].A=max(tree[cur].A+addA,-LINF);
			tree[cur].B=max(addB,tree[cur].B+addA);
			return;
		}
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update(cur<<1,left,right,addA,addB);
		if (mid+1<=right) update(cur<<1|1,left,right,addA,addB);
	}
	inline LL query_cur(int cur,int pos)
	{
		if (tree[cur].left==tree[cur].right) return max(val[tree[cur].left]+tree[cur].A,tree[cur].B);
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) return query_cur(cur<<1,pos); else return query_cur(cur<<1|1,pos);
	}
	inline LL query_history(int cur,int pos)
	{
		if (tree[cur].left==tree[cur].right) return max(val[tree[cur].left]+tree[cur].hA,tree[cur].hB);
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) return query_history(cur<<1,pos); else return query_history(cur<<1|1,pos);
	}
}

int main ()
{
	int i,op,l,r,x;
	n=getint();q=getint();
	for (i=1;i<=n;i++) val[i]=getint();
	SegmentTree::build(1,1,n);
	while (q--)
	{
		op=getint();
		if (op<4) l=getint(),r=getint();
		x=getint();
		if (op==1) SegmentTree::update(1,l,r,x,0);
		if (op==2) SegmentTree::update(1,l,r,-x,0);
		if (op==3) SegmentTree::update(1,l,r,-LINF,x);
		if (op==4) printf("%lld\n",SegmentTree::query_cur(1,x));
		if (op==5) printf("%lld\n",SegmentTree::query_history(1,x));
	}
	return 0;
}
