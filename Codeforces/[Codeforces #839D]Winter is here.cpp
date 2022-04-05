#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))
// #define LOCAL true

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
template<typename T> inline T myabs(T x) {return (x>0)?x:(-x);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e6;

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

int n,a[MAXN+48],cnt[MAXN+48];

int fac[MAXN+48],ifac[MAXN+48];
inline void init_inv()
{
	fac[0]=1;for (register int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
	ifac[n]=quick_pow(fac[n],MOD-2);
	for (register int i=n-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

inline int C(int x,int y)
{
	if (x<0 || x<y) return 0;
	return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

int pw[MAXN+48],p[MAXN+48],F[MAXN+48];

int main ()
{
#ifdef LOCAL
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);for (register int i=1;i<=n;i++) Get(a[i]),cnt[a[i]]++;
	init_inv();pw[0]=1;for (register int i=1;i<=n;i++) pw[i]=add(pw[i-1]+pw[i-1]);
	for (register int i=1;i<=n;i++) p[i]=1ll*i*pw[i-1]%MOD;
	for (register int i=1;i<=MAXN;i++)
	{
		int sz=0;
		for (register int j=i;j<=MAXN;j+=i) sz+=cnt[j];
		F[i]=p[sz];
	}
	int ans=1ll*F[MAXN]*MAXN%MOD;
	for (register int i=MAXN-1;i>=2;i--)
	{
		for (register int j=i*2;j<=MAXN;j+=i) Sub(F[i],F[j]);
		Add(ans,1ll*F[i]*i%MOD);
	}
	printf("%d\n",ans);
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
