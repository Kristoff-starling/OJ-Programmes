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
const int magic=348;
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

int n,q;
int a[MAXN+48];ull sum[MAXN+48];

namespace BIT
{
	ull c[MAXN+48];
	inline void init() {memset(c,0,sizeof(c));}
	inline void modify(int x,int delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
	inline ull query(int x) {ull res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
}

struct Sequence
{
	int a[MAXN+48],b[MAXN+48],L[MAXN+48],R[MAXN+48],bel[MAXN+48],N;
	ull bsum[MAXN+48];
	inline void block()
	{
		for (register int i=1;i<=n;i++) b[i]=a[i];
		N=n/magic;if (n%magic) N++;
		for (register int i=1;i<=N;i++)
		{
			L[i]=(i-1)*magic+1;R[i]=(i==N?n:i*magic);
			for (register int j=L[i];j<=R[i];j++) bel[j]=i;
		}
		for (register int i=1;i<=N;i++) sort(b+L[i],b+R[i]+1);
		for (register int i=1;i<=N;i++)
			for (register int j=L[i];j<=R[i];j++)
				bsum[i]+=sum[b[j]];
	}
	inline void modify(int pos,int delta)
	{
		for (register int i=1;i<=N;i++)
		{
			int l=L[i],r=R[i],mid,st=R[i]+1;
			while (l<=r)
			{
				mid=(l+r)>>1;
				if (b[mid]>=pos) st=mid,r=mid-1; else l=mid+1;
			}
			bsum[i]+=1ll*delta*(R[i]-st+1);
		}
	}
	inline ull query(int l,int r)
	{
		if (bel[l]==bel[r])
		{
			ull res=0;
			for (register int i=l;i<=r;i++) res+=BIT::query(a[i])+sum[a[i]];
			return res;
		}
		int st=bel[l]+1,ed=bel[r]-1;ull res=0;
		for (register int i=st;i<=ed;i++) res+=bsum[i];
		for (register int i=l;i<=R[bel[l]];i++) res+=BIT::query(a[i])+sum[a[i]];
		for (register int i=L[bel[r]];i<=r;i++) res+=BIT::query(a[i])+sum[a[i]];
		return res;
	}
}L,R;

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);int l,r,x,y;for (register int i=1;i<=n;i++) Get(a[i]),sum[i]=sum[i-1]+a[i];
	for (register int i=1;i<=n;i++) Get(l,r),L.a[i]=l-1,R.a[i]=r;
	BIT::init();L.block();R.block();
	Get(q);int op;
	while (q--)
	{
		Get(op);
		if (op==1)
		{
			Get(x,y);int delta=y-a[x];
			BIT::modify(x,delta);a[x]=y;
			L.modify(x,delta);R.modify(x,delta);
		}
		else
		{
			Get(l,r);
			printf("%llu\n",R.query(l,r)-L.query(l,r));
		}
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
