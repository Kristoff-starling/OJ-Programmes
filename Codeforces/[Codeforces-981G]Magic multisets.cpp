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
		for (;ch>32;ch=Getchar()) *++s=ch;
		*(s+1)='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0'; else while (x) s[++pt]='0'+x%10,x/=10;
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=2e5;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int n,q;

namespace SegmentTree
{
	struct node
	{
		int left,right;
		int k,b,sum;
		inline node operator * (int t) {k=(1ll*k*t)%MOD;b=(1ll*b*t)%MOD;sum=(1ll*sum*t)%MOD;return (*this);}
		inline node operator + (int t) {b=add(b+t);sum=add(sum+(1ll*t*(right-left+1))%MOD);return (*this);}
	}tree[MAXN*4];
	inline void pushdown(int cur)
	{
		tree[cur<<1]=tree[cur<<1]*tree[cur].k;
		tree[cur<<1|1]=tree[cur<<1|1]*tree[cur].k;
		tree[cur<<1]=tree[cur<<1]+tree[cur].b;
		tree[cur<<1|1]=tree[cur<<1|1]+tree[cur].b;
		tree[cur].k=1;tree[cur].b=0;
	}
	inline void pushup(int cur) {tree[cur].sum=add(tree[cur<<1].sum+tree[cur<<1|1].sum);}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].k=1;tree[cur].b=0;tree[cur].sum=0;
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
	}
	inline void update(int cur,int left,int right,int t,int delta)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) {tree[cur]=tree[cur]*t;tree[cur]=tree[cur]+delta;return;}
		pushdown(cur);int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) update(cur<<1,left,right,t,delta);
		if (mid+1<=right) update(cur<<1|1,left,right,t,delta);
		pushup(cur);
	}
	inline int query(int cur,int left,int right)
	{
		if (left<=tree[cur].left && tree[cur].right<=right) return tree[cur].sum;
		pushdown(cur);int res=0;int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) res=add(res+query(cur<<1,left,right));
		if (mid+1<=right) res=add(res+query(cur<<1|1,left,right));
		pushup(cur);return res;
	}
}

int root[MAXN+48];
namespace DynamicSGT
{
	int lson[MAXN*80],rson[MAXN*80],sta[MAXN*80],tot=0;
	//0:no 1:mixed 2:all yes
	inline int Create()
	{
		++tot;sta[tot]=0;
		lson[tot]=rson[tot]=0;return tot;
	}
	inline void pushdown(int cur)
	{
		if (sta[cur]==2)
		{
			if (!lson[cur]) lson[cur]=Create();sta[lson[cur]]=2;
			if (!rson[cur]) rson[cur]=Create();sta[rson[cur]]=2;
		}
	}
	inline void pushup(int cur)
	{
		int ls=sta[lson[cur]],rs=sta[rson[cur]];
		if (ls==1 || rs==1) {sta[cur]=1;return;}
		if (!ls && !rs) {sta[cur]=0;return;}
		if (ls==2 && rs==2) {sta[cur]=2;return;}
		sta[cur]=1;
	}
	inline void build()
	{
		for (register int i=1;i<=n;i++) root[i]=Create();
	}
	inline void update(int &cur,int left,int right,int l,int r)
	{
		if (!cur) cur=Create();
		if (left<=l && r<=right && sta[cur]!=1)
		{
			if (!sta[cur]) {SegmentTree::update(1,l,r,1,1);sta[cur]=2;} else {SegmentTree::update(1,l,r,2,0);}
			return;
		}
		pushdown(cur);int mid=(l+r)>>1;
		if (left<=mid) update(lson[cur],left,right,l,mid);
		if (mid+1<=right) update(rson[cur],left,right,mid+1,r);
		pushup(cur);
	}
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	io.Get(n);io.Get(q);SegmentTree::build(1,1,n);
	int op,l,r,x;
	while (q--)
	{
		io.Get(op);io.Get(l);io.Get(r);
		if (op==1)
		{
			io.Get(x);
			DynamicSGT::update(root[x],l,r,1,n);
		}
		else
			io.Print(SegmentTree::query(1,l,r));
	}
	io.flush();
	return 0;
}
