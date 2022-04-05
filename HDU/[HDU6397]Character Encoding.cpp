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

const int MAXN=3e5;

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD,y>>=1;
	}
	return res;
}

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int fac[MAXN+48],finv[MAXN+48];
inline void init_inv()
{
	fac[0]=1;
	for (register int i=1;i<=MAXN;i++) fac[i]=(1ll*fac[i-1]*i)%MOD;
	finv[MAXN]=quick_pow(fac[MAXN],MOD-2);
	for (register int i=MAXN-1;i>=0;i--) finv[i]=(1ll*finv[i+1]*(i+1))%MOD;
}

inline int C(int x,int y)
{
	if (x<0 || y<0 || x<y) return 0;
	return ((1ll*fac[x]*finv[y])%MOD*finv[x-y])%MOD;
}

int n,m,k;

int main ()
{
	int ca;io.Get(ca);
	init_inv();
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(k);
		int ans=0;
		for (register int i=0;i<=m && n*i<=k;i++)
		{
			int delta=(1ll*C(m,i)*C(k-n*i+m-1,m-1))%MOD;
			if (i&1) ans=sub(ans-delta); else ans=add(ans+delta);
		}
		io.Print(ans);
	}
	io.flush();return 0;
}
