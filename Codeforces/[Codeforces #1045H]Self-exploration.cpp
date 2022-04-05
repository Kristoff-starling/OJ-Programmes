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

template <typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template <typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=1e5;

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

int inv[MAXN+48],fac[MAXN+48];

inline void init_inv()
{
	fac[0]=1;
	for (register int i=1;i<=MAXN;i++) fac[i]=(1ll*fac[i-1]*i)%MOD;
	inv[MAXN]=quick_pow(fac[MAXN],MOD-2);
	for (register int i=MAXN-1;i>=0;i--) inv[i]=(1ll*inv[i+1]*(i+1))%MOD;
}

inline int C(int x,int y)
{
	if (x<y || x<0 || y<0) return 0;
	return 1ll*fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}

inline int split(int x,int y)
{
	if (!y) {return x==0;}
	return C(x+y-1,y-1);
}

inline int calc(int c[2][2])
{
	if (c[0][1]-c[1][0]<0 || c[0][1]-c[1][0]>1) return 0;
	return 1ll*split(c[0][0],c[1][0]+1)*split(c[1][1],c[0][1])%MOD;
}

int c[2][2],cc[2][2],n;

char A[MAXN+48],B[MAXN+48];

inline int solve(int c[2][2],char *s)
{
	int len=strlen(s+1);
	if (len==1 && s[1]=='0') return 0;
	if (len<n) return 0;
	if (len>n) for (register int i=n;i>=1;i--) s[i]='1';
	char last='1';int res=0,i;
	for (i=n-1;i>=1;i--)
		if (s[i]=='1')
		{
			if (c[last-'0'][0])
			{
				c[last-'0'][0]--;
				res=add(res+calc(c));
				c[last-'0'][0]++;
			}
			if (!c[last-'0'][1]) break;
			c[last-'0'][1]--;last='1';
		}
		else
		{
			if (!c[last-'0'][0]) break;
			c[last-'0'][0]--;last='0';
		}
	if (!i) res=add(res+1);
	return res;
}

inline void Minus()
{
	int len=strlen(A+1),pt=1;
	while (A[pt]=='0') A[pt]='1',pt++;
	A[pt]='0';
	while (len>=1 && A[len]=='0') len--;
	if (!len) len++;
	A[len+1]='\0';
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	init_inv();
	io.getstring(A+1);io.getstring(B+1);
	int lena=strlen(A+1),lenb=strlen(B+1);
	reverse(A+1,A+lena+1);reverse(B+1,B+lenb+1);
	io.Get(c[0][0]);io.Get(c[0][1]);io.Get(c[1][0]);io.Get(c[1][1]);
	Minus();n=c[0][0]+c[0][1]+c[1][0]+c[1][1]+1;
	for (register int i=0;i<=1;i++)
		for (register int j=0;j<=1;j++)
			cc[i][j]=c[i][j];
	int resb=solve(c,B),resa=solve(cc,A);
	io.Print(sub(resb-resa),'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}