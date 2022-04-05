// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=786433;
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
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
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
    template<typename T> inline void Print(T x,char ch)
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
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
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
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=300000;

namespace polynomial
{
	const int NTT_MAX=8e5,G=10;
	int wn_pos[NTT_MAX+48],wn_neg[NTT_MAX+48];bool isfirst=true;
	inline void poly_init()
	{
		for (register int clen=2;clen<=262144;clen<<=1)
			wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
	inline void poly_ntt(int c[],int len,int fl)
	{
		if (isfirst) {poly_init();isfirst=false;}
		for (register int i=(len>>1),j=1;j<len;j++)
		{
			if (i<j) swap(c[i],c[j]);
			int k;for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
		}
		for (register int clen=2;clen<=len;clen<<=1)
		{
			int wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
			for (register int j=0;j<len;j+=clen)
			{
				int w=1;
				for (register int k=j;k<j+(clen>>1);k++)
				{
					int tmp1=c[k],tmp2=mul(c[k+(clen>>1)],w);
					c[k]=add(tmp1+tmp2);c[k+(clen>>1)]=sub(tmp1-tmp2);
					Mul(w,wn);
				}
			}
		}
		if (fl==-1)
		{
			int ilen=quick_pow(len,MOD-2);
			for (register int i=0;i<len;i++) Mul(c[i],ilen);
		}
	}
	inline void poly_mul(int A[],int B[],int N,int M,int C[])
	{
		int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)<<2);
		memset(B+M,0,(len-M)<<2);
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (register int i=0;i<len;i++) C[i]=mul(A[i],B[i]);
		poly_ntt(C,len,-1);
	}
}

int n,m;
vector<int> v[MAXN+48];

int fac[MAXN+48],dp[MAXN+48];

inline void init_fac()
{
	fac[0]=1;
	rep(i,1,MAXN) fac[i]=mul(fac[i-1],i);
}

inline bool check()
{
	rep(i,1,m)
	{
		sort(v[i].begin(),v[i].end());
		int delta=v[i][int(v[i].size())-1]-v[i][0];
		if (delta!=int(v[i].size())-1) return false;
	}
	return true;
}

inline void solve(int left,int right)
{
	if (left==right) {Add(dp[left],fac[left]);return;}
	int mid=(left+right)>>1;
	solve(left,mid);
	static int tmp1[MAXN+48],tmp2[MAXN+48],res[MAXN+48];
	tmp1[0]=tmp2[0]=0;
	rep(i,left,mid) tmp1[i-left+1]=dp[i];
	rep(i,1,right-left) tmp2[i]=fac[i];
	int N=mid-left+2,M=right-left+1;
	polynomial::poly_mul(tmp1,tmp2,N,M,res);
	rep(i,mid+1,right) Sub(dp[i],res[i-left+1]);
	solve(mid+1,right);
}

inline void input()
{
	Get(n,m);
	rep(i,1,m) v[i].clear();
	rep(i,1,m)
	{
		int nu,x;Get(nu);
		while (nu--) Get(x),v[i].pb(x);
	}
}

inline void solve()
{
	if (!check()) {puts("0");return;}
	int ans=1;
	rep(i,1,m) Mul(ans,dp[int(v[i].size())]);
	printf("%d\n",ans);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	init_fac();int ca;Get(ca);
	solve(1,100000);
	while (ca--)
	{
		input();
		solve();
	}
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
