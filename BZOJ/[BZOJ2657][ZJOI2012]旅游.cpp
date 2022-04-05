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

const int MOD=1e9+9;
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
map<Pair,int> m;
vector<int> v[200048];

int dp[200048][2];

inline void addedge(int U,int V,int ind)
{
	if (U>V) swap(U,V);int res=m[mp(U,V)];
	if (res) v[res].pb(ind),v[ind].pb(res); else m[mp(U,V)]=ind;
}

inline void dfs(int cur,int father)
{
	int i,y;
	if (int(v[cur].size())==1 && father)
	{
		dp[cur][0]=dp[cur][1]=1;
		return;
	}
	int fm=0,sm=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			dfs(y,cur);
			dp[cur][0]=max(dp[cur][0],dp[y][0]+1);
			if (dp[y][0]>=fm)
			{
				sm=fm;
				fm=dp[y][0];
			}
			else if (dp[y][0]>sm) sm=dp[y][0];
		}
	}
	dp[cur][1]=fm+sm+1;
}
int main ()
{
	int i,x,y,z;
	n=getint();
	for (i=1;i<=n-2;i++)
	{
		x=getint();y=getint();z=getint();
		addedge(x,y,i);addedge(x,z,i);addedge(y,z,i);
	}
	dfs(1,0);
	int ans=0;for (i=1;i<=n-2;i++) ans=max(ans,dp[i][1]);
	printf("%d\n",ans);
	return 0;
}
