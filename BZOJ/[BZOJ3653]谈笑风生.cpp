#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <iomanip>
#include <bitset>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <list>
#define LL long long
#define LB long double
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int MOD=998244353;
const int magic=348;
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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=3e5;

int n,q;
vector<int> v[MAXN+48];
int seq[MAXN+48],depth[MAXN+48],L[MAXN+48],R[MAXN+48],sz[MAXN+48];

int ind=0;
inline void dfs(int cur,int father)
{
	int i,y;
	seq[++ind]=cur;L[cur]=ind;sz[cur]=1;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father) depth[y]=depth[cur]+1,dfs(y,cur),sz[cur]+=sz[y];
	}
	R[cur]=ind;
}

int root[MAXN+48],tot=0;
namespace SegmentTree
{
	struct node
	{
		int lson,rson;
		LL sum;
	}tree[MAXN*20];
	inline void build(int left,int right)
	{
		root[0]=++tot;tree[tot].lson=tree[tot].rson=0;
		tree[tot].sum=0;
	}
	inline void pushup(int cur)
	{
		tree[cur].sum=tree[tree[cur].lson].sum+tree[tree[cur].rson].sum;
	}
	inline void Insert(int last,int cur,int pos,int val,int l,int r)
	{
		tree[cur]=tree[last];
		if (l==r) {tree[cur].sum+=val;return;}
		int mid=(l+r)>>1;
		if (pos<=mid)
		{
			tree[cur].lson=++tot;
			Insert(tree[last].lson,tree[cur].lson,pos,val,l,mid);
		}
		else
		{
			tree[cur].rson=++tot;
			Insert(tree[last].rson,tree[cur].rson,pos,val,mid+1,r);
		}
		pushup(cur);
	}
	inline LL query(int cur,int left,int right,int l,int r)
	{
		if (left<=l && r<=right) return tree[cur].sum;
		LL res=0;int mid=(l+r)>>1;
		if (left<=mid && tree[cur].lson) res+=query(tree[cur].lson,left,right,l,mid);
		if (mid+1<=right && tree[cur].rson) res+=query(tree[cur].rson,left,right,mid+1,r);
		return res;
	}
}

int main ()
{
	int i,x,y;n=getint();q=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	depth[1]=1;dfs(1,-1);
	SegmentTree::build(1,n);
	for (i=1;i<=n;i++) root[i]=++tot,SegmentTree::Insert(root[i-1],root[i],depth[seq[i]],sz[seq[i]]-1,1,n);
	int p,k;LL ans=0;
	while (q--)
	{
		p=getint();k=getint();
		ans=1ll*(min(k,depth[p]-1))*(sz[p]-1);
		ans+=SegmentTree::query(root[R[p]],depth[p]+1,depth[p]+k,1,n)-SegmentTree::query(root[L[p]],depth[p]+1,depth[p]+k,1,n);
		printf("%lld\n",ans);
	}
	return 0;
}
