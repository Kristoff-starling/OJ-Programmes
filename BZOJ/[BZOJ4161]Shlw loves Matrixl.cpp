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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=2000;

int n,k;
int a[MAXN+48],h[MAXN+48];
int g[MAXN+48],inv[MAXN+48];

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

inline void construct_g()
{
	int i;
	g[k]=1;for (i=k;i>=1;i--) g[k-i]=sub(-a[i]);
	if (k&1) for (i=k;i>=0;i--) g[i]=sub(-g[i]);
	for (i=0;i<=k;i++) inv[i]=quick_pow(g[i],MOD-2);
}

struct poly
{
	int a[MAXN*5+48],len;
	inline void clear() {for (register int i=0;i<len;i++) a[i]=0;}
	inline poly operator * (poly other)
	{
		poly res;res.len=len+other.len-1;res.clear();
		for (register int i=0;i<len;i++)
			for (register int j=0;j<other.len;j++)
				res.a[i+j]=add(res.a[i+j]+(1ll*a[i]*other.a[j])%MOD);
		for (register int i=res.len-1;i>=k;i--)
		{
			int tmp=(1ll*inv[k]*res.a[i])%MOD;
			for (register int j=i;j>=i-k;j--)
				res.a[j]=sub(res.a[j]-(1ll*g[j-i+k]*tmp)%MOD);
		}
		if (res.len>k) res.len=k;
		return res;
	}
	inline void print() {for (register int i=0;i<len;i++) cout<<a[i]<<' ';cout<<endl;}
};

inline poly quick_pow(poly x,int y)
{
	poly res;res.len=1;res.a[0]=1;
	while (y)
	{
		if (y&1) res=res*x,y--;
		x=x*x;y>>=1;
	}
	return res;
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int i;n=getint();k=getint();
	for (i=1;i<=k;i++) a[i]=getint();
	for (i=0;i<=k-1;i++) h[i]=getint(),h[i]=add(h[i]+MOD);
	if (n<=k-1) {printf("%d\n",add(h[n]+MOD));return 0;}
	construct_g();poly base;base.len=2;base.a[1]=1;base.a[0]=0;
	poly res=quick_pow(base,n);
	int ans=0;
	for (i=0;i<=k-1;i++) ans=add(ans+(1ll*h[i]*res.a[i])%MOD);
	printf("%d\n",ans);
	return 0;
}
