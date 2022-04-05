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
#define DEBUG(...) printf(__VA_ARGS__)
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
int a[100048];

struct node
{
	int left,right;
	LL sum,maxn;
}tree[600048];

inline void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
		tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
	}
	else
		tree[cur].sum=tree[cur].maxn=a[left];
}

bool cut(int cur,int x)
{
	return tree[cur].maxn<x;
}

bool check(int cur)
{
	return tree[cur].left==tree[cur].right;
}

inline void pushup(int cur)
{
	tree[cur].sum=(tree[cur<<1].sum+tree[cur<<1|1].sum);
	tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
}

inline void update(int cur,int left,int right,int x)
{
	if (tree[cur].right<left || tree[cur].left>right || cut(cur,x)) return;
	if (left<=tree[cur].left && tree[cur].right<=right && check(cur))
	{
		tree[cur].sum%=x;
		tree[cur].maxn%=x;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	update(cur<<1,left,right,x);update(cur<<1|1,left,right,x);
	pushup(cur);
}

inline void update(int cur,int pos,int newval)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].sum=tree[cur].maxn=newval;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid) update(cur<<1,pos,newval); else update(cur<<1|1,pos,newval);
	pushup(cur);
}

inline LL query(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	LL res=0;
	if (left<=mid) res+=query(cur<<1,left,right);
	if (mid+1<=right) res+=query(cur<<1|1,left,right);
	return res;
}

int main ()
{
	int type,l,r,x;
	n=getint();q=getint();
	for (int i=1;i<=n;i++) a[i]=getint();
	build(1,1,n);
	while (q--)
	{
		type=getint();
		if (type==1)
		{
			l=getint();r=getint();
			printf("%lld\n",query(1,l,r));
		}
		if (type==2)
		{
			l=getint();r=getint();x=getint();
			update(1,l,r,x);
		}
		if (type==3)
		{
			l=getint();x=getint();
			update(1,l,x);
		}
	}
	return 0;
}
