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
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

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

const int MAXN=3e4;

int n;LL a[MAXN+48];int ans[MAXN+48];
int m;int d[MAXN+48];LL c[MAXN+48];int num[MAXN+48][48],L[MAXN+48];

int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
int table[348];

int len;

inline void getnum(int d,int id,int num[]) {REP(i,len,1) num[i]=id%(d+1),id/=(d+1);}
inline int getid(int d,int num[]) {int res=0;rep(i,1,len) res=res*(d+1)+num[i];return res;}

int dp[9000048];

inline int solve(int id,int curd,int p)
{
	if (dp[id]!=-1) return dp[id];
	int num[48];getnum(curd,id,num);
	int pos=-1;
	rep(i,1,len) if (num[i]==curd) {pos=i;break;}
	if (pos==-1)
	{
		int x=getid(curd-1,num);
		if (x>=n) return dp[id]=1; else return dp[id]=(a[x]%p);
	}
	dp[id]=1;
	rep(i,0,curd-1)
	{
		num[pos]=i;
		dp[id]=dp[id]*solve(getid(curd,num),curd,p)%p;
	}
	return dp[id];
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	rep(i,0,9) table['0'+i]=i; rep(i,65,70) table[i]=i-55;
	Get(n);rep(i,0,n-1) Get(a[i]);
	char s[48];int tmp[48];
	Get(m);rep(i,1,m)
	{
		Get(d[i]);
		scanf("%s",s+1);
		int l=strlen(s+1);L[i]=l;rep(j,1,l) num[i][j]=(s[j]!='?'?table[s[j]]:d[i]);
		Get(c[i]);
	}
	rep(i,1,m) ans[i]=-1;
	rep(nu,0,24)
	{
		int p=prime[nu];
		rep(curd,2,16)
		{
			len=1;int prod=curd;while (prod-1<n-1) len++,prod*=curd;
			int Max=0;rep(i,1,len) Max=Max*(curd+1)+curd;
			rep(i,0,Max) dp[i]=-1;
			rep(i,1,m) if (d[i]==curd && ans[i]==-1)
			{
				bool f=false;
				rep(j,1,L[i]-len) if (num[i][j]!=curd && num[i][j]!=0) {f=true;break;}
				if (f)
				{
					int fans=(c[i]%p);
					if (!fans) ans[i]=p;
				}
				else
				{
					rep(j,L[i]-len+1,L[i]) tmp[j-L[i]+len]=num[i][j];
					int fans=(solve(getid(curd,tmp),curd,p)+c[i]%p)%p;
					if (!fans) ans[i]=p;
				}
			}
		}
	}
	rep(i,1,m) printf("%d\n",ans[i]);
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
