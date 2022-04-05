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

const int MAXN=400;

int n;
struct node
{
	//clockwise
	int a,b,c,d;
	node () {}
	inline node (int aa,int bb,int cc,int dd) {a=aa;b=bb;c=cc;d=dd;}
	inline void input() {io.Get(a);io.Get(b);io.Get(c);io.Get(d);}
	inline void print() {cerr<<a<<' '<<b<<' '<<c<<' '<<d<<endl;}
	inline bool operator == (const node &other) const
	{
		return a==other.a && b==other.b && c==other.c && d==other.d;
	}
	inline bool operator < (const node &other) const
	{
		if (a!=other.a) return a<other.a;
		if (b!=other.b) return b<other.b;
		if (b!=other.c) return c<other.c;
		return d<other.d;
	}
}a[MAXN+48];

inline LL tohash(node x)
{
	LL res=x.d;
	res=res*1048+x.c;
	res=res*1048+x.b;
	res=res*1048+x.a;
	return res;
}

map<LL,int> Mp;
vector<node> v;

inline int cnt_same(node x,node y)
{
	int res=0;
	if (x==y) res++;
	if (x==node(y.b,y.c,y.d,y.a)) res++;
	if (x==node(y.c,y.d,y.a,y.b)) res++;
	if (x==node(y.d,y.a,y.b,y.c)) res++;
	return res;
}

inline void print(node x) {x.print();}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);LL ans=0;
	for (register int i=1;i<=n;i++) a[i].input();
	for (register int i=n;i>=1;i--)
	{
		for (register int j=0;j<int(v.size());j++)
		{
			node A,B,C,D;
			A=node(a[i].b,a[i].a,v[j].b,v[j].a);
			B=node(a[i].c,a[i].b,v[j].a,v[j].d);
			C=node(a[i].d,a[i].c,v[j].d,v[j].c);
			D=node(a[i].a,a[i].d,v[j].c,v[j].b);
			//if (i==4 && j==4) cerr<<"--------"<<endl,A.print(),B.print(),C.print(),D.print(),cerr<<"----------"<<endl;
			//if (i==4 && j==4) cerr<<Mp[tohash(C)]<<"%%%%"<<endl;
			LL cur=1;
			cur=cur*(Mp[tohash(A)]-cnt_same(A,v[j]));
			cur=cur*(Mp[tohash(B)]-cnt_same(B,v[j])-cnt_same(B,A));
			cur=cur*(Mp[tohash(C)]-cnt_same(C,v[j])-cnt_same(C,A)-cnt_same(C,B));
			cur=cur*(Mp[tohash(D)]-cnt_same(D,v[j])-cnt_same(D,A)-cnt_same(D,B)-cnt_same(D,C));
			//if (i==4 && j==4) {cerr<<cur<<"!!!";v[j].print();}
			//cerr<<i<<' '<<j<<' '<<cur<<endl;
			ans+=cur;
		}
		Mp[tohash(a[i])]++;
		Mp[tohash(node(a[i].b,a[i].c,a[i].d,a[i].a))]++;
		Mp[tohash(node(a[i].c,a[i].d,a[i].a,a[i].b))]++;
		Mp[tohash(node(a[i].d,a[i].a,a[i].b,a[i].c))]++;
		//cerr<<"~~~~~~~~~~~~~~~~"<<endl;
		//print(a[i]);
		//print(node(a[i].b,a[i].c,a[i].d,a[i].a));
		//print(node(a[i].c,a[i].d,a[i].a,a[i].b));
		//print(node(a[i].d,a[i].a,a[i].b,a[i].c));
		//cerr<<"~~~~~~~~~~~~~~~~"<<endl;
		v.pb(a[i]);
		v.pb(node(a[i].b,a[i].c,a[i].d,a[i].a));
		v.pb(node(a[i].c,a[i].d,a[i].a,a[i].b));
		v.pb(node(a[i].d,a[i].a,a[i].b,a[i].c));
	}
	cout<<ans<<endl;
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}