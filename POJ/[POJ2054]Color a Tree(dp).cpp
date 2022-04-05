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

int n,root;
int dp[1048][1048];
int sz[1048];
vector<int> v[1048];
int val[1048];
int clist[1048],ctot,tmp[1048],tot;
int DP[1048][1048],pre[1048][1048];

inline bool cmp(int x,int y) {return sz[x]<sz[y];}

inline void Dfs(int cur)
{
	sz[cur]=1;int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		Dfs(y);sz[cur]+=sz[y];
	}
	sort(v[cur].begin(),v[cur].end(),cmp);
}

inline void merge(int cur)
{
	int N=ctot,M=sz[cur],i,j;
	DP[N+1][M+1]=0;
	for (i=N+1;i>=1;i--)
		for (j=M+1;j>=1;j--)
		{
			if (i==N+1 && j==M+1) continue;
			DP[i][j]=INF;
			if (i!=N+1) DP[i][j]=min(DP[i][j],val[clist[i]]*(i+j-1)+DP[i+1][j]),pre[i][j]=1;
			if (j!=M+1)
				if (DP[i][j]>val[dp[cur][j]]*(i+j-1)+DP[i][j+1])
				{
					DP[i][j]=val[dp[cur][j]]*(i+j-1)+DP[i][j+1];
					pre[i][j]=2;
				}
		}
	tot=0;int pt1=1,pt2=1;
	while (pt1<=N || pt2<=M)
	{
		if (pre[pt1][pt2]==1) tmp[++tot]=clist[pt1++]; else tmp[++tot]=dp[cur][pt2++];
	}
	ctot=tot;
	for (i=1;i<=ctot;i++) clist[i]=tmp[i];
}

inline void dfs(int cur)
{
	int i,y;
	dp[cur][1]=cur;
	if (int(v[cur].size())==0) return;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		dfs(y);
	}
	for (i=1;i<=sz[v[cur][0]];i++) clist[i]=dp[v[cur][0]][i];
	ctot=sz[v[cur][0]];
	for (i=1;i<int(v[cur].size());i++) merge(v[cur][i]);
	for (i=1;i<=ctot;i++) dp[cur][i+1]=clist[i];
}

int main ()
{
	int i,x,y;
	while (scanf("%d%d",&n,&root) && n && root)
	{
		for (i=1;i<=n;i++) val[i]=getint(),v[i].clear();
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();
			v[x].pb(y);
		}
		Dfs(root);dfs(root);
		int ans=0,t=0;
		for (i=1;i<=n;i++) ans+=val[dp[root][i]]*(++t);
		printf("%d\n",ans);
	}
	return 0;
}
