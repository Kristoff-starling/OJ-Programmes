// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=1500;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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
const int MAXV=3e4;

namespace polynomial
{
	struct Complex
	{
		double r,i;
		Complex () {}
		inline Complex(double _r,double _i) {r=_r,i=_i;}
		inline Complex operator + (Complex other) {return Complex(r+other.r,i+other.i);}
		inline Complex operator - (Complex other) {return Complex(r-other.r,i-other.i);}
		inline Complex operator * (Complex other) {return Complex(r*other.r-i*other.i,r*other.i+i*other.r);}
		inline Complex operator / (double t) {return Complex(r/t,i/t);}
	}a[MAXN+48],b[MAXN+48];
	inline void poly_fft(Complex c[],int len,int fl)
	{
		for (register int i=(len>>1),j=1;j<len;j++)
		{
			if (i<j) swap(c[i],c[j]);
			int k;for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
		}
		for (register int clen=2;clen<=len;clen<<=1)
		{
			Complex wn=Complex(cos(pi*2.0*fl/clen),sin(pi*2.0*fl/clen));
			for (register int j=0;j<len;j+=clen)
			{
				Complex w=Complex(1,0);
				for (register int k=j;k<j+(clen>>1);k++)
				{
					Complex tmp1=c[k],tmp2=c[k+(clen>>1)]*w;
					c[k]=tmp1+tmp2;c[k+(clen>>1)]=tmp1-tmp2;
					w=w*wn;
				}
			}
		}
		if (fl==-1)
			for (register int i=0;i<len;i++) c[i]=c[i]/len;
	}
	inline void poly_mul(LL A[],LL B[],int N,int M,LL C[])
	{
		int len=1;while (len<=N+M) len<<=1;
		for (register int i=0;i<N;i++) a[i]=Complex(A[i],0);for (register int i=N;i<len;i++) a[i]=Complex(0,0);
		for (register int i=0;i<M;i++) b[i]=Complex(B[i],0);for (register int i=M;i<len;i++) b[i]=Complex(0,0);
		poly_fft(a,len,1);poly_fft(b,len,1);
		for (register int i=0;i<len;i++) a[i]=a[i]*b[i];
		poly_fft(a,len,-1);
		for (register int i=0;i<N+M-1;i++) C[i]=(LL)(a[i].r+0.5);
	}
}

int n,V,a[MAXN+48];

int N,L[MAXN+48],R[MAXN+48],bel[MAXN+48];
LL f[MAXN+48],g[MAXN+48],res[MAXN+48];
int cnt[MAXV+48];

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);for (register int i=1;i<=n;i++) Get(a[i]),check_max(V,a[i]);V++;
	N=n/magic;if (n%magic) N++;
	for (register int i=1;i<=N;i++)
	{
		L[i]=(i-1)*magic+1;R[i]=(i==N?n:L[i]+magic-1);
		for (register int j=L[i];j<=R[i];j++) bel[j]=i;
	}
	LL ans=0;
	for (register int i=2;i<=N-1;i++)
	{
		memset(f,0,sizeof(f));memset(g,0,sizeof(g));memset(res,0,sizeof(res));
		for (register int j=1;j<=R[i-1];j++) f[a[j]]++;
		for (register int j=L[i+1];j<=n;j++) g[a[j]]++;
		polynomial::poly_mul(f,g,V,V,res);
		for (register int j=L[i];j<=R[i];j++) ans+=res[2*a[j]];
	}
	memset(cnt,0,sizeof(cnt));
	for (register int i=n;i>=1;i--)
	{
		for (register int j=L[bel[i]];j<=i-1;j++)
			if (2*a[i]-a[j]>=1 && 2*a[i]-a[j]<V) ans+=cnt[2*a[i]-a[j]];
		cnt[a[i]]++;
	}
	memset(cnt,0,sizeof(cnt));
	for (register int i=1;i<=n;i++)
	{
		if (i==L[bel[i]] && i!=1)
			for (register int j=L[bel[i]-1];j<=R[bel[i]-1];j++) cnt[a[j]]++;
		for (register int j=i+1;j<=R[bel[i]];j++)
			if (2*a[i]-a[j]>=1 && 2*a[i]-a[j]<V) ans+=cnt[2*a[i]-a[j]];
	}
	printf("%lld\n",ans);
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
