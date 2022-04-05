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

int n,m;
int qind[100048],tot=0;
priority_queue<int> q[100048];
int sz[100048];LL sum[100048];
vector<int> v[100048];
int c[100048],L[100048];
LL ans=0;

inline void merge(int rt1,int rt2)
{
	while (!q[rt2].empty()) q[rt1].push(q[rt2].top()),q[rt2].pop();
	sum[rt1]+=sum[rt2];sz[rt1]+=sz[rt2];
}

inline void dfs(int cur,int father)
{
	if (int(v[cur].size())==1 && father)
	{
		qind[cur]=++tot;
		q[tot].push(c[cur]);sum[tot]=c[cur];sz[tot]=1;
		ans=max(ans,(long long)L[cur]);
		return;
	}
	int i,y;
	int maxsz=0,maxind;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			dfs(y,cur);
			if (sz[qind[y]]>maxsz)
			{
				maxsz=sz[qind[y]];
				maxind=qind[y];
			}
		}
	}
	qind[cur]=maxind;
	q[maxind].push(c[cur]);sz[maxind]++;sum[maxind]+=c[cur];
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father && qind[y]!=maxind) merge(maxind,qind[y]);
	}
	while (sum[maxind]>m)
	{
		int cc=q[maxind].top();
		sum[maxind]-=cc;sz[maxind]--;
		q[maxind].pop();
	}
	ans=max(ans,(long long)L[cur]*sz[qind[cur]]);
}

int main ()
{
	int i,x;n=getint();m=getint();
	for (i=1;i<=n;i++)
	{
		x=getint();c[i]=getint();L[i]=getint();
		if (x) v[x].pb(i),v[i].pb(x);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
