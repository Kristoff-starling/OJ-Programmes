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

const int MAXN=1e5;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int fac[MAXN+48],inv[MAXN+48],finv[MAXN+48];
inline void init_inv()
{
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (register int i=2;i<=MAXN;i++)
	{
		fac[i]=(1ll*fac[i-1]*i)%MOD;
		inv[i]=MOD-(1ll*(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(1ll*finv[i-1]*inv[i])%MOD;
	}
}

inline int C(int x,int y)
{
	return ((1ll*fac[x]*finv[y])%MOD*finv[x-y])%MOD;
}

struct Query
{
	int n,m,ind;
	inline bool operator < (const Query &other) const
	{
		if (n/magic!=other.n/magic) return n/magic<other.n/magic;
		return m<other.m;
	}
}q[MAXN+48];
int ans[MAXN+48];

int main ()
{
	init_inv();int i,ca;ca=getint();
	for (i=1;i<=ca;i++) q[i].n=getint(),q[i].m=getint(),q[i].ind=i;
	sort(q+1,q+ca+1);
	int L=1,R=0,curans=1;
	for (i=1;i<=ca;i++)
	{
		if (q[i].n>=L)
		{
			while (L<q[i].n) curans=sub((1ll*curans*2)%MOD-C(L++,R));
			while (R<q[i].m) curans=add(curans+C(L,++R));
			while (R>q[i].m) curans=sub(curans-C(L,R--));
		}
		else
		{
			while (L>q[i].n) curans=(1ll*add(curans+C(--L,R))*inv[2])%MOD;
			while (R<q[i].m) curans=add(curans+C(L,++R));
			while (R>q[i].m) curans=sub(curans-C(L,R--));
		}
		ans[q[i].ind]=curans;
	}
	for (i=1;i<=ca;i++) printf("%d\n",ans[i]);
	return 0;
}
