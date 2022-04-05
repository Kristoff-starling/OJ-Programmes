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

const int MOD=123456789;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-8;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int p,t,N,m;
vector<int> v[48];
int dp[1048][101];

inline int mod(int x) {while (x>=p) x-=p;while (x<0) x+=p;return x;}

inline bool check(int j,int Mask)
{
	int i;
	for (i=0;i<int(v[j].size());i++)
		if (Mask&(1<<(v[j][i]-1))) return false;
	return true;
}

inline int solve(int Mask,int n)
{
	if (n==1) return 1;
	if (dp[Mask][n]!=-1) return dp[Mask][n];
	dp[Mask][n]=0;int i,j;
	for (i=1;i<=n-1;i++)
		for (j=1;j<=N;j++)
			if (check(j,Mask))
				dp[Mask][n]=mod(dp[Mask][n]+(solve(Mask|(1<<(j-1)),i)*solve(Mask,n-i))%p);
	return dp[Mask][n];
}

int main ()
{
	int i,x,y;
	p=getint();t=getint();t/=2;N=getint();m=getint();
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();
		v[y].pb(x);
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",solve(0,t+1));
	return 0;
}
