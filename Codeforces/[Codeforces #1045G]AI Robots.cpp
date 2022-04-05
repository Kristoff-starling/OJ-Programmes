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

const int INF=1e9;
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

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=1e5;

int n,k;

struct robot
{
	int iq,id;int l,r,nl,nr,nc;
}a[MAXN+48];
int iql[MAXN+48],iqr[MAXN+48],itot;
int toiq[MAXN+48];
Pair b[MAXN+48];

inline bool cmp_iq(robot x,robot y) {return x.iq<y.iq;}
inline bool cmp_center(robot x,robot y) {return x.nc<y.nc;}

int root[MAXN+48];
namespace SegmentTree
{
	const int MAXM=5e6;
	int lson[MAXM+48],rson[MAXM+48],cnt[MAXM+48],tot=0;
	inline int Create() {++tot;lson[tot]=rson[tot]=cnt[tot]=0;return tot;}
	inline void update(int &cur,int pos,int l,int r,int delta)
	{
		if (!cur) cur=Create();
		cnt[cur]+=delta;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid) update(lson[cur],pos,l,mid,delta); else update(rson[cur],pos,mid+1,r,delta);
	}
	inline int query(int cur,int left,int right,int l,int r)
	{
		if (!cur || right<l || left>r) return 0;
		if (left<=l && r<=right) return cnt[cur];
		int mid=(l+r)>>1;
		return query(lson[cur],left,right,l,mid)+query(rson[cur],left,right,mid+1,r);
	}
}

struct Pt
{
	int type,from,val;
	Pt () {}
	inline Pt (int tt,int ff,int vv) {type=tt;from=ff;val=vv;}
	inline bool operator < (const Pt &other) const {return val<other.val;}
}p[MAXN*6+48];int tot;

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(k);int x,r;
	for (register int i=1;i<=n;i++)
	{
		io.Get(x);io.Get(r);io.Get(a[i].iq);
		a[i].l=x-r;a[i].r=x+r;
	}
	sort(a+1,a+n+1,cmp_iq);
	a[1].id=1;
	for (register int i=2;i<=n;i++) a[i].id=a[i-1].id+(a[i].iq!=a[i-1].iq),toiq[a[i].id]=a[i].iq;
	int curl=1,curr=0;itot=a[n].id;
	for (register int i=1;i<=itot;i++)
	{
		while (curr<itot && toiq[curr+1]-toiq[i]<=k) curr++;
		while (curl<itot && toiq[i]-toiq[curl]>k) curl++;
		iql[i]=curl;iqr[i]=curr;
	}
	tot=0;
	for (register int i=1;i<=n;i++) p[++tot]=Pt(1,i,a[i].l),p[++tot]=Pt(2,i,(a[i].l+a[i].r)>>1),p[++tot]=Pt(3,i,a[i].r);
	sort(p+1,p+tot+1);int lim=0;
	for (register int i=1;i<=tot;i++)
	{
		if (i==1 || p[i].val!=p[i-1].val) lim++;
		if (p[i].type==1)
			a[p[i].from].nl=lim;
		else if (p[i].type==2)
			a[p[i].from].nc=lim;
		else
			a[p[i].from].nr=lim;
	}
	sort(a+1,a+n+1,cmp_center);
	for (register int i=1;i<=n;i++) b[i]=mp(a[i].nl,i);
	sort(b+1,b+n+1);int pt=0;
	LL ans=0;
	for (register int i=1;i<=n;i++)
	{
		while (pt<=n && b[pt].x<=a[i].nc)
			SegmentTree::update(root[a[b[pt].y].id],a[b[pt].y].nc,1,lim,1),pt++;
		SegmentTree::update(root[a[i].id],a[i].nc,1,lim,-1);
		for (register int j=iql[a[i].id];j<=iqr[a[i].id];j++)
			ans+=SegmentTree::query(root[j],a[i].nl,a[i].nr,1,lim);
	}
	io.Print(ans,'\n');io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}