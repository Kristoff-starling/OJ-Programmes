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
int c[100048],leader[100048];
vector<int> v[100048];
int L[100048],R[100048];int ind=0;
int seq[100048];

inline void dfs(int cur,int father)
{
	L[cur]=++ind;int i,y;seq[ind]=cur;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father) dfs(y,cur);
	}
	R[cur]=ind;
}

int root[100048],tot=0;
namespace SegmentTree
{
	struct node
	{
		int lson,rson;
		LL sum;int num;
	}tree[6000048];
	inline void pushup(int cur)
	{
		tree[cur].num=tree[tree[cur].lson].num+tree[tree[cur].rson].num;
		tree[cur].sum=tree[tree[cur].lson].sum+tree[tree[cur].rson].sum;
	}
	inline void Insert(int last,int cur,int pos,int l,int r)
	{
		tree[cur]=tree[last];
		if (l==r)
		{
			tree[cur].sum+=pos;
			tree[cur].num++;
			return;
		}
		int mid=(l+r)>>1;
		if (pos<=mid)
		{
			tree[cur].lson=++tot;
			Insert(tree[last].lson,tree[cur].lson,pos,l,mid);
		}
		else
		{
			tree[cur].rson=++tot;
			Insert(tree[last].rson,tree[cur].rson,pos,mid+1,r);
		}
		pushup(cur);
	}
	inline int query(int last,int cur,int k,int l,int r)
	{
		LL lsum=tree[tree[cur].lson].sum-tree[tree[last].lson].sum;int lnum=tree[tree[cur].lson].num-tree[tree[last].lson].num;
		if (l==r) return min(k/l,tree[cur].num-tree[last].num);
		int mid=(l+r)>>1;
		if (lsum>k) return query(tree[last].lson,tree[cur].lson,k,l,mid); else return lnum+query(tree[last].rson,tree[cur].rson,k-lsum,mid+1,r);
	}
}

int main ()
{
	int i,x;n=getint();m=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();c[i]=getint();leader[i]=getint();
		if (x) v[x].pb(i),v[i].pb(x);
	}
	dfs(1,0);
	root[0]=++tot;
	for (i=1;i<=n;i++)
	{
		root[i]=++tot;
		SegmentTree::Insert(root[i-1],root[i],c[seq[i]],1,lim);
	}
	LL ans=0;
	for (i=1;i<=n;i++)
	{
		int sz=SegmentTree::query(root[L[i]-1],root[R[i]],m,1,lim);
		ans=max(ans,(long long)leader[i]*sz);
	}
	printf("%lld\n",ans);
	return 0;
}
