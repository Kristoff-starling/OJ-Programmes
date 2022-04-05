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

const int MAXN=1e6;

int n;
int a[MAXN+48],b[MAXN+48];

int c[MAXN*2+48],RL[MAXN*2+48],maxright,pos,len;
inline void Manacher()
{
	for (register int i=1;i<=n-1;i++) c[++len]=INF,c[++len]=b[i];
	c[++len]=INF;
	maxright=pos=0;
	for (register int i=1;i<=len;i++)
	{
		if (i<maxright) RL[i]=min(RL[2*pos-i],maxright-i); else RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=len && c[i-RL[i]]==c[i+RL[i]]) RL[i]++;
		if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
	}
}

inline bool check_valid(int left,int right)
{
	if (left>right) return true;
	int mid=(left+right)>>1,pos=mid*2;
	int L=left*2,R=(right-1)*2;
	if (pos-RL[pos]+1<=L && pos+RL[pos]-1>=R) return true; else return false;
}

inline bool calc_val(int l1,int r1,int l2,int r2)
{
	if (l1>r1 || l2>r2) return true;
	return (a[l1]+a[r1])==(a[l2]+a[r2]);
}

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
	for (register int i=1;i<=n-1;i++) b[i]=a[i]-a[i+1];
	Manacher();
	for (register int i=0;i<=n-2;i+=2)
		if (check_valid(1,i) && check_valid(i+1,n) && calc_val(1,i,i+1,n)) {io.Print(i/2,'\n');io.flush();return 0;}
	printf("IMPOSSIBLE\n");
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
