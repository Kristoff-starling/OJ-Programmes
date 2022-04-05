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
const int MOD=998244353;
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
const int MAXM=5e6;

int n,m;
unsigned int X,Y,Z;

namespace Generator
{
	inline unsigned int RNG61()
	{
		X=X^(X<<11);
		X=X^(X>>4);
		X=X^(X<<5);
		X=X^(X>>14);
		unsigned int W=X^(Y^Z);
		X=Y;Y=Z;Z=W;
		return Z;
	}
	unsigned int f[MAXM*3+48];
	inline void init() {for (register int i=1;i<=m*3;i++) f[i]=RNG61();}
	inline void gen(int i,int &l,int &r,int &v)
	{
		l=f[i*3-2]%n+1;r=f[i*3-1]%n+1;
		if (l>r) swap(l,r);
		v=f[i*3]%(1<<30);
	}
}

int Log[MAXN+48];
int ST[MAXN+48][21];

int main ()
{
	int i,j,ca,l,r,v;ca=getint();
	Log[0]=Log[1]=0;for (i=2;i<=MAXN;i++) Log[i]=Log[i>>1]+1;
	while (ca--)
	{
		n=getint();m=getint();X=getint();Y=getint();Z=getint();
		for (i=1;i<=n;i++)
			for (j=0;j<=20;j++)
				ST[i][j]=0;
		Generator::init();
		for (i=1;i<=m;i++)
		{
			Generator::gen(i,l,r,v);
			int k=Log[r-l+1];
			ST[l][k]=max(ST[l][k],v);ST[r-(1<<k)+1][k]=max(ST[r-(1<<k)+1][k],v);
		}
		for (j=20;j>=1;j--)
			for (i=1;i<=n-(1<<j)+1;i++)
				ST[i][j-1]=max(ST[i][j-1],ST[i][j]),ST[i+(1<<(j-1))][j-1]=max(ST[i+(1<<(j-1))][j-1],ST[i][j]);
		LL ans=0;
		for (i=1;i<=n;i++) ans^=(1ll*i*ST[i][0]);
		printf("%lld\n",ans); 
	}
	return 0;
}
