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

int n,q;
int a[1000048];

struct node
{
	int left,right;
	int fmax,cnt,smax;
	LL sum;
}tree[4000048];

inline void pushup(int cur)
{
	tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
	if (tree[cur<<1].fmax>=tree[cur<<1|1].fmax)
	{
		tree[cur].fmax=tree[cur<<1].fmax;
		tree[cur].cnt=tree[cur<<1].cnt+(tree[cur<<1].fmax==tree[cur<<1|1].fmax?tree[cur<<1|1].cnt:0);
		if (tree[cur<<1].fmax==tree[cur<<1|1].fmax)
			tree[cur].smax=max(tree[cur<<1].smax,tree[cur<<1|1].smax);
		else
			tree[cur].smax=max(tree[cur<<1].smax,tree[cur<<1|1].fmax);
	}
	else
	{
		tree[cur].fmax=tree[cur<<1|1].fmax;
		tree[cur].cnt=tree[cur<<1|1].cnt;
		tree[cur].smax=max(tree[cur<<1|1].smax,tree[cur<<1].fmax);
	}
}

inline void pushdown(int cur)
{
	if (tree[cur].fmax<tree[cur<<1].fmax)
	{
		tree[cur<<1].sum-=((long long)(tree[cur<<1].fmax-tree[cur].fmax)*tree[cur<<1].cnt);
		tree[cur<<1].fmax=tree[cur].fmax;
	}
	if (tree[cur].fmax<tree[cur<<1|1].fmax)
	{
		tree[cur<<1|1].sum-=((long long)(tree[cur<<1|1].fmax-tree[cur].fmax)*tree[cur<<1|1].cnt);
		tree[cur<<1|1].fmax=tree[cur].fmax;
	}
}

inline void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		pushup(cur);
	}
	else
	{
		tree[cur].fmax=tree[cur].sum=a[left];
		tree[cur].smax=-1;tree[cur].cnt=1;
	}
}

bool cut(int cur,int cmp)
{
	return tree[cur].fmax<=cmp;
}

bool check(int cur,int cmp)
{
	return (tree[cur].smax<cmp && cmp<tree[cur].fmax);
}

inline void update(int cur,int left,int right,int cmp)
{
	if (tree[cur].right<left || tree[cur].left>right || cut(cur,cmp)) return;
	if (left<=tree[cur].left && tree[cur].right<=right && check(cur,cmp))
	{
		tree[cur].sum-=((long long)(tree[cur].fmax-cmp)*tree[cur].cnt);
		tree[cur].fmax=cmp;
		return;
	}
	pushdown(cur);
	update(cur<<1,left,right,cmp);update(cur<<1|1,left,right,cmp);
	pushup(cur);
}

inline int query_max(int cur,int left,int right)
{
	if (tree[cur].right<left || tree[cur].left>right) return -1;
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].fmax;
	int res=-1;
	pushdown(cur);
	res=max(res,query_max(cur<<1,left,right));res=max(res,query_max(cur<<1|1,left,right));
	pushup(cur);
	return res;
}

inline LL query_sum(int cur,int left,int right)
{
	if (tree[cur].right<left || tree[cur].left>right) return 0ll;
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
	LL res=0;
	pushdown(cur);
	res=query_sum(cur<<1,left,right)+query_sum(cur<<1|1,left,right);
	pushup(cur);
	return res;
}

int main ()
{
	int ca,i,type,l,r,x;
	ca=getint();
	while (ca--)
	{
		n=getint();q=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		build(1,1,n);
		while (q--)
		{
			type=getint();l=getint();r=getint();if (!type) x=getint();
			if (type==0) update(1,l,r,x);
			if (type==1) printf("%d\n",query_max(1,l,r));
			if (type==2) printf("%lld\n",query_sum(1,l,r));
		}
	}
	return 0;
}
