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
//#define LOCAL true

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

int n;
int a[48],sum;
int table[2000048];
int A[48],B[48];
int suma[200048],sumb[200048];

namespace Hash
{
	const int hashmod=19260817;
	int head[hashmod+48],nxt[15000048];LL val[15000048];int tot=1;
	inline void insert(LL v)
	{
		int pos=v%hashmod;
		for (register int i=head[pos];i;i=nxt[i])
			if (val[i]==v) return;
		val[++tot]=v;nxt[tot]=head[pos];head[pos]=tot;
	}
	inline bool query(LL v)
	{
		int pos=v%hashmod;
		for (register int i=head[pos];i;i=nxt[i])
			if (val[i]==v) return true;
		return false;
	}
}

set<int> s[100048];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	cerr<<"Running..."<<endl;
#endif
	//freopen ("subsets.in","r",stdin);
	//freopen ("subsets.out","w",stdout);
	io.Get(n);
	for (register int i=1;i<=n;i++) io.Get(a[i]),sum+=a[i];
	int len1=n/4*3,len2=n-len1,sum=0;
	for (register int i=1;i<=len1;i++) A[i]=a[i];
	for (register int i=len1+1;i<=n;i++) B[i-len1]=a[i],sum+=a[i];
	for (register int Mask=0;Mask<=(1<<len1)-1;Mask++)
	{
		suma[Mask]=0;
		for (register int i=1;i<=len1;i++)
			if (Mask&(1<<(i-1))) suma[Mask]+=A[i];
	}
	for (register int Mask=0;Mask<=(1<<len2)-1;Mask++)
	{
		sumb[Mask]=0;
		for (register int i=1;i<=len2;i++)
			if (Mask&(1<<(i-1))) sumb[Mask]+=B[i];
	}
	for (register int Mask=0;Mask<=(1<<len1)-1;Mask++)
		for (register int sub=Mask;;sub=(sub-1)&Mask)
		{
			if (suma[sub]<suma[Mask^sub] || suma[sub]-suma[Mask^sub]>sum) {if (!sub) break; else continue;}
			Hash::insert(1ll*Mask*INF+(suma[sub]-suma[Mask^sub]));
			if (!sub) break;
		}
	int ans=0;
	for (register int Mask=0;Mask<=(1<<len2)-1;Mask++)
		for (register int toMask=0;toMask<=(1<<len1)-1;toMask++)
		{
			if (Mask==0 && toMask==0) continue;
			bool f=false;
			for (register int sub=Mask;;sub=(sub-1)&Mask)
			{
				if (sumb[sub]<sumb[Mask^sub]) {if (!sub) break; else continue;}
				if (Hash::query(1ll*toMask*INF+sumb[sub]-sumb[Mask^sub])) {f=true;break;}
				if (!sub) break;
			}
			if (f) ans++;
		}
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}