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
const int INF=1e9;
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

int n,k,m;
LL dp[348][348],sum[348][348],c[348][348];

int main ()
{
	int i,j,p;
	n=getint();k=getint();m=getint();
	c[0][0]=1;
	for (i=1;i<=n;i++)
	{
		c[i][0]=c[i][i]=1;
		for (j=1;j<=i-1;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%m;
	}
	for (i=0;i<=k;i++) dp[1][i]=1,sum[1][i]=k-i+1;
	for (i=2;i<=n+1;i++)
		for (j=k;j>=0;j--)
		{
			dp[i][j]=0;
			for (p=1;p<=i-1;p++)
				dp[i][j]=(dp[i][j]+((dp[i-p][j]*sum[p][j+1])%m*c[i-2][p-1])%m)%m;
			sum[i][j]=(sum[i][j+1]+dp[i][j])%m;
		}
	printf("%lld\n",dp[n+1][0]);
	return 0;
}
