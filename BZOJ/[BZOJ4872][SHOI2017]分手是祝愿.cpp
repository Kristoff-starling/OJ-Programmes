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

const int MOD=100003;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,k;
int status[100048];
int need[100048];

vector<int> b[100048];int Res[100048];

int sum=0;
LL dp[100048];

LL inv[100048];
void init_inv()
{
	int i;inv[1]=1;
	for (i=2;i<=n;i++)
		inv[i]=MOD-((MOD/i)*inv[MOD%i])%MOD;
}

LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1)
		{
			res=(res*x)%MOD;
			y--;
		}
		x=(x*x)%MOD;
		y>>=1;
	}
	return res;
}

int main ()
{
	int i,j,curres;
	n=getint();k=getint();
	for (i=1;i<=n;i++) status[i]=getint();
	for (i=1;i<=n;i++)
	{
		for (j=i;j<=n;j+=i)
			b[i].pb(j);
		Res[i]=(status[i]==0?0:1);
	}
	for (i=n;i>=1;i--)
	{
		curres=Res[i];
		for (j=0;j<int(b[i].size());j++)
			if (b[i][j]>i) curres^=need[b[i][j]];
		need[i]=curres;
	}
	for (i=1;i<=n;i++) sum+=need[i];
		memset(dp,0,sizeof(dp));
	init_inv();LL ans=0;
	for (i=n;i>k;i--)
		dp[i]=((((long long)dp[i+1]*(n-i))%MOD+n)%MOD*inv[i])%MOD;
	for (i=sum;i>k;i--) ans=(ans+dp[i])%MOD;
	if (k>sum) ans=(ans+sum)%MOD; else ans=(ans+k)%MOD;
	for (i=1;i<=n;i++) ans=(ans*i)%MOD;
	printf("%lld\n",ans);
	return 0;
}
