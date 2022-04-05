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

int n,m;
int a[48][48];
LL dp[18][18][10048];

int main ()
{
	int ca,tt=0,i,j,Mask,plug1,plug2;ca=getint();
	while (ca--)
	{
		n=getint();m=getint();
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				a[i][j]=getint();
		memset(dp,0,sizeof(dp));
		dp[1][0][0]=1;
		for (i=1;i<=n;i++)
		{
			for (j=1;j<=m;j++)
				for (Mask=0;Mask<=(1<<(m+1))-1;Mask++)
				{
					plug1=(Mask&(1<<(j-1)));plug2=(Mask&(1<<j));
					if (a[i][j])
					{
						dp[i][j][Mask]+=dp[i][j-1][Mask^(1<<(j-1))^(1<<j)];
						if ((plug1 && plug2) || (!plug1 && !plug2)) continue;
						dp[i][j][Mask]+=dp[i][j-1][Mask];
					}
					else
					{
						if (!plug1 && !plug2) dp[i][j][Mask]=dp[i][j-1][Mask]; else dp[i][j][Mask]=0;
					}
				}
			for (Mask=0;Mask<=(1<<m)-1;Mask++)
				dp[i+1][0][Mask<<1]+=dp[i][m][Mask];
		}
		printf("Case %d: There are %lld ways to eat the trees.\n",++tt,dp[n][m][0]);
	}
	return 0;
}
