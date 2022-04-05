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
vector<Pair> v[100048];
int dp[100048];

inline void dfs(int cur)
{
	if (int(v[cur].size())==0)
	{
		dp[cur]=INF;
		return;
	}
	int i,y;
	dp[cur]=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		dfs(y);
		dp[cur]+=min(v[cur][i].y,dp[y]);
	}
}

int main ()
{
	int i,fa,c;n=getint();
	for (i=2;i<=n;i++)
	{
		fa=getint();c=getint();
		v[fa].pb(mp(i,c));
	}
	dfs(1);
	printf("%d",dp[1]);puts(".00");
	return 0;
}
