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

int n;
vector<Pair> v[200048];
int upnum[200048],downnum[200048];
int dp[200048];vector<int> trans[200048];

inline void dfs(int cur,int father)
{
	int i,y;upnum[cur]=downnum[cur]=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			dfs(y,cur);
			upnum[cur]+=upnum[y];downnum[cur]+=downnum[y];
			if (v[cur][i].y) downnum[cur]++; else upnum[cur]++;
		}
	}
}

inline void Dfs(int cur,int father)
{
	dp[cur]=upnum[cur];trans[cur].pb(0);
	int i,y,Up=0,Down=0,uu,dd,curu,curd;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			Dfs(y,cur);
			if (v[cur][i].y) Down++; else Up++;
		}
	}
	uu=upnum[cur]-Up;dd=downnum[cur]-Down;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			curu=uu-upnum[y];
			if (v[cur][i].y) curu+=Up; else curu+=Up-1;
			if (v[cur][i].y) curu++;
			if (dp[y]+curu<dp[cur])
			{
				dp[cur]=dp[y]+curu;
				trans[cur].clear();trans[cur].pb(y);
			}
			else if (dp[y]+curu==dp[cur])
				trans[cur].pb(y);
		}
	}
}

vector<int> anslist;
inline void getans(int cur)
{
	int i;
	for (i=0;i<int(trans[cur].size());i++)
		if (!trans[cur][i]) anslist.pb(cur); else getans(trans[cur][i]);
}
	
int main ()
{
	int i,x,y;
	n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(mp(y,1));v[y].pb(mp(x,0));
	}
	dfs(1,-1);Dfs(1,-1);
	printf("%d\n",dp[1]);
	getans(1);sort(anslist.begin(),anslist.end());
	for (i=0;i<int(anslist.size());i++) printf("%d ",anslist[i]);puts("");
	return 0;
}
