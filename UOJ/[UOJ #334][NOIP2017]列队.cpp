#include <bits/stdc++.h>
using namespace std;

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

const int INF=2e9;
const LL LFIN=2e16;
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

const int MAXN=3e5;

int n,m,q;
bool f; 

int root1[MAXN+48],root2[MAXN+48],Root;
int cnt[MAXN+48];
namespace Treap
{
	struct node
	{
		int priority,left,right;LL val;
		int sz;
	}tree[MAXN*5];int tot=0;
	inline int Create(int left,int right,LL val,int priority)
	{
		++tot;
		tree[tot].val=val;tree[tot].priority=priority;tree[tot].left=left;tree[tot].right=right;
		tree[tot].sz=1;
		return tot;
	}
	inline void pushup(int cur) {tree[cur].sz=tree[tree[cur].left].sz+tree[tree[cur].right].sz+1;}
	inline Pair split1(int root,LL val)
	{
		if (!root) return mp(0,0);
		if (tree[root].val>val)
		{
			Pair splitted=split1(tree[root].left,val);
			tree[root].left=splitted.y;pushup(root);
			return mp(splitted.x,root);
		}
		else
		{
			Pair splitted=split1(tree[root].right,val);
			tree[root].right=splitted.x;pushup(root);
			return mp(root,splitted.y);
		}
	}
	inline Pair split2(int root,int k)
	{
		if (!root) return mp(0,0);
		int leftsz=tree[tree[root].left].sz+1;
		if (k>=leftsz)
		{
			Pair splitted=split2(tree[root].right,k-leftsz);
			tree[root].right=splitted.x;pushup(root);
			return mp(root,splitted.y);
		}
		else
		{
			Pair splitted=split2(tree[root].left,k);
			tree[root].left=splitted.y;pushup(root);
			return mp(splitted.x,root);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1+root2;
		if (tree[root1].priority<tree[root2].priority)
		{
			tree[root1].right=merge(tree[root1].right,root2);
			pushup(root1);return root1;
		}
		else
		{
			tree[root2].left=merge(root1,tree[root2].left);
			pushup(root2);return root2;
		}
	}
	inline void treap_insert(int &root,LL val)
	{
		Pair splitted=split1(root,val);
		root=merge(merge(splitted.x,Create(0,0,val,rand())),splitted.y);
	}
	inline void treap_insert(int &root,int pos,LL val)
	{
		Pair splitted=split2(root,pos-1);
		root=merge(merge(splitted.x,Create(0,0,val,rand())),splitted.y);
	}
	inline void treap_delete(int &root,int pos)
	{
		Pair splitted=split2(root,pos-1);Pair splitted2=split2(splitted.y,1);
		root=merge(splitted.x,splitted2.y);
	}
	inline LL query(int &root,int pos)
	{
		Pair splitted=split2(root,pos-1);Pair splitted2=split2(splitted.y,1);
		LL res=tree[splitted2.x].val;
		root=merge(merge(splitted.x,splitted2.x),splitted2.y);
		return res;
	}
	inline int find(int root,int k,int ss)
	{
		if (!root) return k+ss; 
		int leftsz=tree[root].val-tree[tree[root].left].sz-1-ss;
		if (leftsz>=k) return find(tree[root].left,k,ss); else return find(tree[root].right,k,ss+tree[tree[root].left].sz+1);
	}
}

int main ()
{
	n=getint();m=getint();q=getint();
	memset(root1,0,sizeof(root1));memset(root2,0,sizeof(root2));Root=0;int i,x,y;
	for (i=1;i<=n;i++) Treap::treap_insert(Root,1ll*i*m);
	int cc=0;
	while (q--)
	{
		cc++;
		if (cc==11) f=true; else f=false;
		x=getint();y=getint();
		if (y==m)
		{
			LL res=Treap::query(Root,x);Treap::treap_delete(Root,x);
			printf("%lld\n",res);
			Treap::treap_insert(Root,n,res);
			continue;
		}
		if (y<=m-1-cnt[x])
		{
			LL res=Treap::find(root1[x],y,0);
			printf("%lld\n",1ll*(x-1)*m+res);
			Treap::treap_insert(root1[x],res);
			LL tmp=Treap::query(Root,x);Treap::treap_delete(Root,x);
			Treap::treap_insert(root2[x],++cnt[x],tmp);
			Treap::treap_insert(Root,n,1ll*(x-1)*m+res);
		}
		else
		{
			int yy=y-(m-1-cnt[x]);
			LL res=Treap::query(root2[x],yy);Treap::treap_delete(root2[x],yy);
			printf("%lld\n",res);
			LL tmp=Treap::query(Root,x);Treap::treap_delete(Root,x);
			Treap::treap_insert(root2[x],cnt[x],tmp);
			Treap::treap_insert(Root,n,res);
		}
	}
	return 0;
}
