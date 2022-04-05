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

int n;
struct node
{
	int val,nv,ind;
}a[MAXN+48];
inline bool cmp_val(node x,node y) {return x.val<y.val;}
inline bool cmp_ind(node x,node y) {return x.ind<y.ind;}

namespace BIT
{
	#define LOWBIT(x) x & (-x)
	int c[MAXN+48];
	inline void init() {for (register int i=1;i<=n;i++) c[i]=0;}
	inline void update(int x) {while (x<=n) c[x]++,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x-=LOWBIT(x);return res;}
}

int X,Y;

int main ()
{
	while (scanf("%d%d%d",&n,&X,&Y)!=EOF)
	{
		int i;
		for (i=1;i<=n;i++) scanf("%d",&a[i].val),a[i].ind=i;
		sort(a+1,a+n+1,cmp_val);a[1].nv=1;
		for (i=2;i<=n;i++) a[i].nv=a[i-1].nv+(a[i].val!=a[i-1].val);
		sort(a+1,a+n+1,cmp_ind);
		BIT::init();LL cnt=0;
		for (i=n;i>=1;i--) cnt+=BIT::query(a[i].nv-1),BIT::update(a[i].nv);
		cnt*=min(X,Y);
		printf("%lld\n",cnt);		
	}
	return 0;
}
