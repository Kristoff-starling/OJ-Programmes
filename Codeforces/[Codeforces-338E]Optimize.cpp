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

const int MAXN=3e5;

int n,m,h;

struct data
{
	int val;
	int nv,ind;
}a[MAXN+48];

inline bool cmp_val(data x,data y) {return x.val<y.val;}
inline bool cmp_ind(data x,data y) {return x.ind<y.ind;}

int b[MAXN+48];
int need[MAXN+48],table[MAXN+48];
int root=1;

namespace SegmentTree
{
	const int MAXN=1e7;
	int lson[MAXN+48],rson[MAXN+48],minn[MAXN+48],lazy[MAXN+48],cnt[MAXN+48],tot;
	inline int Create()
	{
		++tot;
		lson[tot]=rson[tot]=0;minn[tot]=INF;lazy[tot]=cnt[tot]=0;
		return tot;
	}
	inline void pushdown(int cur)
	{
		if (lazy[cur])
		{
			lazy[lson[cur]]+=lazy[cur];
			minn[lson[cur]]-=lazy[cur];
			lazy[rson[cur]]+=lazy[cur];
			minn[rson[cur]]-=lazy[cur];
			lazy[cur]=0;
		}
	}
	inline void pushup(int cur)
	{
		minn[cur]=INF;
		if (lson[cur]) minn[cur]=min(minn[cur],minn[lson[cur]]);
		if (rson[cur]) minn[cur]=min(minn[cur],minn[rson[cur]]);
		cnt[cur]=cnt[lson[cur]]+cnt[rson[cur]];
	}
	inline void init() {Create();minn[0]=INF;}
	inline void add(int &cur,int pos,int l,int r,int rnk)
	{
		if (!cur) cur=Create();
		if (l==r)
		{
			cnt[cur]++;
			minn[cur]=need[pos]-(rnk+cnt[cur]);
			assert(m!=90000 || minn[cur]>=0);
			return;
		}
		pushdown(cur);int mid=(l+r)>>1;
		if (pos<=mid) add(lson[cur],pos,l,mid,rnk); else add(rson[cur],pos,mid+1,r,rnk+cnt[lson[cur]]);
		pushup(cur);
	}
	inline void del(int cur,int pos,int l,int r,int rnk)
	{
		if (l==r)
		{
			cnt[cur]--;
			if (cnt[cur]) minn[cur]=need[pos]-(rnk+cnt[cur]); else minn[cur]=INF;
			return;
		}
		pushdown(cur);int mid=(l+r)>>1;
		if (pos<=mid) del(lson[cur],pos,l,mid,rnk); else del(rson[cur],pos,mid+1,r,rnk+cnt[lson[cur]]);
		if (!cnt[lson[cur]]) lson[cur]=0;
		if (!cnt[rson[cur]]) rson[cur]=0;
		pushup(cur);
	}
	inline void update(int cur,int left,int right,int l,int r,int delta)
	{
		if (!cur || r<left || l>right || left>right) return;
		if (left<=l && r<=right)
		{
			lazy[cur]+=delta;
			minn[cur]-=delta;
			return;
		}
		pushdown(cur);
		int mid=(l+r)>>1;
		update(lson[cur],left,right,l,mid,delta);
		update(rson[cur],left,right,mid+1,r,delta);
		pushup(cur);
	}
}

int main ()
{
	io.Get(n);io.Get(m);io.Get(h);
	for (register int i=1;i<=m;i++) io.Get(b[i]);
	for (register int i=1;i<=n;i++) io.Get(a[i].val),a[i].ind=i;
	sort(b+1,b+m+1);
	sort(a+1,a+n+1,cmp_val);int id=0;
	for (register int i=1;i<=n;i++)
	{
		if (i==1 || a[i].val!=a[i-1].val) id++;
		a[i].nv=id;table[id]=a[i].val;
	}
	sort(a+1,a+n+1,cmp_ind);
	int pt=m+1;
	for (register int i=1;i<=id;i++)
	{
		while (pt>1 && b[pt-1]+table[i]>=h) pt--;
		need[i]=m-pt+1;
	}
	int ans=0;
	SegmentTree::init();
	for (register int i=1;i<=m;i++)
	{
		SegmentTree::add(root,a[i].nv,1,id,0);
		SegmentTree::update(root,a[i].nv+1,id,1,id,1);
	}
	if (SegmentTree::minn[root]>=0) ans++;
	for (register int i=2;i<=n-m+1;i++)
	{
		int v1=a[i-1].nv,v2=a[m+i-1].nv;
		if (v1<v2)
		{
			SegmentTree::del(root,v1,1,id,0);
			SegmentTree::add(root,v2,1,id,0);
			if (v1+1<v2) SegmentTree::update(root,v1+1,v2-1,1,id,-1);
		}
		else
		{
			SegmentTree::add(root,v2,1,id,0);
			SegmentTree::del(root,v1,1,id,0);
			if (v2+1<v1) SegmentTree::update(root,v2+1,v1-1,1,id,1);
		}
		if (SegmentTree::minn[root]>=0) ans++;
	}
	io.Print(ans,'\n');
	io.flush();return 0;
}
