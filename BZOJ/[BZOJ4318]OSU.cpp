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

int n;double p[100048];
double ans,dp[100048],dp2[100048];

inline double tri(double x) {return x*x*x;}

int main ()
{
	int i;
	n=getint();for (i=1;i<=n;i++) scanf("%lf",&p[i]);
	dp[0]=0;dp2[0]=0;ans=0;
	for (i=1;i<=n;i++)
	{
		dp[i]=(dp[i-1]+1)*p[i];
		dp2[i]=(dp2[i-1]+2*dp[i-1]+1)*p[i];
		ans+=(3*dp2[i-1]+3*dp[i-1]+1)*p[i];
	}
	printf("%.1lf\n",ans);
	return 0;
}

