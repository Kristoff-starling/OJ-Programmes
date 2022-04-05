#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LIBNF=2e16;
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

const int MAXN=2e5;

int n,q,L[MAXN+48],R[MAXN+48];
int mex[MAXN+48];

int root[MAXN+48];
namespace SegmentTree
{
	int lson[MAXN*20],rson[MAXN*20],minn[MAXN*20],tot;
	inline void pushup(int cur) {minn[cur]=min(minn[lson[cur]],minn[rson[cur]]);}
	inline void build(int &cur,int l,int r)
	{
		if (l==r) return;
		if (!cur) cur=++tot;
		int mid=(l+r)>>1;
		build(lson[cur],l,mid);build(rson[cur],mid+1,r);
	}
	inline void insert(int cur,int last,int pos,int nv,int l,int r)
	{
		lson[cur]=lson[last];rson[cur]=rson[last];
		if (l==r) {minn[cur]=nv;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) lson[cur]=++tot,insert(lson[cur],lson[last],pos,nv,l,mid);
		else rson[cur]=++tot,insert(rson[cur],rson[last],pos,nv,mid+1,r);
		pushup(cur);
	}
	inline int query(int cur,int pos,int l,int r)
	{
		if (l==r) return l;
		int mid=(l+r)>>1;
		if (minn[lson[cur]]>=pos) return query(rson[cur],pos,mid+1,r); else return query(lson[cur],pos,l,mid);
	}
}

int main ()
{
	Get(n);for (register int i=2;i<=n;i++) Get(L[i]),Get(R[i]);
	SegmentTree::build(root[0],0,n);
	root[1]=++SegmentTree::tot;SegmentTree::insert(root[1],root[0],0,1,0,n);mex[1]=0;
	for (register int i=2;i<=n;i++)
	{
		mex[i]=SegmentTree::query(root[R[i]],L[i],0,n);
		root[i]=++SegmentTree::tot;SegmentTree::insert(root[i],root[i-1],mex[i],i,0,n);
	}
	Get(q);int num,x;
	while (q--)
	{
		Get(num);int xsum=0;
		while (num--) Get(x),xsum^=mex[x];
		printf("%d\n",xsum);
	}
	return 0;
}
