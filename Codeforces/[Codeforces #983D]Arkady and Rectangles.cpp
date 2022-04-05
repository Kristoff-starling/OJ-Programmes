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
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

const int MAXN=1e5;

int n;

struct Rec
{
	int down,up,left,right;
	int nl,nr;
	inline void input () {io.Get(left);io.Get(down);io.Get(right);io.Get(up);}
}a[MAXN+48];

struct point
{
	int pos,from,type;
	point () {}
	inline point (int pp,int ff,int tt) {pos=pp;from=ff;type=tt;}
	inline bool operator < (const point &other) const
	{
		if (pos!=other.pos) return pos<other.pos;
		if (type!=other.type) return type<other.type;
		if (!type) return from>other.from; else return from<other.from;
	}
}b[MAXN*2+48];int tot;

int ans[MAXN+48];

namespace SegmentTree
{
	struct node
	{
		set<int> s;
		int cmaxn,fmaxn,minn,hminn;
		node () {s.insert(0);cmaxn=fmaxn=minn=hminn=0;}
		inline void add(int x) {s.insert(x);cmaxn=(*s.rbegin());}
		inline void del(int x) {s.erase(x);cmaxn=(*s.rbegin());}
		inline void query(int lim) {if (cmaxn>=lim) ans[cmaxn]=1;}
	}tree[MAXN*8];
	inline void pushdown(int cur)
	{
		tree[cur].fmaxn=max(tree[cur].cmaxn,tree[cur>>1].fmaxn);
	}
	inline void pushup(int cur,bool isleaf)
	{
		tree[cur].minn=max(tree[cur].cmaxn,isleaf?0:min(tree[cur<<1].minn,tree[cur<<1|1].minn));
	}
	inline void solve(int cur,bool isleaf)
	{
		tree[cur].query(max(tree[cur].minn,tree[cur].hminn));
		if (!isleaf)
		{
			int ff=max(tree[cur].hminn,tree[cur].cmaxn);
			tree[cur<<1].hminn=min(tree[cur<<1].hminn,ff);
			tree[cur<<1|1].hminn=min(tree[cur<<1|1].hminn,ff);
		}
		tree[cur].hminn=tree[cur>>1].fmaxn;
	}
	inline void update(int cur,int left,int right,int id,int op,int l,int r)
	{
		pushdown(cur);solve(cur,l==r);
		if (left<=l && r<=right)
		{
			if (op==0) tree[cur].add(id); else tree[cur].del(id);
			pushdown(cur);pushup(cur,l==r);
			if (l!=r)
			{
				tree[cur<<1].hminn=min(tree[cur<<1].hminn,tree[cur].fmaxn);
				tree[cur<<1|1].hminn=min(tree[cur<<1|1].hminn,tree[cur].fmaxn);
			}
			tree[cur].query(max(tree[cur].minn,tree[cur].fmaxn));
			return;
		}
		int mid=(l+r)>>1;
		if (left<=mid) update(cur<<1,left,right,id,op,l,mid);
		if (mid+1<=right) update(cur<<1|1,left,right,id,op,mid+1,r);
		pushup(cur,l==r);tree[cur].query(max(tree[cur].minn,tree[cur].fmaxn));
	}
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	io.Get(n);int i,id;
	for (i=1;i<=n;i++) a[i].input();
	tot=0;for (i=1;i<=n;i++) b[++tot]=point(a[i].left,i,0),b[++tot]=point(a[i].right,i,1);
	sort(b+1,b+tot+1);id=0;
	for (i=1;i<=tot;i++)
	{
		if (i==1 || b[i].pos!=b[i-1].pos) id++;
		if (!b[i].type) a[b[i].from].nl=id; else a[b[i].from].nr=id;
	}
	tot=0;for (i=1;i<=n;i++) b[++tot]=point(a[i].down,i,0),b[++tot]=point(a[i].up,i,1);
	sort(b+1,b+tot+1);
	for (i=1;i<=tot;i++) cerr<<i<<endl,SegmentTree::update(1,a[b[i].from].nl,a[b[i].from].nr-1,b[i].from,b[i].type,1,id-1);
	int fans=0;for (i=1;i<=n;i++) fans+=ans[i];
	io.Print(fans+1);io.flush();return 0;
}
