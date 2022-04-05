#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <iomanip>
#include <bitset>
#include <cmath>
#include <functional>
#include <sstream>
#include <algorithm>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <vector>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

LL N;

inline LL mod(LL x,LL MO) {while (x>=MO) x-=MO;while (x<0) x+=MO;return x;}
inline LL gcd(LL x,LL y) {return y==0?x:gcd(y,x%y);}
inline LL myabs(LL x) {return x>=0?x:-x;}

inline LL quick_mul(LL x,LL y,LL MO)
{
	LL res=0;x%=MO;
	while (y)
	{
		if (y&1) res=mod(res+x,MO);
		x=mod(x+x,MO);y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y,LL MO)
{
	LL res=1;x%=MO;
	while (y)
	{
		if (y&1) res=quick_mul(res,x,MO),y--;
		x=quick_mul(x,x,MO);y>>=1;
	}
	return res;
}

int lp[]={2,3,5,7,11,13,17,19,23,29,31,37};
LL x[148];
inline bool Miller_Rabin(LL n)
{
	int i;
	for (i=0;i<=11;i++)
	{
		if (n==lp[i]) return true;
		if (n%lp[i]==0) return false;
	}
	int ti=20;LL tmp=n-1;int k=0;
	while (!(tmp&1)) k++,tmp>>=1;
	while (ti--)
	{
		LL a=rand()%(n-2)+2;
		x[0]=quick_pow(a,tmp,n);
		for (i=1;i<=k;i++)
		{
			x[i]=quick_mul(x[i-1],x[i-1],n);
			if (x[i]==1 && x[i-1]!=1 && x[i-1]!=n-1) return false;
		}
		if (x[k]!=1) return false;
	}
	return true;
}

inline LL pollard_rho(LL n,LL c)
{
	LL x=rand()%n,y=x;LL i=1,k=2;
	while (true)
	{
		i++;
		x=mod(quick_mul(x,x,n)+c,n);
		LL p=gcd(myabs(x-y),n);
		if (p!=1 && p!=n) return p;
		if (y==x) return n;
		if (i==k)
		{
			y=x;
			k<<=1;
		}
	}
	return n;
}

vector<LL> fac;
inline void findfac(LL n)
{
	if (n==1) return;
	if (Miller_Rabin(n)) {fac.pb(n);return;}
	LL p=n;
	while (p>=n) p=pollard_rho(p,rand()%n);
	findfac(p);findfac(n/p);
}

int main ()
{
	srand(time(NULL));
	N=getLL();
	if (N==1) {puts("1");return 0;}
	if (Miller_Rabin(N)) {printf("%lld\n",N-1);return 0;}
	findfac(N);
	sort(fac.begin(),fac.end());LL ans=N;
	for (register int i=0;i<int(fac.size());i++)
	{
		if (i && fac[i-1]==fac[i]) continue;
		ans=ans-ans/fac[i];
	}
	printf("%lld\n",ans);
	return 0;
}
