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

int n;
int dp[30000048];
int lim;

int main ()
{
	n=getint();int i,j,d;
	lim=1;
	while ((1<<lim)-1<=n) lim++;lim--;
	dp[0]=1;
	for (i=1;i<=lim;i++)
	{
		d=(1<<i)-1;
		for (j=0;j<=n-d;j++) dp[j+d]+=dp[j],dp[j+d]=(dp[j+d]>=MOD?dp[j+d]-MOD:dp[j+d]);
	}
	printf("%lld\n",dp[n]);
	return 0;
}
