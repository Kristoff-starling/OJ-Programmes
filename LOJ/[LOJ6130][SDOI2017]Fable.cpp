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
#define LOCAL true

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

const int MAXN=2e5;

int n,k;

Pair a[MAXN+48];
int ans[MAXN+48],b[MAXN+48],tot;

inline bool cmp(Pair x,Pair y)
{
	if (x.x!=y.x) return x.x>y.x;
	return x.y>y.y;
}

namespace BIT
{
	#define LOWBIT(x) x & (-x)
	int c[MAXN+48];
	inline void init () {memset(c,0,sizeof(c));}
	inline void update(int x,int delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
}

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	double t=clock();
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(k);
	for (register int i=1;i<=n;i++) io.Get(a[i].x),a[i].y=i;
	sort(a+1,a+n+1,cmp);
	BIT::init();
	for (register int i=1;i<=n;i++)
	{
		register int cnt=BIT::query(a[i].y);
		if (cnt>=k) ans[a[i].y-k]=a[i].x;
		else b[++tot]=a[i].x;
		BIT::update(a[i].y,1);
	}
	sort(b+1,b+tot+1);
	cerr<<"*"<<n<<endl;
	for (register int i=1,pt=1;i<=n;i++)
		if (!ans[i]) io.Print(b[pt++],'\n'); else io.Print(ans[i],'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
