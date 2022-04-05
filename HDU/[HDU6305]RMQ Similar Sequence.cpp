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

const int MAXN=1e6;

int n;
int a[MAXN+48];
vector<int> v[MAXN+48];
int pos[MAXN+48];

int inv[MAXN+48],finv[MAXN+48],fac[MAXN+48];
inline void init_inv()
{
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (register int i=2;i<=MAXN;i++)
	{
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		fac[i]=(1ll*fac[i-1]*i)%MOD;
		finv[i]=(1ll*finv[i-1]*inv[i])%MOD;
	}
}

inline int C(int x,int y)
{
	int res=fac[x];
	res=(1ll*res*finv[y])%MOD;res=(1ll*res*finv[x-y])%MOD;
	return res;
}

struct DSU
{
	int pre[MAXN+48];
	inline void init() {for (register int i=0;i<=n+1;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}dsu;

int L[MAXN+48],R[MAXN+48];

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int ca;ca=getint();int i,j,pt;
	init_inv();
	while (ca--)
	{
		n=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		for (i=1;i<=n;i++) v[i].clear();
		for (i=n;i>=1;i--) v[a[i]].pb(i);
		pt=0;
		for (i=1;i<=n;i++)
			for (j=0;j<int(v[i].size());j++)
				a[v[i][j]]=++pt,pos[pt]=v[i][j];
		a[0]=a[n+1]=n+1;
		dsu.init();
		for (i=1;i<=n;i++)
		{
			L[i]=dsu.find_anc(pos[i]-1)+1;
			dsu.update(pos[i],pos[i]-1);
		}
		dsu.init();
		for (i=1;i<=n;i++)
		{
			R[i]=dsu.find_anc(pos[i]+1)-1;
			dsu.update(pos[i],pos[i]+1);
		}
		int ans=1;
		for (i=1;i<=n;i++) ans=(1ll*ans*C(R[i]-L[i],R[i]-pos[i]))%MOD;
		ans=(((1ll*ans*finv[n])%MOD*inv[2])%MOD*n)%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
