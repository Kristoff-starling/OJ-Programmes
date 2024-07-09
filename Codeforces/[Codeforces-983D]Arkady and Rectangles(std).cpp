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

const int MAXN=2e5;

namespace SegmentTree
{
	struct node
	{
		int left,right;
		set<int> marked,unmarked;
		int maxn,minn;
	}tree[MAXN*4];
	inline void pushup(int cur)
	{
		tree[cur].maxn=tree[cur].minn=-1;
		if (tree[cur].left!=tree[cur].right)
		{
			tree[cur].maxn=max(tree[cur<<1].maxn,tree[cur<<1|1].maxn);
			tree[cur].minn=min(tree[cur<<1].minn,tree[cur<<1|1].minn);
		}
		if (tree[cur].unmarked.size()) tree[cur].maxn=max(tree[cur].maxn,*tree[cur].unmarked.rbegin());
		if (tree[cur].marked.size()) tree[cur].minn=max(tree[cur].minn,*tree[cur].marked.rbegin());
		if (tree[cur].maxn<tree[cur].minn) tree[cur].maxn=-1;
	}
	inline void build(int cur,int left,int right)
	{
		tree[cur].left=left;tree[cur].right=right;
		tree[cur].marked.clear();tree[cur].unmarked.clear();
		if (left!=right)
		{
			int mid=(left+right)>>1;
			build(cur<<1,left,mid);build(cur<<1|1,mid+1,right);
		}
		pushup(cur);
	}
	inline void add(int cur,int left,int right,bool type,int val)
	{
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			if (!type) tree[cur].unmarked.insert(val); else tree[cur].marked.insert(val);
			pushup(cur);return;
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) add(cur<<1,left,right,type,val);
		if (mid+1<=right) add(cur<<1|1,left,right,type,val);
		pushup(cur);
	}
	inline void del(int cur,int left,int right,bool type,int val)
	{
		if (left<=tree[cur].left && tree[cur].right<=right)
		{
			if (!type) tree[cur].unmarked.erase(val); else tree[cur].marked.erase(val);
			pushup(cur);return;
		}
		int mid=(tree[cur].left+tree[cur].right)>>1;
		if (left<=mid) del(cur<<1,left,right,type,val);
		if (mid+1<=right) del(cur<<1|1,left,right,type,val);
		pushup(cur);
	}
}

int n;

struct node
{
	int left,right,down,up;
	int nl,nr;
	inline void input() {io.Get(left);io.Get(down);io.Get(right);io.Get(up);}
}a[MAXN+48];

struct point
{
	int val;bool type;int from;
	point () {}
	inline point(int vv,bool tt,int ff) {val=vv;type=tt;from=ff;}
	inline bool operator < (const point &other) const
	{
		if (val!=other.val) return val<other.val;
		if (type!=other.type) return type;
		if (!type) return from>other.from; else return from<other.from;
	}
}b[MAXN+48];int tot;

bool marked[MAXN+48];

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	io.Get(n);int i;
	for (i=1;i<=n;i++) a[i].input(),b[++tot]=point(a[i].left,false,i),b[++tot]=point(a[i].right,true,i);
	sort(b+1,b+tot+1);int id=0;
	for (i=1;i<=tot;i++)
	{
		if (i==1 || b[i].val!=b[i-1].val) id++;
		if (!b[i].type) a[b[i].from].nl=id; else a[b[i].from].nr=id;
	}
	tot=0;for (i=1;i<=n;i++) b[++tot]=point(a[i].down,false,i),b[++tot]=point(a[i].up,true,i);
	sort(b+1,b+tot+1);
	SegmentTree::build(1,1,id-1);
	for (i=0;;)
	{
		do
		{
			++i;
			if (!b[i].type) SegmentTree::add(1,a[b[i].from].nl,a[b[i].from].nr-1,false,b[i].from);
			else SegmentTree::del(1,a[b[i].from].nl,a[b[i].from].nr-1,marked[b[i].from],b[i].from);
		}
		while (i<tot && b[i+1].val==b[i].val);
		while (SegmentTree::tree[1].maxn!=-1)
		{
			int curcol=SegmentTree::tree[1].maxn;
			marked[curcol]=true;
			SegmentTree::del(1,a[curcol].nl,a[curcol].nr-1,false,curcol);
			SegmentTree::add(1,a[curcol].nl,a[curcol].nr-1,true,curcol);
		}
		if (i==tot) break;
	}
	int cnt=1;for (i=1;i<=n;i++) cnt+=marked[i];
	io.Print(cnt,'\n');
	io.flush();return 0;
}
