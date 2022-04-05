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

int n;
char s[300048];
double ans,dp[300048];

int main ()
{
	int i;
	n=getint();scanf("%s",s+1);
	dp[0]=0;ans=0;
	for (i=1;i<=n;i++)
		if (s[i]=='o')
		{
			dp[i]=dp[i-1]+1;
			ans+=2*dp[i-1]+1;
		}
		else if (s[i]=='?')
		{
			dp[i]=(dp[i-1]+1)*0.5;
			ans+=dp[i-1]+0.5;
		}
		else
			dp[i]=0;
	printf("%.4lf\n",ans);
	return 0;
}
