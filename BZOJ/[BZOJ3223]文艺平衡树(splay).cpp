#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

const int MAXN=1e5;

namespace splay
{
	struct node
	{
		int ch[2],father;int val;
		int flip,sz;
	}tree[MAXN*2];int root,tot;
	inline int Create(int lson,int rson,int val,int father)
	{
		++tot;tree[tot].ch[0]=lson;tree[tot].ch[1]=rson;
		tree[tot].val=val;tree[tot].father=father;
		tree[tot].sz=1;tree[tot].flip=0;
		return tot;
	}
	inline void pushdown(int cur)
	{
		if (tree[cur].flip)
		{
			tree[tree[cur].ch[0]].flip^=1;
			tree[tree[cur].ch[1]].flip^=1;
			swap(tree[cur].ch[0],tree[cur].ch[1]);
			tree[cur].flip=0;
		}
	}
	inline void pushup(int cur)
	{
		tree[cur].sz=tree[tree[cur].ch[0]].sz+tree[tree[cur].ch[1]].sz+1;
	}
	inline void rotate(int x)
	{
		int y=tree[x].father,z=tree[y].father;
		pushdown(y);pushdown(x);
		int k=(tree[y].ch[1]==x);
		tree[z].ch[tree[z].ch[1]==y]=x;
		tree[y].ch[k]=tree[x].ch[k^1];tree[x].ch[k^1]=y;
		tree[tree[y].ch[k]].father=y;tree[y].father=x;tree[x].father=z;
		pushup(y);pushup(x);
	}
	inline void splay(int x,int target)
	{
		int y,z;
		while (tree[x].father!=target)
		{
			y=tree[x].father;z=tree[y].father;
			if (z!=target)
				if ((tree[y].ch[1]==x)^(tree[z].ch[1]==y)) rotate(x); else rotate(y);
			rotate(x);
		}
		if (!target) root=x;
	}
	inline int find(int x)
	{
		int cur=root;
		for (;;)
		{
			pushdown(cur);
			int lsz=tree[tree[cur].ch[0]].sz+1;
			if (lsz==x) return cur;
			if (lsz>x) cur=tree[cur].ch[0]; else x-=lsz,cur=tree[cur].ch[1];
		}
	}
	inline void build()
	{
		root=Create(0,0,0,0);
		tree[root].ch[1]=Create(0,0,0,root);
		splay(tree[root].ch[1],0);
	}
	inline void insert(int pos,int val)
	{
		int x=find(pos);splay(x,0);
		int y=find(pos+1);splay(y,root);
		tree[y].ch[0]=Create(0,0,val,y);
		splay(tree[y].ch[0],0);
	}
	inline void splay_rotate(int l,int r)
	{
		int x=find(l);splay(x,0);
		int y=find(r+2);splay(y,root);
		tree[tree[y].ch[0]].flip^=1;
	}
	inline void print(int cur)
	{
		if (!cur) return;
		pushdown(cur);
		print(tree[cur].ch[0]);
		if (tree[cur].val) printf("%d ",tree[cur].val);
		print(tree[cur].ch[1]);
	}
}

int n,m;

int main ()
{
	int i,x,y;n=getint();m=getint();
	splay::build();
	for (i=1;i<=n;i++)
		splay::insert(i,i);
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();
		splay::splay_rotate(x,y);
	}
	splay::print(splay::root);
	return 0;
}
