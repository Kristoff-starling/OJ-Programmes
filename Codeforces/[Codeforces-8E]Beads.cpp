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

int n;LL k;
int a[148];LL pw[148];

inline LL Count(int len)
{
	int Len=min(len,n-len);LL res=0;
	//not reverse
	for (register int i=2;i<=Len;i++)
		if (a[i]==0) res+=pw[n-len-i];
	if ((len<<1)<n)
	{
		LL p=pw[(n-Len-Len+1)/2],np=pw[n-Len-Len]-p;
		res+=p+np/2;
	}
	else
	{
		bool f=true;
		for (register int i=Len+1,j=n-Len;i<=j;i++,j--)
		{
			if (a[i]==0 && a[j]==1) break;
			if (a[i]==1 && a[j]==0) {f=false;break;}
		}
		if (f) res++;
	}
	bool f=true;
	for (register int i=1;i<=len;i++) if (a[i]) {f=false;break;}
	if (f) res--; // 000...0 is not allowed
	if (len==n) return res;
	//reverse,a[n]=1;
	for (register int i=2;i<=Len;i++)
		if (a[i]==0) res+=pw[n-len-i];
	if ((len<<1)<n)
	{
		if ((n-Len-Len)%2==0)
		{
			LL p=pw[(n-Len-Len+1)/2],np=pw[n-Len-Len]-p;
			res+=p+np/2;
		}
		else
		{
			LL p=pw[(n-Len-Len+1)/2],np=pw[n-Len-Len]-p;
			p/=2;
			res+=p+np/2;
		}
	}
	else
	{
		bool f=true;
		for (register int i=Len+1,j=n-Len;i<=j;i++,j--)
		{
			if (a[i]==0 && a[j]==0) break;
			if (a[i]==1 && a[j]==1) {f=false;break;}
		}
		if (f) res++;
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
	io.Get(n);io.Get(k);a[1]=0;
	pw[0]=1;for (register int i=1;i<=n;i++) pw[i]=pw[i-1]+pw[i-1]; 
	if (Count(1)<k) {printf("-1\n");return 0;}
	for (register int i=2;i<=n;i++)
	{
		a[i]=0;
		register LL res=Count(i);
		if (k>res) k-=res,a[i]=1;
	}
	for (register int i=1;i<=n;i++) printf("%d",a[i]);
	printf("\n");
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}