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
int fa[1048],val[1048];

namespace DSU
{
	int pre[1048],sum[1048],sz[1048],ans[1048];
	inline void init() {for (register int i=1;i<=n;i++) pre[i]=i,sum[i]=val[i],sz[i]=1,ans[i]=val[i];}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		ans[x]+=ans[y]+(sum[y]*sz[x]);
		pre[y]=x;sum[x]+=sum[y];sz[x]+=sz[y];
	}
}

typedef pair<double,int> PII;
priority_queue<PII> q;

int main ()
{
	int i,x,y;
	while (scanf("%d%d",&n,&root) && n && root)
	{
		for (i=1;i<=n;i++) val[i]=getint();
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();
			fa[y]=x;
		}
		DSU::init();
		for (i=1;i<=n;i++) q.push(mp(val[i],i));
		while (!q.empty())
		{
			x=q.top().y;q.pop();
			if (DSU::find_anc(x)!=x || x==root) continue;
			y=DSU::find_anc(fa[x]);
			DSU::update(y,x);
			q.push(mp(DSU::sum[y]*1.0/DSU::sz[y],y));
		}
		printf("%d\n",DSU::ans[root]);
	}
	return 0;
}
