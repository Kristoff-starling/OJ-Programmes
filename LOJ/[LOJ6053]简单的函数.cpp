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

LL n;int inv2;

int prime[MAXN+48],sump[MAXN+48],tot;bool isprime[MAXN+48];int F[MAXN+48],small[MAXN+48],t[MAXN+48];
inline void sieve()
{
	F[1]=1;sump[0]=0;memset(isprime,true,sizeof(isprime));
	for (register int i=2;i<=MAXN;i++)
	{
		if (isprime[i]) prime[++tot]=i,F[i]=(i^1),t[i]=1,small[i]=i,sump[tot]=add(sump[tot-1]+i);
		for (register int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0)
			{
				F[i*prime[j]]=1ll*F[i/small[i]]*(prime[j]^(t[i]+1))%MOD;
				small[i*prime[j]]=small[i]*prime[j];t[i*prime[j]]=t[i]+1;
				break;
			}
			else
				F[i*prime[j]]=1ll*F[i]*F[prime[j]]%MOD,small[i*prime[j]]=prime[j],t[i*prime[j]]=1;
		}
	}
}

int L0[MAXN+48],L1[MAXN+48],cntP[MAXN+48];
int g0[MAXN+48],g1[MAXN+48],G0[MAXN+48],G1[MAXN+48],f0[MAXN+48],f1[MAXN+48];

inline int calc_sump(int left,int right) {if (left>right) return 0;return sub(sump[right]-sump[left-1]);}
inline int calc_fp(int x) {return x^1;}
inline int calc_fpk(int x,int y) {return x^y;}
inline int calc_sumf(int left,int right)
{
	if (left>right) return 0;
	int res=sub(sub(sump[right]-sump[left-1])-(right-left+1));
	if (left==1) Add(res,2);
	return res;
}

inline void calc_g(int sqrtn,int PN)
{
	for (register int i=1;i<=sqrtn;i++) g0[i]=i,G0[i]=1ll*(i+1)*i%MOD*inv2%MOD,g1[i]=n/i,G1[i]=1ll*(n/i+1)%MOD*((n/i)%MOD)%MOD*inv2%MOD;
	for (register int i=1;i<=PN;i++)
	{
		for (register int j=1;j<=sqrtn && i<L1[j];j++)
		{
			LL x=n/j/prime[i];
			Sub(g1[j],(x<=sqrtn?sub(g0[x]-max(0,min(i-1,cntP[x])-L0[x]+1)):sub(g1[n/x]-max(0,i-L1[n/x]))));
			Sub(G1[j],1ll*prime[i]*(x<=sqrtn?sub(G0[x]-calc_sump(L0[x],min(i-1,cntP[x]))):sub(G1[n/x]-calc_sump(L1[n/x],i-1)))%MOD);
		}
		for (register int j=sqrtn;j>=1 && i<L0[j];j--)
		{
			LL x=j/prime[i];
			Sub(g0[j],sub(g0[x]-max(0,min(i-1,cntP[x])-L0[x]+1)));
			Sub(G0[j],1ll*prime[i]*sub(G0[x]-calc_sump(L0[x],min(i-1,cntP[x])))%MOD);
		}
	}
	for (register int i=1;i<=sqrtn;i++)
	{
		Sub(g1[i],add(max(0,PN-L1[i]+1)+1));Sub(G1[i],add(calc_sump(L1[i],PN)+1));
		g1[i]=sub(G1[i]-g1[i]);
	}
	if (sqrtn==1 && n>=2) Add(g1[1],2);
}

inline void calc_f(int sqrtn,int PN)
{
	for (register int i=1;i<=sqrtn;i++) f0[i]=f1[i]=1;
	for (register int i=PN;i>=1;i--)
	{
		for (register int j=1;j<=sqrtn && i<L1[j];j++)
		{
			LL x=n/j/prime[i];
			for (register int c=1;x;x/=prime[i],c++)
				Add(f1[j],1ll*calc_fpk(prime[i],c)*(x<=sqrtn?add(f0[x]+calc_sumf(max(L0[x],i+1),cntP[x])):add(f1[n/x]+calc_sumf(max(L1[n/x],i+1),PN)))%MOD);
		}
		for (register int j=sqrtn;j>=1 && i<L0[j];j--)
		{
			LL x=j/prime[i];
			for (register int c=1;x;x/=prime[i],c++)
				Add(f0[j],1ll*calc_fpk(prime[i],c)*add(f0[x]+calc_sumf(max(L0[x],i+1),cntP[x]))%MOD);
		}
	}
	for (register int i=1;i<=sqrtn;i++) Add(f1[i],calc_sumf(L1[i],PN));
}

inline int calc()
{
	int sqrtn=1;for (;1ll*sqrtn*sqrtn<=n;sqrtn++);sqrtn--;
	int PN=1;for (;1ll*prime[PN]*prime[PN]<=n;PN++);PN--;
	L0[0]=0;for (register int i=1;i<=sqrtn;i++) for (L0[i]=L0[i-1];1ll*prime[L0[i]]*prime[L0[i]]<=i;L0[i]++);
	L1[sqrtn+1]=0;for (register int i=sqrtn;i>=1;i--) for (L1[i]=L1[i+1];1ll*prime[L1[i]]*prime[L1[i]]<=n/i;L1[i]++);
	cntP[0]=0;for (register int i=1;i<=sqrtn;i++) for (cntP[i]=cntP[i-1];prime[cntP[i]+1]<=i;cntP[i]++);
	inv2=quick_pow(2,MOD-2);
	calc_g(sqrtn,PN);calc_f(sqrtn,PN);
	int res=f1[1];
	for (register int i=1;i<=sqrtn;i++) Add(res,1ll*g1[i]*F[i]%MOD);
	return res;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%lld",&n);sieve();
	printf("%d\n",calc());
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}
