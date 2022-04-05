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

int n,K;
vector<int> v[100048];

int dp[100048][10],tmp[100048][10];

inline void dfs(int cur,int father)
{
	int i,j,k,y,cc=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father) dfs(y,cur);
	}
	for (i=0;i<=K*2;i++) tmp[cc][i]=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			cc++;
			for (j=0;j<=K*2;j++) tmp[cc][j]=INF;
			for (j=0;j<=K*2;j++)
				for (k=0;k<=j;k++)
					tmp[cc][j]=min(tmp[cc][j],tmp[cc-1][j-k]+dp[y][k]+((k&1)?1:2));
		}
	}
	for (i=0;i<=K*2;i++) dp[cur][i]=tmp[cc][i];
}

int main ()
{
	int i,x,y;
	n=getint();K=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	dfs(1,-1);
	printf("%d\n",dp[1][K*2]+K);
	return 0;
}
