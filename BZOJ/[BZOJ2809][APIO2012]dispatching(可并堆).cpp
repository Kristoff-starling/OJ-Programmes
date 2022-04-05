#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n,m;
int cost[MAXN+48],leader[MAXN+48];
vector<int> v[MAXN+48];

int root[MAXN+48];
LL ans=-1;

namespace LeftistTree
{
	int lson[MAXN+48],rson[MAXN+48],sz[MAXN+48],val[MAXN+48],h[MAXN+48],tot=0;LL sum[MAXN+48];
	inline int newtree(int vv)
	{
		++tot;lson[tot]=rson[tot]=0;
		sz[tot]=1;sum[tot]=val[tot]=vv;
		h[tot]=1;
		return tot;
	}
	inline int merge(int x,int y)
	{
		if (!x || !y) return x+y;
		if (val[x]<val[y]) swap(x,y);
		rson[x]=merge(rson[x],y);
		if (h[lson[x]]<h[rson[x]]) swap(lson[x],rson[x]);
		h[x]=h[rson[x]]+1;
		sz[x]=sz[lson[x]]+sz[rson[x]]+1;
		sum[x]=sum[lson[x]]+sum[rson[x]]+val[x];
		return x;
	}
	inline int pop(int x) {return merge(lson[x],rson[x]);}
}

using namespace LeftistTree;

inline void dfs(int cur,int father)
{
	int i,y;root[cur]=newtree(cost[cur]);
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			dfs(y,cur);
			root[cur]=merge(root[cur],root[y]);
			while (sum[root[cur]]>m) root[cur]=pop(root[cur]);
		}
	}
	ans=max(ans,1ll*leader[cur]*sz[root[cur]]);
}

int main ()
{
	n=getint();m=getint();int i,x;
	for (i=1;i<=n;i++)
	{
		x=getint();cost[i]=getint();leader[i]=getint();
		if (x) v[x].pb(i),v[i].pb(x);
	}
	dfs(1,-1);
	printf("%lld\n",ans);
	return 0;
}
