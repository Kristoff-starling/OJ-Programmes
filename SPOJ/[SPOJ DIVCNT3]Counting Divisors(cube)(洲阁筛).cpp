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

const int MAXN=1e6;

int prime[MAXN+48],tot;bool isprime[MAXN+48];
int D3[MAXN+48],small[MAXN+48];
inline void sieve()
{
	D3[1]=1;memset(isprime,true,sizeof(isprime));
	for (register int i=2;i<=MAXN;i++)
	{
		if (isprime[i]) prime[++tot]=i,D3[i]=4,small[i]=i;
		for (register int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0)
			{
				if (i==small[i]) D3[i*prime[j]]=D3[i]+3; else D3[i*prime[j]]=D3[i/small[i]]*D3[small[i]*prime[j]];
				small[i*prime[j]]=small[i]*prime[j];
			}
			else
				D3[i*prime[j]]=D3[i]*D3[prime[j]],small[i*prime[j]]=prime[j];
		}
	}
}

int L0[MAXN+48],L1[MAXN+48],cntP[MAXN+48];
LL g0[MAXN+48],g1[MAXN+48],f0[MAXN+48],f1[MAXN+48];

inline void calc_g(int sqrtn,int PN,LL n)
{
	for (register int i=1;i<=sqrtn;i++) g0[i]=i,g1[i]=n/i;
	for (register int i=1;i<=PN;i++)
	{
		for (register int j=1;j<=sqrtn && i<L1[j];j++)
		{
			LL x=n/j/prime[i];
			g1[j]-=((x<=sqrtn)?(g0[x]-max(0,min(i-1,cntP[x])-L0[x]+1)):(g1[n/x]-max(0,(i-1)-L1[n/x]+1)));
		}
		for (register int j=sqrtn;j>=1 && i<L0[j];j--)
		{
			LL x=j/prime[i];
			g0[j]-=(g0[x]-max(0,min(i-1,cntP[x])-L0[x]+1));
		}
	}
	for (register int i=1;i<=sqrtn;i++) g1[i]-=max(0,PN-L1[i]+1)+1;
	for (register int i=1;i<=sqrtn;i++) g1[i]*=4;
}

inline void calc_f(int sqrtn,int PN,LL n)
{
	for (register int i=1;i<=sqrtn;i++) f0[i]=f1[i]=1;
	for (register int i=PN;i>=1;i--)
	{
		for (register int j=1;j<=sqrtn && i<L1[j];j++)
		{
			LL x=n/j/prime[i];
			for (register int c=1;x;c++,x/=prime[i])
				f1[j]+=1ll*(3*c+1)*((x<=sqrtn)?f0[x]+4ll*max(0,cntP[x]-max(i+1,L0[x])+1):f1[n/x]+4ll*max(0,PN-max(i+1,L1[n/x])+1));
		}
		for (register int j=sqrtn;j>=1 && i<L0[j];j--)
		{
			LL x=j/prime[i];
			for (register int c=1;x;c++,x/=prime[i])
				f0[j]+=1ll*(3*c+1)*(f0[x]+4ll*max(0,cntP[x]-max(i+1,L0[x])+1));
		}
	}
	for (register int i=1;i<=sqrtn;i++) f1[i]+=4ll*(PN-L1[i]+1);
}

inline LL calc(LL n)
{
	int sqrtn=1;for (;1ll*sqrtn*sqrtn<=n;sqrtn++);sqrtn--;
	int PN=1;for (;1ll*prime[PN]*prime[PN]<=n;PN++);PN--;
	L0[0]=1;
	for (register int i=1;i<=sqrtn;i++)
		for (L0[i]=L0[i-1];1ll*prime[L0[i]]*prime[L0[i]]<=i;L0[i]++);
	L1[sqrtn+1]=1;
	for (register int i=sqrtn;i>=1;i--)
	{
		LL x=n/i;
		for (L1[i]=L1[i+1];1ll*prime[L1[i]]*prime[L1[i]]<=x;L1[i]++);
	}
	cntP[0]=0;
	for (register int j=1;j<=sqrtn;j++)
		for (cntP[j]=cntP[j-1];prime[cntP[j]+1]<=j;cntP[j]++);
	calc_g(sqrtn,PN,n);calc_f(sqrtn,PN,n);
	LL ans=f1[1];
	for (register int i=1;i<=sqrtn;i++) ans+=1ll*D3[i]*g1[i];
	return ans;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int ca;scanf("%d",&ca);LL n;
	sieve();
	while (ca--)
	{
		scanf("%lld",&n);
		printf("%lld\n",calc(n));
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
}
