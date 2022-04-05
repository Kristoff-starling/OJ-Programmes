#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
int a[4248][4248];
LL dp[4248][4248];
const int BASE=2008;
LL fac[100048],inv[100048],finv[100048];

inline void init_inv()
{
	fac[0]=fac[1]=1;inv[0]=inv[1]=1;finv[0]=finv[1]=1;
	for (register int i=2;i<=100000;i++)
	{
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		fac[i]=(fac[i-1]*i)%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
}

inline LL C(int x,int y)
{
	if (x<y) return 0ll;
	return ((fac[x]*finv[y])%MOD*finv[x-y])%MOD;
}

int main ()
{
	int i,j,x,y;
	init_inv();
	n=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();y=getint();
		a[BASE+x][BASE+y]++;
		a[BASE-x][BASE-y]++;
	}
	for (i=1;i<=BASE;i++)
		for (j=1;j<=BASE;j++)
			dp[i][j]=a[i][j];
	for (i=1;i<=BASE*2;i++)
		for (j=1;j<=BASE*2;j++)
			dp[i][j]=(dp[i][j]+dp[i-1][j]+dp[i][j-1])%MOD;
	LL ans=0;
	for (i=BASE+1;i<=BASE*2;i++)
		for (j=BASE+1;j<=BASE*2;j++)
			ans=(ans+(dp[i][j]*a[i][j])%MOD)%MOD;
	for (i=BASE+1;i<=BASE*2;i++)
		for (j=BASE+1;j<=BASE*2;j++)
			ans=((ans-((long long)a[i][j]*C((i-BASE+j-BASE)*2,j-BASE+j-BASE))%MOD)%MOD+MOD)%MOD;
	ans=(ans*finv[2])%MOD;
	printf("%lld\n",ans);
	return 0;
}
