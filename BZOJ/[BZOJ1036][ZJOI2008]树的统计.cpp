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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,q;
int depth[1000048],sz[1000048],fa[1000048];
int son[1000048];int top[1000048];
vector<int> v[1000048];
int weight[1000048],id[1000048],ind=0;
int Pos[1000048];
char type[10];

struct node
{
	int left,right;
	LL sum;int maxn;
}tree[300048];

void dfs(int cur,int father)
{
	int i,max_sz=-1;
	sz[cur]=1;fa[cur]=father;son[cur]=0;
	for (i=0;i<v[cur].size();i++)
		if (v[cur][i]!=father)
		{
			depth[v[cur][i]]=depth[cur]+1;
			dfs(v[cur][i],cur);
			sz[cur]+=sz[v[cur][i]];
			if (sz[v[cur][i]]>max_sz)
			{
				son[cur]=v[cur][i];
				max_sz=sz[v[cur][i]];
			}
		}
}

void dfs2(int cur,int tp)
{
	int i;
	top[cur]=tp;id[cur]=++ind;Pos[ind]=cur;
	if (son[cur]) dfs2(son[cur],tp);
	for (i=0;i<v[cur].size();i++)
		if (v[cur][i]!=fa[cur] && v[cur][i]!=son[cur])
			dfs2(v[cur][i],v[cur][i]);
}

void build(int cur,int left,int right)
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
		tree[cur].maxn=tree[cur].sum=weight[Pos[left]];
}

void update(int cur,int pos,int nl)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].maxn=tree[cur].sum=nl;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid) update(cur<<1,pos,nl); else update(cur<<1|1,pos,nl);
	tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
	tree[cur].sum=tree[cur<<1].sum+tree[cur<<1|1].sum;
}

int query_max(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].maxn;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	int res=-INF;
	if (left<=mid) res=max(res,query_max(cur<<1,left,right));
	if (mid+1<=right) res=max(res,query_max(cur<<1|1,left,right));
	return res;
}

LL query_sum(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
	LL res=0;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) res+=query_sum(cur<<1,left,right);
	if (mid+1<=right) res+=query_sum(cur<<1|1,left,right);
	return res;
}

LL calc_sum(int u,int v)
{
	LL res=0;
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
		}
		res+=query_sum(1,id[tp1],id[u]);
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]<depth[v]) swap(u,v);
	res+=query_sum(1,id[v],id[u]);
	return res;
}

int calc_max(int u,int v)
{
	int res=-INF;
	int tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
		}
		res=max(res,query_max(1,id[tp1],id[u]));
		u=fa[tp1];tp1=top[u];
	}
	if (depth[u]<depth[v]) swap(u,v);
	res=max(res,query_max(1,id[v],id[u]));
	return res;
}

int main ()
{
	int i,x,y,len;
	n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	for (i=1;i<=n;i++) weight[i]=getint();
	depth[1]=1;dfs(1,0);dfs2(1,1);
	build(1,1,ind);
	q=getint();
	for (i=1;i<=q;i++)
	{
		scanf("%s",type+1);
		if (type[2]=='H')
		{
			x=getint();len=getint();
			update(1,id[x],len);
		}
		if (type[2]=='S')
		{
			x=getint();y=getint();
			printf("%lld\n",calc_sum(x,y));
		}
		if (type[2]=='M')
		{
			x=getint();y=getint();
			printf("%d\n",calc_max(x,y));
		}
	}
	return 0;
}
