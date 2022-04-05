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
 
const int MOD=998244353;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
 
inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,k;
vector<int> v[100048];

struct Edge
{
	int x,y;
	int len;
}edge[100048];

int ans=0;

int sum[100048],fa[100048],faind[100048];

inline int Get(int ind,int cur)
{
	if (edge[ind].x==cur) return edge[ind].y; else return edge[ind].x;
}

inline void dfs(int cur,int father)
{
	int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=Get(v[cur][i],cur);
		if (y!=father)
		{
			sum[y]=sum[cur]+edge[v[cur][i]].len;
			fa[y]=cur;faind[y]=v[cur][i];
			dfs(y,cur);
		}
	}
}

inline int find_dia()
{
	sum[1]=0;fa[1]=-1;dfs(1,-1);
	int maxn=-INF,maxpos,i;
	for (i=1;i<=n;i++)
		if (sum[i]>maxn)
		{
			maxn=sum[i];
			maxpos=i;
		}
	sum[maxpos]=0;fa[maxpos]=-1;dfs(maxpos,-1);
	maxn=-INF;
	for (i=1;i<=n;i++)
		if (sum[i]>maxn)
		{
			maxn=sum[i];
			maxpos=i;
		}
	return maxpos;
}

inline void update(int cur)
{
	while (fa[cur]!=-1)
	{
		edge[faind[cur]].len=-1;
		cur=fa[cur];
	}
}

int res=0,dp[100048];
inline void Dfs(int cur,int father)
{
	int i,y;dp[cur]=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=Get(v[cur][i],cur);
		if (y!=father)
		{
			Dfs(y,cur);
			res=max(res,dp[y]+edge[v[cur][i]].len+dp[cur]);
			dp[cur]=max(dp[cur],dp[y]+edge[v[cur][i]].len);
		}
	}
}

int main ()
{
	int i,x,y,ans=0;
	n=getint();k=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(i);v[y].pb(i);
		edge[i]=Edge{x,y,1};
	}
	int ed=find_dia();
	ans+=sum[ed];
	if (k==1) {printf("%d\n",(n-1)*2-ans+1);return 0;}
	update(ed);
	Dfs(1,-1);ans+=res;
	printf("%d\n",(n-1)*2-ans+2);
	return 0;
}
