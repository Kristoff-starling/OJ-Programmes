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
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,m;
int A[MAXN+48],B[MAXN+48];
vector<int> tmp;

struct node
{
	int x,y,ny;
	inline bool operator < (const node &other) const {return x<other.x;}
}a[MAXN+48];int tot;

struct Pt
{
	int val,from;
	Pt () {}
	inline Pt (int vv,int ff) {val=vv;from=ff;}
	inline bool operator < (const Pt &other) {return val<other.val;}
}b[MAXN+48];int btot,itot;

map<Pair,bool> Mp;

namespace BIT
{
	int c[MAXN+48];
	inline void init() {memset(c,0,sizeof(c));}
	inline void update(int x,int delta) {while (x<=itot) Add(c[x],delta),x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) {Add(res,c[x]),x-=LOWBIT(x);}return res;}
	inline int query(int left,int right) {return query(right)-query(left-1);}
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);
	for (register int i=1;i<=n;i++) io.Get(A[i]);
	for (register int i=1;i<=m;i++) io.Get(B[i]);
	int pt=0;B[0]=0;tot=btot=0;Mp.clear();
	for (register int i=1;i<=n;i++)
	{
		while (pt<=m && B[pt]<=A[i]) pt++;pt--;
		if (!pt || pt==m || Mp.find(mp(A[i]-B[pt],B[pt+1]-A[i]))!=Mp.end()) continue;
		a[++tot].x=A[i]-B[pt];a[tot].y=B[pt+1]-A[i];Mp[mp(a[tot].x,a[tot].y)]=true;
		b[++btot]=Pt(a[tot].y,tot);
	}
	sort(b+1,b+btot+1);itot=0;
	for (register int i=1;i<=btot;i++)
	{
		if (i==1 || b[i].val!=b[i-1].val) itot++;
		a[b[i].from].ny=itot;
	}
	BIT::init();int ans=0;
	sort(a+1,a+tot+1);pt=1;
	while (pt<=tot)
	{
		register int pt1=pt;
		while (pt1<=tot && a[pt1].x==a[pt].x) pt1++;pt1--;
		tmp.clear();
		for (register int i=pt;i<=pt1;i++)
		{
			int val=add(1+BIT::query(1,a[i].ny-1));
			Add(ans,val);tmp.pb(val);
		}
		for (register int i=pt;i<=pt1;i++) BIT::update(a[i].ny,tmp[i-pt]);
		pt=pt1+1;
	}
	io.Print(add(ans+1),'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}