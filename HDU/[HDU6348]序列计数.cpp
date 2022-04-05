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

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

const int MAXN=1e4;

int n;
int a[MAXN+48];

struct BIT
{
	#define LOWBIT(x) x & (-x)
	int c[MAXN+48];
	inline void init () {for (register int i=1;i<=n;i++) c[i]=0;}
	inline void update(int x,int delta) {while (x<=n) c[x]=add(c[x]+delta),x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res=add(res+c[x]),x-=LOWBIT(x);return res;}
}b[201];

int ans[MAXN+48];

int main ()
{
	int i,j,ca;ca=getint();int cc=0;
	while (ca--)
	{
		n=getint();
		for (i=1;i<=n;i++) a[i]=getint();
		for (i=1;i<=200;i++) b[i].init();
		for (i=1;i<=n;i++) ans[i]=0;
		for (i=1;i<=n;i++)
		{
			ans[1]=add(ans[1]+1);b[1].update(a[i],1);
			for (j=2;j<=200;j++)
			{
				int cur=b[j-1].query(a[i]-1);
				ans[j]=add(ans[j]+cur);
				b[j].update(a[i],cur);
			}
		}
		printf("Case #%d: ",++cc);
		for (i=1;i<=n;i++) printf(i==n?"%d":"%d ",ans[i]);
		puts("");
	}
	return 0;
}
