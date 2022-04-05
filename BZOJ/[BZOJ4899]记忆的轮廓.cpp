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

int n,m,k;
double dp[2048];
vector<int> v[2048];
double sum[2048][2048];
double prefix[2048];
int d[2048];

inline void Clear()
{
	for (register int i=1;i<=m;i++) v[i].clear(),dp[i]=0;
	memset(sum,0,sizeof(sum));
}

inline void dfs(int cur)
{
	int i,y;
	if (!d[cur]) {dp[cur]=1;return;}
	dp[cur]=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];dfs(y);
		if (y>n) dp[cur]+=(dp[y]+1)/d[cur];
	}
}

double DP[2048],tmp[2048];

inline void solve(int hl,int hr,int cl,int cr)
{
	if (hl>hr || cl>cr) return;
	int mid=(hl+hr)>>1,i,minpos=1;
	for (i=cl;i<=min(mid-1,cr);i++)
		if (tmp[mid]>DP[i]+sum[i][mid])
		{
			tmp[mid]=DP[i]+sum[i][mid];
			minpos=i;
		}
	solve(hl,mid-1,cl,minpos);
	solve(mid+1,hr,minpos,cr);
}			

int main ()
{
	int ca,i,j,sta,x,y;ca=getint();
	while (ca--)
	{
		n=getint();m=getint();k=getint();Clear();
		for (i=1;i<=n-1;i++) v[i].pb(i+1);
		for (i=1;i<=m-n;i++)
		{
			x=getint();y=getint();
			v[x].pb(y);
		}
		for (i=1;i<=m;i++) d[i]=int(v[i].size());
		dfs(1);
		for (i=1;i<=n;i++)
			for (j=i;j<=n;j++)
				sum[i][j]=(i==j?0:d[j-1]*(sum[i][j-1]+dp[j-1])+1);
		for (sta=2;sta<=k;sta++)
		{
			for (i=0;i<=n;i++) tmp[i]=1e100;
			solve(1,n,1,n);
			for (i=0;i<=n;i++) DP[i]=tmp[i];
		}
		printf("%.4lf\n",DP[n]);
	}
	return 0;
}
