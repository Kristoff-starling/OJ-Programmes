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
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void add(int &x,int y) {x=add(x+y);}
inline void sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e5;

int n;

int Root;
namespace Treap
{
	struct node
	{
		int left,right,val,priority,id;
		int sz,maxn;
	}tree[MAXN*2+48];int tot=0;
	inline void pushup(int cur)
	{
		tree[cur].sz=1;tree[cur].maxn=tree[cur].val;
		if (tree[cur].left) tree[cur].sz+=tree[tree[cur].left].sz,tree[cur].maxn=max(tree[cur].maxn,tree[tree[cur].left].maxn);
		if (tree[cur].right) tree[cur].sz+=tree[tree[cur].right].sz,tree[cur].maxn=max(tree[cur].maxn,tree[tree[cur].right].maxn);
	}
	inline int Create(int val,int priority,int id,int left,int right)
	{
		++tot;tree[tot].left=left;tree[tot].right=right;tree[tot].val=val;tree[tot].priority=priority;tree[tot].id=id;
		pushup(tot);return tot;
	}
	inline void print(int root)
	{
		if (!root) return;
		print(tree[root].left);
		io.Print(tree[root].id,' ');
		print(tree[root].right);
	}
	inline Pair split(int root,int k)
	{
		if (!root) return mp(0,0);
		int leftsz=tree[tree[root].left].sz+1;
		if (k>=leftsz)
		{
			Pair splitted=split(tree[root].right,k-leftsz);
			tree[root].right=splitted.x;pushup(root);
			return mp(root,splitted.y);
		}
		else
		{
			Pair splitted=split(tree[root].left,k);
			tree[root].left=splitted.y;pushup(root);
			return mp(splitted.x,root);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1^root2;
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
	inline int query(int root,int cmp)
	{
		if (!root) return 0;
		if (tree[tree[root].right].maxn>cmp) return tree[tree[root].left].sz+1+query(tree[root].right,cmp);
		if (tree[root].val>cmp) return tree[tree[root].left].sz+1;
		return query(tree[root].left,cmp);
	}
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	srand(time(NULL));
	io.Get(n);int vv,cc;
	for (register int i=1;i<=n;i++)
	{
		// cerr<<i<<endl;
		io.Get(vv);io.Get(cc);
		cc=min(cc,Treap::tree[Root].sz);
		Pair splitted=Treap::split(Root,Treap::tree[Root].sz-cc);
		int chc=Treap::query(splitted.y,vv);
		Pair splitted2=Treap::split(splitted.y,chc);
		// cerr<<i<<endl;
		Root=Treap::merge(splitted.x,Treap::merge(splitted2.x,Treap::merge(Treap::Create(vv,rand(),i,0,0),splitted2.y)));
	}
	Treap::print(Root);io.Writechar('\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}