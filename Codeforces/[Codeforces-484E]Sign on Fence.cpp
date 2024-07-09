#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const double eps=1e-10;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	f=(ch=='-')?true:false;
	res=(ch=='-')?0:ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?-res:res;
}

struct Res
{
	int max_left,max_right,maxn;
};

struct node
{
	int left,right;
	int lson,rson;
	int max_left,max_right,maxn;
}tree[3000048];
int root[200048],tot=0;

void Pushup(int cur)
{
	tree[cur].max_left=tree[tree[cur].lson].max_left;
	if (tree[tree[cur].lson].max_left==tree[tree[cur].lson].right-tree[tree[cur].lson].left+1)
		tree[cur].max_left+=tree[tree[cur].rson].max_left;
	tree[cur].max_right=tree[tree[cur].rson].max_right;
	if (tree[tree[cur].rson].max_right==tree[tree[cur].rson].right-tree[tree[cur].rson].left+1)
		tree[cur].max_right+=tree[tree[cur].lson].max_right;
	tree[cur].maxn=max(tree[tree[cur].lson].maxn,tree[tree[cur].rson].maxn);
	tree[cur].maxn=max(tree[cur].maxn,tree[tree[cur].lson].max_right+tree[tree[cur].rson].max_left);
}

void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		tree[cur].lson=++tot;build(tree[cur].lson,left,mid);
		tree[cur].rson=++tot;build(tree[cur].rson,mid+1,right);
		Pushup(cur);
	}
	else
	{
		tree[cur].lson=tree[cur].rson=-1;
		tree[cur].max_left=tree[cur].max_right=tree[cur].maxn=1;
	}
}

void Insert(int cur,int last,int pos)
{
	tree[cur]=tree[last];
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].max_left=tree[cur].max_right=tree[cur].maxn=0;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid)
	{
		tree[cur].lson=++tot;
		Insert(tree[cur].lson,tree[last].lson,pos);
	}
	else
	{
		tree[cur].rson=++tot;
		Insert(tree[cur].rson,tree[last].rson,pos);
	}
	Pushup(cur);
}

int query_left(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].max_left;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) return query_left(tree[cur].lson,left,right); else return query_left(tree[cur].rson,left,right);
}

int query_right(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].max_right;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (mid+1<=right) return query_right(tree[cur].rson,left,right); else return query_right(tree[cur].lson,left,right);
}

Res getRes(int x,int y,int z)
{
	Res ret;
	ret.max_left=x;ret.max_right=y;ret.maxn=z;
	return ret;
}

Res query(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return getRes(tree[cur].max_left,tree[cur].max_right,tree[cur].maxn);
	int mid=(tree[cur].left+tree[cur].right)>>1;
	Res res1=getRes(0,0,0),res2=getRes(0,0,0);
	if (left<=mid) res1=query(tree[cur].lson,left,right);
	if (mid+1<=right) res2=query(tree[cur].rson,left,right);
	Res ret;
	ret.max_left=res1.max_left;
	if (res1.max_left==tree[tree[cur].lson].right-tree[tree[cur].lson].left+1)
		ret.max_left+=res2.max_left;
	ret.max_right=res2.max_right;
	if (res2.max_right==tree[tree[cur].rson].right-tree[tree[cur].rson].left+1)
		ret.max_right+=res1.max_right;
	ret.maxn=max(res1.maxn,res2.maxn);
	ret.maxn=max(ret.maxn,res1.max_right+res2.max_left);
	return ret;
}

int n,q;
struct info
{
	int h;
	int num;
	bool operator < (const info &x) const
	{
		return h<x.h;
	}
}a[100048];

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++) a[i].h=getint(),a[i].num=i;
	sort(a+1,a+n+1);
	root[a[1].num]=++tot;
	build(root[a[1].num],1,n);
	for (i=2;i<=n;i++)
	{
		root[a[i].num]=++tot;
		Insert(root[a[i].num],root[a[i-1].num],a[i-1].num);
	}
	q=getint();
	int l,r,L,R,W,mid,ans;
	while (q--)
	{
		L=getint();R=getint();W=getint();
		l=1;r=n;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (query(root[a[mid].num],L,R).maxn>=W)
			{
				ans=mid;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		printf("%d\n",a[ans].h);
	}
	return 0;
}
