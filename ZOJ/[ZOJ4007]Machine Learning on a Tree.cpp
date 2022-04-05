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
int w[100048];
int dp[100048][2];

int head[100048],to[200048],nxt[200048],tot;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

inline void Clear()
{
	tot=1;memset(head,0,sizeof(head));
	for (register int i=1;i<=n;i++) dp[i][0]=dp[i][1]=INF;
}

inline void dfs(int cur,int father)
{
	int i,y;
	if (w[cur]!=1) dp[cur][0]=0;if (w[cur]!=0) dp[cur][1]=0;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father) 
		{
			dfs(y,cur);
			if (w[cur]!=1) dp[cur][0]+=min(dp[y][0],dp[y][1]+1);
			if (w[cur]!=0) dp[cur][1]+=min(dp[y][1],dp[y][0]+1);
		}
	}
}

int main ()
{
	int ca,i,x,y;ca=getint();
	while (ca--)
	{
		n=getint();Clear();
		for (i=1;i<=n;i++) w[i]=getint();
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();
			addedge(x,y);
		}
		dfs(1,-1);
		printf("%d\n",min(dp[1][0],dp[1][1]));
	}
	return 0;
}
