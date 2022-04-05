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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL a,b;int k;

inline int gcd(int x,int y) {return (!y)?x:gcd(y,x%y);}
inline int lcm(int x,int y) {return x/gcd(x,y)*y;}

int dp[500048],dp2[500048];

int target;
inline int solve(int cur,int target)
{
	if (dp[cur]!=-1) return dp[cur];
	if (cur==target) {dp[cur]=0;return 0;}
	dp[cur]=INF;dp[cur]=min(dp[cur],solve(cur-1,target)+1);
	for (register int i=2;i<=k;i++) if (cur%i && cur-cur%i>=target) dp[cur]=min(dp[cur],solve(cur-cur%i,target)+1);
	return dp[cur];
}

int main ()
{
	int i;
	a=getLL();b=getLL();k=getint();
	LL Lcm=1;
	for (i=2;i<=k;i++) Lcm=lcm(Lcm,i);
	LL ans=0,ulim,dlim;
	dlim=(b%Lcm==0?b:(b/Lcm+1)*Lcm);
	ulim=a/Lcm*Lcm;
	if (dlim<=a)
	{
		memset(dp,-1,sizeof(dp));ans=(ulim-dlim)/Lcm*solve(Lcm,0);
		memset(dp,-1,sizeof(dp));ans+=(b%Lcm==0?0:solve(Lcm,b%Lcm));
		memset(dp,-1,sizeof(dp));ans+=solve(a%Lcm,0);
	}
	else
	{
		memset(dp,-1,sizeof(dp));
		ans=solve(a%Lcm,b%Lcm);
	}
	printf("%lld\n",ans);
	return 0;
}
