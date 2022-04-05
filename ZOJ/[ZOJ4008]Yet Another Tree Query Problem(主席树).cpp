#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
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

const int MAXN=2e5;

int n,q;
Pair edge[MAXN+48];

int root[MAXN+48];
namespace SegmentTree
{
	const int MAXM=5e6;
	int lson[MAXM+48],rson[MAXM+48],cnt[MAXM+48],tot;
	inline void init() {root[0]=0;tot=0;}
	inline int Create() {++tot;lson[tot]=rson[tot]=cnt[tot]=0;return tot;}
	inline void insert(int cur,int last,int pos,int l,int r)
	{
		lson[cur]=lson[last];rson[cur]=rson[last];cnt[cur]=cnt[last];
		cnt[cur]++;
		if (l==r) return;
		int mid=(l+r)>>1;
		if (pos<=mid)
		{
			lson[cur]=Create();
			insert(lson[cur],lson[last],pos,l,mid);
		}
		else
		{
			rson[cur]=Create();
			insert(rson[cur],rson[last],pos,mid+1,r);	
	}
	}
	inline int query(int left,int right,int pos,int l,int r)
	{
		if (l==r) return cnt[right]-cnt[left];
		int mid=(l+r)>>1;
		if (pos<=mid) return query(lson[left],lson[right],pos,l,mid); else return query(rson[left],rson[right],pos,mid+1,r)+cnt[lson[right]]-cnt[lson[left]];
	}
}

inline int bsearch(int pos)
{
	int l=1,r=n-1,mid,res=n;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (edge[mid].x>=pos) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int ca;//io.Get(ca);
	// cerr<<"*"<<endl;
	scanf("%d",&ca);
	// cerr<<ca<<endl;
	while (ca--)
	{
		// io.Get(n);io.Get(q);
		scanf("%d%d",&n,&q);
		// cerr<<n<<' '<<q<<endl;
		for (register int i=1;i<=n-1;i++)
		{
			// io.Get(edge[i].x);io.Get(edge[i].y);
			scanf("%d%d",&edge[i].x,&edge[i].y);
			if (edge[i].x>edge[i].y) swap(edge[i].x,edge[i].y);
		}
		sort(edge+1,edge+n);
		SegmentTree::init();
		for (register int i=1;i<=n-1;i++)
		{
			root[i]=SegmentTree::Create();
			SegmentTree::insert(root[i],root[i-1],edge[i].y,1,n);
		}
		// cerr<<"*"<<' '<<ca<<endl;
		while (q--)
		{
			// register int l,r;io.Get(l);io.Get(r);
			register int l,r;scanf("%d%d",&l,&r);
			int pos=bsearch(l),num=SegmentTree::query(root[pos-1],root[n-1],r,1,n);
			// io.Print(r-l+1-num,'\n');
			// cerr<<"*"<<endl;
			printf("%d\n",r-l+1-num);
		}
	}
	// io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
