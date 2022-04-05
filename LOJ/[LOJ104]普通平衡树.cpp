#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))
#define rep(i,a,b) for (register int i=a;i<=b;i++)
#define Rep(i,b,a) for (register int i=b;i>=a;i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

namespace Treap
{
	struct Treap
	{
		int lson,rson,val,priority,sz;
	}tree[MAXN+48];int tot=0,Root;
	inline void init() {tree[0].lson=tree[0].rson=tree[0].sz=tot=Root=0;}
	inline void pushup(int cur) {tree[cur].sz=tree[tree[cur].lson].sz+tree[tree[cur].rson].sz+1;}
	inline int Create(int left,int right,int val,int priority) {++tot;tree[tot].lson=left;tree[tot].rson=right;tree[tot].val=val;tree[tot].priority=priority;pushup(tot);return tot;}
	inline Pair split(int cur,int k)
	{
		if (!cur) return mp(0,0);
		int leftsz=tree[tree[cur].lson].sz+1;
		if (k>=leftsz)
		{
			Pair splitted=split(tree[cur].rson,k-leftsz);
			tree[cur].rson=splitted.x;pushup(cur);return mp(cur,splitted.y);
		}
		else
		{
			Pair splitted=split(tree[cur].lson,k);
			tree[cur].lson=splitted.y;pushup(cur);return mp(splitted.x,cur);
		}
	}
	//key to the right
	inline Pair split1(int cur,int key)
	{
		if (!cur) return mp(0,0);
		if (key<=tree[cur].val)
		{
			Pair splitted=split1(tree[cur].lson,key);
			tree[cur].lson=splitted.y;pushup(cur);return mp(splitted.x,cur);
		}
		else
		{
			Pair splitted=split1(tree[cur].rson,key);
			tree[cur].rson=splitted.x;pushup(cur);return mp(cur,splitted.y);
		}
	}
	//key to the left
	inline Pair split2(int cur,int key)
	{
		if (!cur) return mp(0,0);
		if (key>=tree[cur].val)
		{
			Pair splitted=split2(tree[cur].rson,key);
			tree[cur].rson=splitted.x;pushup(cur);return mp(cur,splitted.y);
		}
		else
		{
			Pair splitted=split2(tree[cur].lson,key);
			tree[cur].lson=splitted.y;pushup(cur);return mp(splitted.x,cur);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1^root2;
		if (tree[root1].priority<=tree[root2].priority)
		{
			tree[root1].rson=merge(tree[root1].rson,root2);
			pushup(root1);return root1;
		}
		else
		{
			tree[root2].lson=merge(root1,tree[root2].lson);
			pushup(root2);return root2;
		}
	}
	inline void insert(int x)
	{
		Pair splitted=split1(Root,x);
		Root=merge(merge(splitted.x,Create(0,0,x,rand())),splitted.y);
	}
	inline void del(int x)
	{
		Pair splitted=split1(Root,x),splitted2=split(splitted.y,1);
		Root=merge(splitted.x,splitted2.y);
	}
	inline int xrank(int x)
	{
		Pair splitted=split1(Root,x);int res=tree[splitted.x].sz+1;
		Root=merge(splitted.x,splitted.y);return res;
	}
	inline int rankx(int x)
	{
		Pair splitted=split(Root,x-1);Pair splitted2=split(splitted.y,1);
		int res=tree[splitted2.x].val;
		Root=merge(merge(splitted.x,splitted2.x),splitted2.y);return res;
	}
	inline int getprev(int x)
	{
		Pair splitted=split1(Root,x);Pair splitted2=split(splitted.x,tree[splitted.x].sz-1);
		int res=tree[splitted2.y].val;
		Root=merge(merge(splitted2.x,splitted2.y),splitted.y);return res;
	}
	inline int getnxt(int x)
	{
		Pair splitted=split2(Root,x);Pair splitted2=split(splitted.y,1);
		int res=tree[splitted2.x].val;
		Root=merge(merge(splitted.x,splitted2.x),splitted2.y);
		return res;
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	double T=clock();
	cerr<<"Running..."<<endl;
#endif
	// srand(time(NULL));
	int n,op,x;Get(n);Treap::init();
	int cnt=0;
	while (n--)
	{
		Get(op,x);
		if (op==1) Treap::insert(x);
		if (op==2) Treap::del(x);
		if (op==3) printf("%d\n",Treap::xrank(x));
		if (op==4) printf("%d\n",Treap::rankx(x));
		if (op==5) printf("%d\n",Treap::getprev(x));
		if (op==6) printf("%d\n",Treap::getnxt(x));
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
