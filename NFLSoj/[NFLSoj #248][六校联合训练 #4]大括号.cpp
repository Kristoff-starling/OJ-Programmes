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
#define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=666623333;
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

const int MAXN=5000;

int n,p,q,a,b,Lwin,Rwin;
char s[MAXN+48];

int dp1[MAXN+48][MAXN+48],dp2[MAXN+48][MAXN+48];

int main ()
{
	// freopen ("a.in","r",stdin);
	// freopen ("a.out","w",stdout);
	io.Get(n);io.Get(p);io.Get(q);io.Get(a);io.Get(b);
	Lwin=1ll*p*quick_pow(p+q,MOD-2)%MOD;
	Rwin=1ll*q*quick_pow(p+q,MOD-2)%MOD;
	io.getstring(s+1);
	dp1[0][a]=1;
	for (register int i=1;i<=n;i++)
	{
		if (s[i]=='L')
			for (register int j=0;j<=n;j++)
				dp1[i][j]=dp1[i-1][j+1];
		else
		{
			int presum=0;
			for (register int j=1;j<=n;j++)
			{
				presum=add(1ll*presum*Rwin%MOD+1ll*dp1[i-1][j]*Lwin%MOD);
				dp1[i][j]=presum;
			}
		}
	}
	dp2[n+1][b]=1;
	for (register int i=n;i>=1;i--)
	{
		if (s[i]=='R')
			for (register int j=0;j<=n;j++)
				dp2[i][j]=dp2[i+1][j+1];
		else
		{
			int presum=0;
			for (register int j=1;j<=n;j++)
			{
				presum=add(1ll*presum*Lwin%MOD+1ll*dp2[i+1][j]*Rwin%MOD);
				dp2[i][j]=presum;
			}
		}
	}
	int ans=0;
	for (register int i=0;i<=n;i++) Add(ans,1ll*dp1[i][0]*dp2[i+1][0]%MOD);
	io.Print(ans,'\n');io.flush();
	return 0;			
}