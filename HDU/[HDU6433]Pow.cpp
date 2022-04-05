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
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

struct Bigint
{
	#define bucket 10000000
	int len;LL b[3048];
	inline void clear() {memset(b,0,sizeof(b));len=0;}
	inline void Set(int x)
	{
		len=0;
		if (x==0) {len=1;return;}
		while (x) b[++len]=x%bucket,x/=bucket;
	}
	inline Bigint operator + (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=max(len,other.len);i++)
		{
			res.b[i]+=b[i]+other.b[i];
			res.b[i+1]+=res.b[i]/bucket;
			res.b[i]%=bucket;
		}
		res.len=max(len,other.len);
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline Bigint operator * (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=len;i++)
			for (register int j=1;j<=other.len;j++)
				res.b[i+j-1]+=b[i]*other.b[j];
		for (register int i=1;i<=len+other.len-1;i++)
			res.b[i+1]+=res.b[i]/bucket,res.b[i]%=bucket;
		res.len=len+other.len-1;
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline int getw(int x)
	{
		if (!x) return 1;
		int res=0;
		while (x) res++,x/=10;
		return res;
	}
	inline void print()
	{
		io.Print(b[len]);
		for (register int i=len-1;i>=1;i--)
		{
			int w=getw(b[i]);
			for (register int j=1;j<=7-w;j++) io.Writechar('0');
			io.Print(b[i]);
		}
		io.Writechar('\n');
	}
}pro;

inline Bigint quick_pow(Bigint x,int y)
{
	Bigint res;res.Set(1);
	while (y)
	{
		if (y&1) res=res*x,y--;
		x=x*x;y>>=1;
	}
	return res;
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca;io.Get(ca);int n,i;pro.Set(2);
	while (ca--)
	{
		io.Get(n);
		quick_pow(pro,n).print();
	}
	io.flush();return 0;
}

