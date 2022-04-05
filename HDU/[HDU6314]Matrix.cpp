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

const int MAXN=3000;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int c[MAXN+48][MAXN+48];
inline void init_c()
{
	int i,j;c[0][0]=1;
	for (i=1;i<=MAXN;i++)
	{
		c[i][0]=c[i][i]=1;
		for (j=1;j<=i-1;j++)
			c[i][j]=add(c[i-1][j-1]+c[i-1][j]);
	}
}

int pw[MAXN*MAXN+48];
inline void init_pw()
{
	pw[0]=1;
	for (register int i=1;i<=MAXN*MAXN;i++) pw[i]=add(pw[i-1]+pw[i-1]);
}

int n,m,A,B;
int fa[MAXN+48],fb[MAXN+48];
inline void init_f()
{
	int i,j;
	fa[A]=1;
	for (i=A+1;i<=n;i++)
	{
		fa[i]=0;
		for (j=A;j<=i-1;j++)
			fa[i]=sub(fa[i]-(1ll*c[i-1][j-1]*fa[j])%MOD);
	}
	fb[B]=1;
	for (i=B+1;i<=m;i++)
	{
		fb[i]=0;
		for (j=B;j<=i-1;j++)
			fb[i]=sub(fb[i]-(1ll*c[i-1][j-1]*fb[j])%MOD);
	}
}

int main ()
{
	init_c();init_pw();int i,j;
	while (scanf("%d%d%d%d",&n,&m,&A,&B)!=EOF)
	{
		init_f();int ans=0;
		for (i=A;i<=n;i++)
			for (j=B;j<=m;j++)
				ans=add(ans+((((1ll*fa[i]*fb[j])%MOD*c[n][i])%MOD*c[m][j])%MOD*pw[(n-i)*(m-j)])%MOD);
		printf("%d\n",ans);
	}
	return 0;
}
