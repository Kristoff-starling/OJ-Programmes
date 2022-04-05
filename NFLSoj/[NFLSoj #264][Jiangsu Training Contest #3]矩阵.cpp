#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int 
#define pb push_back
#define pf push_front
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
#define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

inline void Getchar(char &x)
{
	while (!isalpha(x=getchar()));
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=2000;

int n,m,q;
int a[MAXN+48][MAXN+48];

int main ()
{
	Get(n);Get(m);Get(q);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			a[i][j]=(i-1)*m+j;
	int x1,y1,x2,y2;char op;
	while (q--)
	{
		Getchar(op);Get(x1);Get(y1);Get(x2);Get(y2);
		if (op=='H')
			for (register int i=x1;i<=x2;i++)
				for (register int l=y1,r=y2;l<r;swap(a[i][l],a[i][r]),l++,r--);
		else
			for (register int l=x1,r=x2;l<r;l++,r--)
				for (register int j=y1;j<=y2;j++) swap(a[l][j],a[r][j]);
	}
	LL sum;
	for (register int i=1;i<=n;i++)
	{
		sum=0;
		for (register int j=1;j<=m;j++) sum+=a[i][j];
		printf("%lld ",sum);
	}
	printf("\n");
	for (register int j=1;j<=m;j++)
	{
		sum=0;
		for (register int i=1;i<=n;i++) sum+=a[i][j];
		printf("%lld ",sum);
	}
	printf("\n");
	return 0;
}
