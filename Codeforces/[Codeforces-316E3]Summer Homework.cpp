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

const int MOD=1e9;
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

int n,q;
inline int mod(LL x)
{
	while (x>=MOD) x-=MOD;
	return x;
}

struct Matrix
{
	int b[3][3];
	inline void init()
	{
		b[1][1]=0;
		b[1][2]=b[2][1]=b[2][2]=1;
	}
	inline void clear() {for (register int i=1;i<=2;i++) for (register int j=1;j<=2;j++) b[i][j]=0;}
	inline Matrix operator + (const Matrix ma)
	{
		Matrix res;res.clear();int i,j;
		for (i=1;i<=2;i++)
			for (j=1;j<=2;j++)
				res.b[i][j]=mod(res.b[i][j]+mod(b[i][j]+ma.b[i][j]));
		return res;
	}
	inline Matrix operator * (const Matrix ma)
	{
		Matrix res;res.clear();int i,j,k;
		for (i=1;i<=2;i++)
			for (j=1;j<=2;j++)
				for (k=1;k<=2;k++)
					res.b[i][j]=mod(res.b[i][j]+((long long)b[i][k]*ma.b[k][j])%MOD);
		return res;
	}
	inline Matrix operator ^ (const Matrix ma)
	{
		Matrix res;res.b[1][1]=res.b[1][2]=0;int j,k;
		for (j=1;j<=2;j++)
			for (k=1;k<=2;k++)
				res.b[1][j]=mod(res.b[1][j]+((long long)b[1][k]*ma.b[k][j])%MOD);
		return res;
	}
	inline Matrix operator & (const Matrix ma)
	{
		Matrix res;res.b[1][1]=res.b[1][2]=0;int j;
		for (j=1;j<=2;j++) res.b[1][j]=mod(res.b[1][j]+mod(b[1][j]+ma.b[1][j]));
		return res;
	}
}trans,ma[200048];
LL fib[200048],sum1[200048],sum2[200048];
int a[200048];

namespace SegmentTree
{
	struct node
	{
		int left,right,len,lazy;
		Matrix ma;
	}tree[1000048];
	inline Matrix pushup(Matrix x,Matrix y,int starter)
	{
		if (starter) y=y^ma[starter];x=x&y;
		return x;
	}
	inline void pushdown(int cur)
	{
		tree[cur<<1].lazy=mod(tree[cur<<1].lazy+tree[cur].lazy);
		tree[cur<<1|1].lazy=mod(tree[cur<<1|1].lazy+tree[cur].lazy);
		tree[cur].lazy=0;
	}
	inline Matrix calc_lazy(Matrix x,int ind)
	{
		if (tree[ind].lazy==0) return x;
		x.b[1][1]=mod(x.b[1][1]+((long long)tree[ind].lazy*sum1[tree[ind].len])%MOD);
		x.b[1][2]=mod(x.b[1][2]+((long long)tree[ind].lazy*sum2[tree[ind].len])%MOD);
		return x;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;tree[cur].lazy=0ll;
		tree[cur].len=tree[cur].right-tree[cur].left+1;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);
			build(cur<<1|1,mid+1,right);
			tree[cur].ma=pushup(tree[cur<<1].ma,tree[cur<<1|1].ma,tree[cur<<1].len);
		}
		else
		{
			tree[cur].ma.b[1][1]=tree[cur].ma.b[1][2]=a[left];
			tree[cur].ma.b[2][1]=tree[cur].ma.b[2][2]=0;
		}
	}
	inline void update(int cur,int pos,int newval)
	{
		if (tree[cur].left==tree[cur].right)
		{
			tree[cur].ma.b[1][1]=tree[cur].ma.b[1][2]=newval;
			tree[cur].lazy=0;
			return;
		}
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (pos<=mid) update(cur<<1,pos,newval); else update(cur<<1|1,pos,newval);
		tree[cur].ma=pushup(calc_lazy(tree[cur<<1].ma,cur<<1),calc_lazy(tree[cur<<1|1].ma,cur<<1|1),tree[cur<<1].len);
	}
	inline Matrix query(int cur,int left,int right,int starter)
	{
		Matrix res;res.clear();
		if (left<=tree[cur].left && tree[cur].right<=right) return calc_lazy(tree[cur].ma,cur)*ma[starter];
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left>mid) {res=query(cur<<1|1,left,right,starter);}
		else if (right<=mid) {res=query(cur<<1,left,right,starter);}
		else {Matrix res1=query(cur<<1,left,tree[cur<<1].right,starter),res2=query(cur<<1|1,tree[cur<<1|1].left,right,starter+mid-left+1);res=res1+res2;}
		tree[cur].ma=pushup(calc_lazy(tree[cur<<1].ma,cur<<1),calc_lazy(tree[cur<<1|1].ma,cur<<1|1),tree[cur<<1].len);
		return res;
	}
	inline void update(int cur,int left,int right,int delta)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) {tree[cur].lazy=mod(tree[cur].lazy+delta);return;}
		pushdown(cur);
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update(cur<<1,left,right,delta);
		if (mid+1<=right) update(cur<<1|1,left,right,delta);
		tree[cur].ma=pushup(calc_lazy(tree[cur<<1].ma,cur<<1),calc_lazy(tree[cur<<1|1].ma,cur<<1|1),tree[cur<<1].len);
	}
}

int main ()
{
	n=getint();q=getint();
	int i,type,pos,newval,l,r,delta;
	trans.init();ma[0].b[1][1]=ma[0].b[2][2]=1;ma[0].b[1][2]=ma[0].b[2][1]=0;
	for (i=1;i<=n+10;i++) ma[i]=ma[i-1]*trans;
	for (i=1;i<=n;i++) a[i]=getint();
	fib[1]=fib[2]=1;for (i=3;i<=n+10;i++) fib[i]=mod(fib[i-1]+fib[i-2]);
	sum1[1]=sum2[1]=1;for (i=2;i<=n+9;i++) sum1[i]=mod(sum1[i-1]+fib[i]),sum2[i]=mod(sum2[i-1]+fib[i+1]);
	SegmentTree::build(1,1,n);
	while (q--)
	{
		type=getint();
		if (type==1)
		{
			pos=getint();newval=getint();
			SegmentTree::update(1,pos,newval);
		}
		if (type==2)
		{
			l=getint();r=getint();
			printf("%d\n",SegmentTree::query(1,l,r,0).b[1][1]);
		}
		if (type==3)
		{
			l=getint();r=getint();delta=getint();
			SegmentTree::update(1,l,r,delta);
		}
	}
	return 0;
}
/*
5 5
1 3 1 2 4
2 1 4
2 1 5
2 2 4
1 3 10
2 1 5
*/
