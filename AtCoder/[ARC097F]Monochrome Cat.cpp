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
#define pii pair<double,double>
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
vector<int> v[100048];int col[100048],d[100048],need[100048];
//0: leaf reachable; 1: leaf unreachable
int dp[100048][2],dp2[100048];
char s[100048];
int haswhite[100048];
int ans,maxminus=0;
int cnt=0;

inline void dfs(int cur,int father)
{
	haswhite[cur]=col[cur];
	int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			dfs(y,cur);
			if (haswhite[y]) haswhite[cur]=1;
		}
	}
}

inline void solve(int cur,int father)
{
	int i,y;bool isleaf=true;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father && haswhite[y])
		{
			isleaf=false;
			solve(y,cur);
		}
	}
	if (isleaf)
	{
		dp[cur][0]=1+(need[cur]==1?1:-1);
		dp[cur][1]=-INF;
		dp2[cur]=dp[cur][0];
		if (cnt>1) maxminus=max(maxminus,dp2[cur]);
		return;
	}
	dp[cur][0]=-INF;dp[cur][1]=dp2[cur]=1+(need[cur]==1?1:-1);
	int nmax=-INF,ymax=-INF;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father && haswhite[y])
		{
			dp[cur][0]=max(dp[cur][0],dp[y][0]+1+(need[cur]==1?1:-1));
			dp[cur][1]=max(dp[cur][1],dp[y][1]+1+(need[cur]==1?1:-1));
			dp2[cur]=max(dp2[cur],nmax+max(dp[y][0],dp[y][1])+1+(need[cur]==1?1:-1));
			dp2[cur]=max(dp2[cur],ymax+dp[y][1]+1+(need[cur]==1?1:-1));
			nmax=max(nmax,dp[y][1]);ymax=max(ymax,dp[y][0]);
		}
	}
	maxminus=max(maxminus,dp2[cur]);
	maxminus=max(maxminus,max(dp[cur][0],dp[cur][1]));
}

int main ()
{
	int i,j,x,y;
	n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	scanf("%s",s+1);
	int root=-1;
	for (i=1;i<=n;i++) {col[i]=(s[i]=='W');if (col[i] && root==-1) root=i;}
	if (root==-1)
	{
		printf("0\n");
		return 0;
	}
	dfs(root,-1);ans=0;
	for (i=1;i<=n;i++)
		if (haswhite[i])
			for (j=0;j<int(v[i].size());j++)
				if (haswhite[v[i][j]]) ans++,d[i]++;
	for (i=1;i<=n;i++) if (haswhite[i]) cnt++,need[i]=(d[i]%2)^col[i],ans+=need[i];
	solve(root,-1);
	printf("%d\n",ans-maxminus);
	return 0;
}
