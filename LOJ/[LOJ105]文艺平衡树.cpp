// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,m;

namespace Treap
{
	struct node
	{
		int lson,rson,val,priority;
		int sz,flip;
		node () {}
		inline node (int _v,int _p,int _l,int _r) {val=_v;priority=_p;lson=_l;rson=_r;flip=0;}
	}tree[MAXN+48];int tot,Root;
	inline void init() {tot=0;Root=0;}
	inline void pushdown(int cur) {if (tree[cur].flip) tree[tree[cur].lson].flip^=1,tree[tree[cur].rson].flip^=1,swap(tree[cur].lson,tree[cur].rson);tree[cur].flip=0;}
	inline void pushup(int cur) {tree[cur].sz=1+tree[tree[cur].lson].sz+tree[tree[cur].rson].sz;}
	inline int Create(int val,int priority,int l,int r) {++tot;tree[tot]=node(val,priority,l,r);pushup(tot);return tot;}
	inline Pair split(int cur,int k)
	{
		if (!cur) return mp(0,0);
		pushdown(cur);
		int leftsz=tree[tree[cur].lson].sz+1;
		if (k>=leftsz)
		{
			Pair splitted=split(tree[cur].rson,k-leftsz);
			tree[cur].rson=splitted.x;pushup(cur);
			return mp(cur,splitted.y);
		}
		else
		{
			Pair splitted=split(tree[cur].lson,k);
			tree[cur].lson=splitted.y;pushup(cur);
			return mp(splitted.x,cur);
		}
	}
	inline int merge(int root1,int root2)
	{
		if (!root1 || !root2) return root1^root2;
		if (tree[root1].priority<tree[root2].priority)
		{
			pushdown(root1);
			tree[root1].rson=merge(tree[root1].rson,root2);
			pushup(root1);return root1;
		}
		else
		{
			pushdown(root2);
			tree[root2].lson=merge(root1,tree[root2].lson);
			pushup(root2);return root2;
		}
	}
	inline void insert(int val) {Root=merge(Root,Create(val,rand(),0,0));}
	inline void reverse(int l,int r)
	{
		Pair splitted=split(Root,l-1),splitted2=split(splitted.y,r-l+1);
		tree[splitted2.x].flip^=1;
		Root=merge(splitted.x,merge(splitted2.x,splitted2.y));
	}
	inline void print(int cur)
	{
		if (!cur) return;
		pushdown(cur);
		print(tree[cur].lson);
		printf("%d ",tree[cur].val);
		print(tree[cur].rson);
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	srand(time(NULL));
	Get(n,m);Treap::init();int l,r;
	for (register int i=1;i<=n;i++) Treap::insert(i);
	while (m--)
	{
		Get(l,r);
		Treap::reverse(l,r);
	}
	Treap::print(Treap::Root);puts("");
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
