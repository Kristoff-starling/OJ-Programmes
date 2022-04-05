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

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch=='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

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

const int MAXN=1e4;
const LL LIM=1e12;

LL n,m;int k;
LL a[MAXN+48];

LL A[MAXN+48],M[MAXN+48];

inline LL quick_mul(LL x,LL y,LL MO)
{
	LL res=0;bool f=true;if (y<0) f=false,y=-y;
	while (y)
	{
		if (y&1) res=(res+x)%MO;
		x=(x+x)%MO;y>>=1;
	}
	if (!f) res=-res;
	while (res<0) res+=MO;
	return res;
}

inline void exgcd(LL a,LL b,LL &x,LL &y)
{
	if (!b) {x=1;y=0;return;}
	exgcd(b,a%b,x,y);
	LL tmp=x;x=y;y=tmp-a/b*y;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);Get(m);Get(k);for (register int i=1;i<=k;i++) Get(a[i]);
	LL LCM=a[1];
	for (register int i=2;i<=k;i++)
	{
		LL g=gcd(LCM, a[i]);
		if (LCM/g>LIM/a[i]) {puts("NO");return 0;}
		LCM=LCM/g*a[i];
	}
	if (LCM>n) {puts("NO");return 0;}
	for (register int i=1;i<=k;i++)
	{
		A[i]=1-i;
		LL tmp=(-A[i])/a[i];A[i]+=tmp*a[i];
		if (A[i]<0) A[i]+=a[i];
		M[i]=a[i];
	}
	LL aa=A[1],mm=M[1];
	for (register int i=2;i<=k;i++)
	{
		LL c=A[i]-aa,g=gcd(mm,M[i]);
		if (c%g) {puts("NO");return 0;}
		LL x,y;exgcd(mm,M[i],x,y);
		x=quick_mul(x,c/g,mm*M[i]/g);
		LL cur=aa+quick_mul(mm,x,mm*M[i]/g),delta=M[i]/g;
		if (cur<0)
		{
			LL tmp=(-cur)/(delta*mm);
			cur+=(delta*mm)*tmp;x=(x+quick_mul(delta,tmp,mm*M[i]/g))%(mm*M[i]/g);
			if (cur<0) cur+=delta*mm,x=(x+delta)%(mm*M[i]/g);
		}
		if (cur>0)
		{
			LL tmp=cur/(delta*mm);
			cur-=(delta*mm)*tmp;x=x-quick_mul(delta,tmp,mm*M[i]/g);
			while (x<0) x+=mm*M[i]/g;
		}
		mm=mm*M[i]/g;aa=cur%mm;
	}
	if (!aa) aa=LCM;
	if (aa+k-1>m) {puts("NO");return 0;}
	else
	{
		for (register LL i=aa;i<=aa+k-1;i++) if (gcd(LCM,i)!=a[i-aa+1]) {puts("NO");return 0;}
		puts("YES");return 0;
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}

