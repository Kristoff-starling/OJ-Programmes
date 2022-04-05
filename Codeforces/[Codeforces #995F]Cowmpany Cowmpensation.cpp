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

inline LL mod(LL x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

vector<int> v[3048];
LL dp[3048][3048];
LL DP[3048];
LL c[3048][3048];

int n,d;

inline void dfs(int cur)
{
	int i,j,y;
	if (int(v[cur].size())==0)
	{
		for (i=1;i<=n;i++) dp[cur][i]=i;
		return;
	}
	for (i=0;i<int(v[cur].size());i++) dfs(v[cur][i]);
	for (i=1;i<=n;i++)
	{
		dp[cur][i]=1;
		for (j=0;j<int(v[cur].size());j++)
			dp[cur][i]=(dp[cur][i]*dp[v[cur][j]][i])%MOD;
		dp[cur][i]=mod(dp[cur][i]+dp[cur][i-1]);
	}
}


LL inv[3048],finv[3048];
inline void init_inv()
{
	inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (register int i=2;i<=n;i++)
	{
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
}

inline void init_c()
{
	int i,j;
	c[0][0]=1;
	for (i=1;i<=n;i++)
	{
		c[i][0]=c[i][i]=1;
		for (j=1;j<=i-1;j++)
			c[i][j]=mod(c[i-1][j-1]+c[i-1][j]);
	}
}

inline LL C(int x,int y)
{
	LL res=1;
	for (register int i=x;i>=x-y+1;i--) res=(res*i)%MOD;
	res=(res*finv[y])%MOD;
	return res;
}

int main ()
{
	int i,j,x,y;n=getint();d=getint();
	for (i=2;i<=n;i++) x=getint(),v[x].pb(i);
	init_inv();init_c();
	dfs(1);
	DP[1]=1;
	for (i=2;i<=n;i++)
	{
		DP[i]=dp[1][i];
		for (j=1;j<=i-1;j++)
			DP[i]=mod(DP[i]-(DP[j]*c[i][j])%MOD);
	}
	LL ans=0;
	for (i=1;i<=min(d,n);i++) ans=mod(ans+(DP[i]*C(d,i))%MOD);
	printf("%lld\n",ans);
	return 0;
}
