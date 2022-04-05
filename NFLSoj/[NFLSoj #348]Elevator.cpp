#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define x first
#define y second
#define pLL pair<LL,LL>
#define mp make_pair
// #define LOCAL true

template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e6;

int n;

struct people
{
	LL t,x;
	inline void input() {scanf("%lld%lld",&t,&x);}
	inline bool operator < (const people &other) const {return t<other.t;}
}a[MAXN+48],b[MAXN+48];int tot;

LL dp[MAXN+48];
pLL q[MAXN+48];int head,tail;

int main ()
{
#ifdef LOCAL
	double T=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	scanf("%d",&n);for (register int i=1;i<=n;i++) a[i].input();
	sort(a+1,a+n+1);
	for (register int i=1;i<=n;i++)
	{
		while (tot && b[tot].x<a[i].x) tot--;
		b[++tot]=a[i];
	}
	for (register int i=1;i<=tot;i++) a[i]=b[i];
	dp[0]=0;int pt=0;head=1,tail=0;
	for (register int i=1;i<=tot;i++)
	{
		while (head<=tail && q[tail].y>=dp[i-1]+2ll*a[i].x) tail--;
		q[++tail]=mp(i-1,dp[i-1]+2ll*a[i].x);
		while (pt+1<i && dp[pt+1]<=a[i].t) pt++;
		while (head<=tail && q[head].x<=pt) head++;
		dp[i]=a[i].t+2ll*a[pt+1].x;
		if (head<=tail) check_min(dp[i],q[head].y);
	}
	printf("%lld\n",dp[tot]);
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
