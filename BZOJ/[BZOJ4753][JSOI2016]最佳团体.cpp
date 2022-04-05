#include <cassert>
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
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,k;
vector<int> v[2548];
double a[2548],b[2548];
int seq[2548],ind=0;
double dp[2548][2548];
int sz[2548];
double l,r,mid;

inline void dfs(int cur)
{
	int i,y;sz[cur]=1;seq[++ind]=cur;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];dfs(y);
		sz[cur]+=sz[y];
	}
}

inline bool check()
{
	int i,j;
	for (i=1;i<=n+2;i++)
		for (j=0;j<=k;j++)
			dp[i][j]=-INF;
	for (i=1;i<=n+2;i++) dp[i][0]=0;
	for (i=n+1;i>=1;i--)
		for (j=1;j<=min(k,n+2-i);j++)
			if (i+sz[seq[i]]<=n+1)
				dp[i][j]=max(dp[i+1][j-1]+a[seq[i]]-b[seq[i]]*mid,dp[i+sz[seq[i]]][j]);
			else
				dp[i][j]=dp[i+1][j-1]+a[seq[i]]-b[seq[i]]*mid;
	return dp[1][k]>=0;
}

int main ()
{
	int i,x;
	k=getint();n=getint();k++;
	for (i=1;i<=n;i++)
	{
		b[i]=getint();a[i]=getint();
		x=getint();v[x].pb(i);
	}
	dfs(0);
	l=0;r=1e4;double ans=0;
	while (r-l>1e-5)
	{
		mid=(l+r)/2;
		if (check()) ans=mid,l=mid; else r=mid;
	}
	printf("%.3lf\n",ans);
	return 0;
}
