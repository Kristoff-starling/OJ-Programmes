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
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int n,m;
int dp[48][100048];int cnt[100048];
int b[48];

inline bool cmp(int x,int y) {return x>y;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MOD;
		x=1ll*x*x%MOD;y>>=1;
	}
	return res;
}

int fac[100048],inv[100048];
inline void init_inv()
{
	fac[0]=1;
	for (register int i=1;i<=100000;i++)
		fac[i]=1ll*fac[i-1]*i%MOD;
	inv[100000]=quick_pow(fac[100000],MOD-2);
	for (register int i=99999;i>=0;i--)
		inv[i]=1ll*inv[i+1]*(i+1)%MOD;
}

inline int C(int x,int y)
{
	if (x<y) return 0;
	return 1ll*fac[x]*inv[y]%MOD*inv[x-y]%MOD;
}

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);
	for (register int i=1;i<=m;i++) io.Get(b[i]);
	sort(b+1,b+m+1,cmp);init_inv();
	for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
	{
		cnt[Mask]=0;
		for (register int j=1;j<=n;j++)
			if (Mask&(1<<(j-1))) cnt[Mask]+=(1<<(j-1));
	}
	memset(dp,0,sizeof(dp));dp[0][0]=1;
	for (register int i=0;i<=m-1;i++)
		for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
			if (dp[i][Mask])
			{
				//not choose i
				dp[i+1][Mask]=add(dp[i+1][Mask]+dp[i][Mask]);
				//choose i
				for (register int j=1;j<=n;j++)
					if (!(Mask&(1<<(j-1))))
					{
						register int left=(1<<n)-b[i+1]-cnt[Mask],need=(1<<(j-1))-1;
						dp[i+1][Mask|(1<<(j-1))]=add(dp[i+1][Mask|(1<<(j-1))]+1ll*dp[i][Mask]*C(left,need)%MOD);
					}
			}
	int ans=0;
	for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
	{
		int curans=dp[m][Mask],left=(1<<n)-1-cnt[Mask];
		for (register int j=1;j<=n;j++)
			if (!(Mask&(1<<(j-1)))) curans=1ll*curans*C(left,(1<<(j-1)))%MOD,left-=(1<<(j-1));
		if (__builtin_popcount(Mask)%2==1)
			ans=sub(ans-curans);
		else
			ans=add(ans+curans);
	}
	for (register int i=1;i<=n;i++) ans=1ll*ans*fac[1<<(i-1)]%MOD;
	ans=1ll*ans*(1<<n)%MOD;
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}