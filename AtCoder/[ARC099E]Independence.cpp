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
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,e;
bool ga[748][748];
vector<int> v[748];
int type[748];
bool f=true;
int a[748];int tot=0;
int c1,c2;
bool dp[748][748];

inline int myabs(int x) {return x>=0?x:-x;}

inline void dfs(int cur)
{
	int i,y;
	if (type[cur]==1) c1++; else c2++;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (!type[y])
		{
			type[y]=3-type[cur];
			dfs(y);
		}
		else
		{
			if (type[y]+type[cur]!=3) f=false;
		}
	}
}

int main ()
{
	int i,x,y,j;n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		ga[x][y]=ga[y][x]=true;
	}
	int cnt=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (i!=j && !ga[i][j]) v[i].pb(j),cnt++;
	cnt/=2;
	for (i=1;i<=n;i++)
		if (!type[i])
		{
			type[i]=1;c1=c2=0;
			dfs(i);a[++tot]=myabs(c1-c2);
		}
	if (!f)
	{
		printf("-1\n");
		return 0;
	}
	dp[0][0]=true;
	for (i=0;i<=tot-1;i++)
		for (j=0;j<=n;j++)
			if (dp[i][j])
			{
				dp[i+1][j+a[i+1]]=true;
				dp[i+1][myabs(j-a[i+1])]=true;
			}
	int pt=0;
	while (!dp[tot][pt]) pt++;
	c1=(n+pt)/2;c2=(n-pt)/2;
	cnt=c1*c2-cnt;
	printf("%d\n",e-cnt);
	return 0;
}
