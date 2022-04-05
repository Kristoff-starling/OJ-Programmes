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
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,q,len;
int a[MAXN+48];
int L[MAXN+48],R[MAXN+48];
int ll[MAXN+48][21],rr[MAXN+48][21];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);
	for (register int i=1;i<=n;i++) io.Get(a[i]);
	io.Get(len);
	for (register int i=1;i<=n;i++)
	{
		if (a[i]-a[1]<=len) {L[i]=1;continue;}
		int l=1,r=i-1,mid;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (a[i]-a[mid]<=len) L[i]=mid,r=mid-1; else l=mid+1;
		}
	}
	for (register int i=1;i<=n;i++)
	{
		if (a[n]-a[i]<=len) {R[i]=n;continue;}
		int l=i+1,r=n,mid;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (a[mid]-a[i]<=len) R[i]=mid,l=mid+1; else r=mid-1;
		}
	}
	for (register int i=1;i<=n;i++) ll[i][0]=L[i];
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=n;i++)
			ll[i][j]=ll[ll[i][j-1]][j-1];
	for (register int i=1;i<=n;i++) rr[i][0]=R[i];
	for (register int j=1;j<=20;j++)
		for (register int i=1;i<=n;i++)
			rr[i][j]=rr[rr[i][j-1]][j-1];
	io.Get(q);
	while (q--)
	{
		int x1,x2;io.Get(x1);io.Get(x2);
		if (x1<x2)
		{
			int ans=0,u=x1;
			for (register int i=20;i>=0;i--)
				if (rr[u][i]<x2) ans+=(1<<i),u=rr[u][i];
			io.Print(ans+1,'\n');
		}
		else
		{
			int ans=0,u=x1;
			for (register int i=20;i>=0;i--)
				if (ll[u][i]>x2) ans+=(1<<i),u=ll[u][i];
			io.Print(ans+1,'\n');
		}
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}