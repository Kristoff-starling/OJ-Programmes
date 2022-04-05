#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <functional>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
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

const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL quick_pow(LL x,LL y)
{
	LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

int n,k;
LL s[5048][5048];
LL inv[5048],finv[5048],fac[5048];

inline void init_inv()
{
	inv[0]=finv[0]=inv[1]=finv[1]=1;
	for (register int i=2;i<=k;i++)
	{
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
}

inline void init_stirling()
{
	int i,j;
	s[1][1]=1;
	for (i=2;i<=k;i++)
		for (j=1;j<=i;j++)
			s[i][j]=(s[i-1][j-1]+(long long)j*s[i-1][j])%MOD;
}

inline LL C(int x,int y)
{
	if (x<y) return 0;
	LL res=1;
	for (register int i=x;i>=x-y+1;i--) res=(res*i)%MOD;
	res=(res*finv[y])%MOD;
	return res;
}

int main ()
{
	int i;LL ans=0;
	n=getint();k=getint();
	init_stirling();init_inv();
	fac[0]=fac[1]=1;for (i=2;i<=k;i++) fac[i]=(fac[i-1]*i)%MOD;
	for (i=1;i<=min(n,k);i++)
		ans=(ans+(((C(n,i)*s[k][i])%MOD*fac[i])%MOD*quick_pow(2,n-i))%MOD)%MOD;
	printf("%lld\n",ans);
	return 0;
}
