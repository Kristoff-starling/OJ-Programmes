#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#define LL long long
#define LB long double
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	int res;char ch;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	LL res;char ch;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,e;
vector<int> v[1048];
int dist[1048][1048],pre[1048][1048];
double dp[1048][1048];

int q[100048],head,tail;
inline void bfs(int starter)
{
	head=tail=1;q[1]=starter;
	int i,x,y;for (i=1;i<=n;i++) dist[starter][i]=INF;
	dist[starter][starter]=0;
	while (head<=tail)
	{
		x=q[head++];
		for (i=0;i<int(v[x].size());i++)
		{
			y=v[x][i];
			if (dist[starter][x]+1<dist[starter][y])
			{
				dist[starter][y]=dist[starter][x]+1;
				q[++tail]=y;pre[starter][y]=x;
			}
			else if (dist[starter][x]+1==dist[starter][y])
				pre[starter][y]=min(pre[starter][y],x);
		}
	}
}

inline double solve(int st,int ed)
{
	if (dp[st][ed]!=-1) return dp[st][ed];
	if (st==ed) {dp[st][ed]=0;return 0;}
	if (dist[ed][st]<=2) {dp[st][ed]=1;return 1;}
	int to=pre[ed][pre[ed][st]];dp[st][ed]=0;
	int deg=int(v[ed].size())+1,i,y;
	for (i=0;i<int(v[ed].size());i++)
	{
		y=v[ed][i];
		dp[st][ed]+=double(solve(to,y)+1)*1.0/deg;
	}
	dp[st][ed]+=double(solve(to,ed)+1)*1.0/deg;
	return dp[st][ed];
}

int main ()
{
	int i,j,x,y,st,ed;n=getint();e=getint();st=getint();ed=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	for (i=1;i<=n;i++) sort(v[i].begin(),v[i].end());
	for (i=1;i<=n;i++) bfs(i);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			dp[i][j]=-1;
	printf("%.3lf\n",solve(st,ed));
}
