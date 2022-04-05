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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL dp[6048][6048];
LL L[6048];
int k,n,mod;LL fac;

LL quick_pow(LL x,LL y)
{
	LL res=1;x%=mod;
	while (y)
	{
		if (y&1)
		{
			res=(res*x)%mod;
			y--;
		}
		x=(x*x)%mod;
		y>>=1;
	}
	return res;
}

int main ()
{
	int i,j;
	k=getint();n=getint();mod=getint();
	for (i=0;i<=n*3;i++)
		for (j=0;j<=n;j++)
			dp[i][j]=(i>=j?1:0);
	for (i=1;i<=n*3;i++)
		for (j=1;j<=min(i,n);j++)
			dp[i][j]=(dp[i-1][j]+(dp[i-1][j-1]*i)%mod)%mod;
	fac=1ll;for (i=1;i<=n;i++) fac=(fac*i)%mod;
	if (k<=n*3) {printf("%lld\n",(dp[k][n]*fac)%mod);return 0;}
	LL ans=0;
	for (i=n;i<=n*3;i++)
	{
		L[i]=1;
		for (j=n;j<=n*3;j++) if (i!=j) L[i]=(L[i]*(i+mod-j))%mod;
		L[i]=quick_pow(L[i],mod-2);
		for (j=n;j<=n*3;j++) if (i!=j) L[i]=(L[i]*(k-j))%mod;
		ans=(ans+(L[i]*dp[i][n])%mod)%mod;
	}
	printf("%lld\n",(ans*fac)%mod);
	return 0;
}
		
