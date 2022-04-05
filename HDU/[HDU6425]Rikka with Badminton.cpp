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

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

int main ()
{
	int a,b,c,d,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(a);io.Get(b);io.Get(c);io.Get(d);
		int curans,ans;
		//d=1
		if (d>=1)
		{
			curans=d,ans=0;
			curans=(1ll*curans*quick_pow(2,a+c))%MOD;
			ans=add(ans+curans);
		}
		//d=0
		//c=0
		ans=add(ans+quick_pow(2,a+b));
		//c>=1,b=0
		if (c>=1)
		{
			curans=(1ll*quick_pow(2,a)*sub(quick_pow(2,c)-1))%MOD;
			ans=add(ans+curans);
		}
		//c>=1,b=1
		if (b>=1)
		{
			curans=((1ll*quick_pow(2,a)*sub(quick_pow(2,c)-1))%MOD*b%MOD);
			ans=add(ans+curans);
		}
		io.Print(ans);
	}
	io.flush();return 0;
}
