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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
  
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
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

int n,r;
double p[1048];int d[1048];
double pw[1048][1048];
double dp[1048][1048];

int main ()
{
	int ca=getint(),i,j;
	while (ca--)
	{
		n=getint();r=getint();
		for (i=1;i<=n;i++) scanf("%lf%d",&p[i],&d[i]);
		for (i=1;i<=n;i++)
		{
			pw[i][0]=1;
			for (j=1;j<=r;j++) pw[i][j]=pw[i][j-1]*(1-p[i]);
		}
		for (i=0;i<=n;i++)
			for (j=0;j<=r;j++)
				dp[i][j]=0;
		dp[0][r]=1;double ans=0;
		for (i=0;i<=n-1;i++)
			for (j=0;j<=r;j++)
				if (dp[i][j]>eps)
				{
					dp[i+1][j]+=dp[i][j]*pw[i+1][j];
					if (j) dp[i+1][j-1]+=dp[i][j]*(1-pw[i+1][j]),ans+=dp[i][j]*(1-pw[i+1][j])*d[i+1];
				}
		printf("%.10lf\n",ans);
	}
	return 0;
}
