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

int head[100048],to[200048],nxt[200048],f[200048],num[200048],tot=0;
inline void addedge(int s,int t,int l,int ind)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;num[tot]=ind;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=l;num[tot]=ind;
}

int n,Ind;
int weight[200048],wlink[200048],Pos[200048],id[200048];
int sz[200048],son[200048],depth[200048],fa[200048];
int top[200048];int dlink[200048];
char type[10];

void Clear()
{
	int i;
	for (i=1;i<=n;i++) head[i]=0;
	tot=1;Ind=0;
	for (i=1;i<=n;i++) weight[i]=wlink[i]=Pos[i]=id[i]=top[i]=dlink[i]=0;
}

void dfs(int cur,int father)
{
	int i,y,max_sz=-1;
	fa[cur]=father;sz[cur]=1;son[cur]=0;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			wlink[y]=num[i];dlink[num[i]]=y;
			dfs(y,cur);
			if (sz[y]>max_sz) max_sz=sz[y],son[cur]=y;
			sz[cur]+=sz[y];
		}
	}
}

void dfs2(int cur,int tp)
{
	int i,y;
	top[cur]=tp;id[cur]=++Ind;Pos[Ind]=wlink[cur];
	if (son[cur]) dfs2(son[cur],tp);
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=fa[cur] && y!=son[cur]) dfs2(y,y);
	}
}

struct node
{
	int left;int right;
	int maxn;
}tree[300048];

void build(int cur,int left,int right)
{
	tree[cur].left=left;tree[cur].right=right;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid);
		build(cur<<1|1,mid+1,right);
		tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
	}
	else
		tree[cur].maxn=weight[Pos[left]];
}

void update(int cur,int pos,int nl)
{
	if (tree[cur].left==tree[cur].right)
	{
		tree[cur].maxn=nl;
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (pos<=mid) update(cur<<1,pos,nl); else update(cur<<1|1,pos,nl);
	tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
}

int query(int cur,int left,int right)
{
	if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].maxn;
	int res=-INF;
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) res=max(res,query(cur<<1,left,right));
	if (mid+1<=right) res=max(res,query(cur<<1|1,left,right));
	return res;
}

int calc_max(int u,int v)
{
	if (u==v) return 0;
	int res=0,tp1=top[u],tp2=top[v];
	while (tp1!=tp2)
	{
		if (depth[tp1]<depth[tp2])
		{
			swap(u,v);
			swap(tp1,tp2);
		}
		res=max(res,query(1,id[tp1],id[u]));
		u=fa[tp1];tp1=top[u];
	}
	if (u==v) return res;
	if (depth[u]<depth[v]) swap(u,v);
	res=max(res,query(1,id[v],id[u]));
	return res;
}

int main ()
{
	int ca,i,x,y,l;
	ca=getint();
	while (ca--)
	{
		Clear();
		n=getint();
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();l=getint();
			addedge(x,y,l,i);weight[i]=l;
		}
		Pos[1]=0;depth[1]=1;dfs(1,0);
		dfs2(1,1);
		//for (i=1;i<=n;i++) cout<<weight[Pos[i]]<<endl;
		//for (i=1;i<=n;i++) cout<<id[i]<<' ';
		//cout<<endl;
		build(1,1,Ind);
		do
		{
			scanf("%s",type+1);
			if (type[1]=='C')
			{
				x=getint();y=getint();
				update(1,id[dlink[x]],y);
			}
			if (type[1]=='Q')
			{
				x=getint();y=getint();
				printf("%d\n",calc_max(x,y));
			}
		}
		while (type[1]!='D');
	}
	return 0;
}
