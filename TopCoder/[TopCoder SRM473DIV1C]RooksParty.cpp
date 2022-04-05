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

const int MOD=1e9+9;
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

struct RooksParty
{
	LL dp[15][48][48],DP[15][48][48];
	LL c[1048][1048];
	inline void init_c()
	{
		c[0][0]=1;int i,j;
		for (i=1;i<=1000;i++)
		{
			c[i][0]=c[i][i]=1;
			for (j=1;j<=i-1;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
		}
	}
	inline LL C(int x,int y)
	{
		if (x<y) return 0;
		return c[x][y];
	}
	inline int countArrangements(int n,int m,vector<int> color)
	{
		int i,curn,curm,ton,tom;
		init_c();int cc=int(color.size());
		memset(dp,0,sizeof(dp));memset(DP,0,sizeof(DP));
		dp[0][n][m]=1;
		for (i=1;i<=cc;i++)
			for (curn=1;curn<=n;curn++)
				for (curm=1;curm<=m;curm++)
				{
					DP[i][curn][curm]=C(curn*curm,color[i-1]);
					for (ton=1;ton<=curn;ton++)
						for (tom=1;tom<=curm;tom++)
						{
							if (ton==curn && tom==curm) continue;
							DP[i][curn][curm]=((DP[i][curn][curm]-(DP[i][ton][tom]*C(curn,ton)%MOD*C(curm,tom))%MOD)%MOD+MOD)%MOD;
						}
				}
		for (i=0;i<=cc-1;i++)
			for (curn=1;curn<=n;curn++)
				for (curm=1;curm<=m;curm++)
					if (dp[i][curn][curm])
					{
						for (ton=1;ton<=curn;ton++)
							for (tom=1;tom<=curm;tom++)
								dp[i+1][curn-ton][curm-tom]=((dp[i+1][curn-ton][curm-tom]+(((dp[i][curn][curm]*C(curn,ton))%MOD*C(curm,tom))%MOD)*DP[i+1][ton][tom]))%MOD;
					}
		LL res=0;
		for (curn=0;curn<=n;curn++)
			for (curm=0;curm<=m;curm++)
				res=(res+dp[cc][curn][curm])%MOD;
		return int(res);
	}
};

/*---Debug Part---*/
/*
int main ()
{
	RooksParty A;
	int nn,mm,cc;
	while (scanf("%d%d%d",&nn,&mm,&cc)!=EOF)
	{
		vector<int> v;int x;
		for (int i=1;i<=cc;i++) x=getint(),v.pb(x);
		cout<<A.countArrangements(nn,mm,v);
	}
	return 0;
}
*/
