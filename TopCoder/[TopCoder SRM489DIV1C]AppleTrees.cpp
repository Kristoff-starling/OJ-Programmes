#include <cassert>
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

int d,n,r[48];
LL dp[48][48][2048];

class AppleTrees
{
	LL inv[200048],finv[200048],fac[200048];
	inline void init_inv()
	{
		int i;inv[0]=inv[1]=finv[0]=finv[1]=fac[0]=fac[1]=1;
		for (i=2;i<=d;i++)
			inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD,finv[i]=(finv[i-1]*inv[i])%MOD,fac[i]=(fac[i-1]*i)%MOD;
	}
	inline LL C(int x,int y)
	{
		if (x<y) return 0;
		return ((fac[x]*finv[y])%MOD*finv[x-y])%MOD;
	}
	inline void clear()
	{
		memset(dp,0,sizeof(dp));
	}
	public:
		inline int theCount(int D,vector<int> info)
		{
			d=D;n=int(info.size());int i,j,k;clear();
			for (i=0;i<=n-1;i++) r[i+1]=info[i];
			sort(r+1,r+n+1);init_inv();
			dp[1][0][0]=1;
			for (i=1;i<=n-1;i++)
				for (j=0;j<=i-1;j++)
					for (k=0;k<=n*40;k++)
						if (dp[i][j][k])
						{
							dp[i+1][j+1][k]=(dp[i+1][j+1][k]+(dp[i][j][k]*(j+2))%MOD)%MOD;
							dp[i+1][j][k+r[i+1]]=(dp[i+1][j][k+r[i+1]]+(dp[i][j][k]*(j*2+2)%MOD))%MOD;
							if (j) dp[i+1][j-1][k+r[i+1]+r[i+1]]=(dp[i+1][j-1][k+r[i+1]+r[i+1]]+dp[i][j][k]*j%MOD)%MOD;
						}
			LL ans=0;
			for (k=0;k<=min(D-1,n*40);k++)
				ans=(ans+(C(D-k-1+n,n)*dp[n][0][k])%MOD)%MOD;
			return int(ans);
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int dd,nn;
	AppleTree A;
	while (scanf("%d%d",&dd,&nn)!=EOF)
	{
		vector<int> rr;int x;
		for (register int i=1;i<=nn;i++) x=getint(),rr.pb(x);
		printf("%d\n",A.theCount(dd,rr));
	}
	return 0;
}
*/
/*
100000 8
{21, 37, 23, 13, 32, 22, 9, 39}
*/
