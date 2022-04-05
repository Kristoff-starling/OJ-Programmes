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
const LL LINF=2e17;
const int INF=1e9;
const int magic=348;
const long double eps=1e-15;
const double pi=3.14159265;
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int p[1048],n;
int dp[1048],son[1048][5048];
int head[100048],nxt[200048],to[200048],tot=1;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
}

inline void dfs(int cur)
{
	int i,j,y,cc=0;
	for (i=head[cur];i;i=nxt[i]) dfs(to[i]);
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];cc++;
		for (j=0;j<=5000;j++) son[cc][j]=INF;
		for (j=0;j<=5000;j++)
		{
			if (j>=p[y]) son[cc][j]=min(son[cc][j],son[cc-1][j-p[y]]+dp[y]);
			if (j>=dp[y]) son[cc][j]=min(son[cc][j],son[cc-1][j-dp[y]]+p[y]);
		}
	}
	dp[cur]=INF;
	for (i=0;i<=p[cur];i++) dp[cur]=min(dp[cur],son[cc][i]);
}

int main ()
{
	int i,x;n=getint();
	for (i=2;i<=n;i++) x=getint(),addedge(x,i);
	for (i=1;i<=n;i++) p[i]=getint();
	dfs(1);
	if (dp[1]<INF) printf("POSSIBLE\n"); else printf("IMPOSSIBLE\n");
	return 0;
}
