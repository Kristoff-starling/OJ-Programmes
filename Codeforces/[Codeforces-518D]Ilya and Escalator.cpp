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

const int MOD=1e9;
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

int n,t;double p;
double dp[2048][2048];

int main ()
{
	n=getint();scanf("%lf",&p);t=getint();
	memset(dp,0,sizeof(dp));dp[0][0]=1;
	int i,j;
	for (i=0;i<=t-1;i++)
		for (j=0;j<=n;j++)
			if (dp[i][j]>eps)
			{
				if (j!=n) dp[i+1][j+1]+=dp[i][j]*p,dp[i+1][j]+=dp[i][j]*(1.0-p);
				else dp[i+1][j]+=dp[i][j];
			}
	double ans=0;
	for (i=0;i<=n;i++) ans=ans+dp[t][i]*i;
	printf("%.6lf",ans);
	return 0;
}
