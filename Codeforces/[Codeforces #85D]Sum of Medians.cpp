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

int root[10];Pair tmp[10];
namespace Treap
{
	struct node
	{
		int left,right,val,priority;
		LL sum;int sz;
	}tree[MAXN*2];int tot=0;
	inline void pushup(int cur)
	{
		tree[cur].sum=tree[tree[cur].left].sum+tree[tree[cur].right].sum+tree[cur].val;
		tree[cur].sz=tree[tree[cur].left].sz+tree[tree[cur].right].sz+1;
	}
	inline int Create(int left,int right,int val,int priority)
	{
		++tot;
		tree[tot].left=left;tree[tot].right=right;tree[tot].val=val;tree[tot].priority=priority;
		pushup(tot);return tot;
	}
	inline Pair split(int root,int val)
	{
		if (!root) return mp(0,0);
		if (tree[root].val<val)
		{
			Pair splitted=split(tree[root].right,val);
			tree[root].right=splitted.x;pushup(root);
			return mp(root,splitted.y);
		}
		else
		{
			Pair splitted=split(tree[root].left,val);
			tree[root].left=splitted.y;pushup(root);
			return mp(splitted.x,root);
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
		if (tree[root1].priority<=tree[root2].priority)
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
	inline bool find(int root,int x)
	{
		if (!root) return false;
		if (tree[root].val==x) return true;
		if (x<tree[root].val) return find(tree[root].left,x); else return find(tree[root].right,x);
	}
}

int main ()
{
	int x,i,pos,q=getint();char op[5];
	while (q--)
	{
		scanf("%s",op+1);
		if (op[1]=='a')
		{
			x=getint();
			for (i=0;i<=4;i++) tmp[i]=Treap::split(root[i],x);
			pos=1;for (i=0;i<=4;i++) pos+=Treap::tree[tmp[i].x].sz;pos%=5;
			tmp[pos].x=Treap::merge(tmp[pos].x,Treap::Create(0,0,x,rand()));
			for (i=0;i<=4;i++) root[(i+1)%5]=Treap::merge(tmp[(i+1)%5].x,tmp[i].y);	
		}
		if (op[1]=='d')
		{
			x=getint();
			for (i=0;i<=4;i++) if (Treap::find(root[i],x)) {pos=i;break;}
			for (i=0;i<=4;i++) tmp[i]=Treap::split(root[i],x);
			tmp[pos].y=Treap::split2(tmp[pos].y,1).y;
			for (i=0;i<=4;i++) root[i]=Treap::merge(tmp[i].x,tmp[(i+1)%5].y);
		}
		if (op[1]=='s') printf("%lld\n",Treap::tree[root[3]].sum);
	}
	return 0;
}
