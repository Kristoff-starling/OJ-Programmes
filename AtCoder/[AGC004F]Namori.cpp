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
const int INF=1e9;
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

int n,e;
vector<int> v[100048];
bool visited[100048];
int depth[100048],cnt[100048][2],fa[100048];
Pair cycle;

inline int myabs(int x) {return x>=0?x:-x;}

namespace tree
{
	inline void dfs(int cur,int father)
	{
		int i,y;
		cnt[cur][0]=cnt[cur][1]=0;cnt[cur][depth[cur]]=1;
		for (i=0;i<int(v[cur].size());i++)
		{
			y=v[cur][i];
			if (y!=father)
			{
				depth[y]=depth[cur]^1;dfs(y,cur);
				cnt[cur][0]+=cnt[y][0];cnt[cur][1]+=cnt[y][1];
			}
		}
	}
	inline int solve()
	{
		int i,x,y;
		depth[1]=1;dfs(1,-1);
		if (cnt[1][0]!=cnt[1][1]) return -1;
		int res=0;
		for (i=2;i<=n;i++) res+=myabs(cnt[i][0]-cnt[i][1]);
		return res;
	}
}

inline void dfs(int cur,int father)
{
	int i,y;visited[cur]=true;fa[cur]=father;
	cnt[cur][0]=cnt[cur][1]=0;cnt[cur][depth[cur]]=1;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			if (visited[y]) {if (cycle.x==0) cycle=mp(y,cur);continue;}
			depth[y]=depth[cur]^1;dfs(y,cur);
			cnt[cur][0]+=cnt[y][0];cnt[cur][1]+=cnt[y][1];
		}
	}
}

namespace even
{
	vector<int> cir;bool incir[100048];
	inline int solve()
	{
		if (cnt[1][0]!=cnt[1][1]) return -1;
		int cur,i,ans=0;cir.clear();
		memset(incir,false,sizeof(incir));
		for (cur=cycle.y;cur!=cycle.x;cur=fa[cur]) incir[cur]=true,cir.pb(cnt[cur][1]-cnt[cur][0]);
		cir.pb(0);
		sort(cir.begin(),cir.end());int nm=int(cir.size());
		int coef=cir[nm/2-1];
		for (i=0;i<int(cir.size());i++) ans+=myabs(cir[i]-coef);
		for (i=2;i<=n;i++)
			if (!incir[i]) ans+=myabs(cnt[i][1]-cnt[i][0]);
		return ans;
	}
}

namespace odd
{
	int w[100048],sz[100048],sum[100048],ans;
	inline void dfs(int cur,int father)
	{
		sz[cur]=(depth[cur]==0);sum[cur]=w[cur];int i,y;
		for (i=0;i<int(v[cur].size());i++)
		{
			y=v[cur][i];
			if (y==father || (y==cycle.x && cur==cycle.y) || (y==cycle.y && cur==cycle.x)) continue;
			dfs(y,cur);sz[cur]+=sz[y];sum[cur]+=sum[y];
		}
		if (cur!=1) ans+=myabs(sum[cur]-sz[cur]);
	}
	inline int solve()
	{
		if (cnt[1][0]%2!=cnt[1][1]%2) return -1;
		ans=myabs(cnt[1][0]-cnt[1][1])/2;int delta=(cnt[1][0]-cnt[1][1])/2,i;
		for (i=1;i<=n;i++) w[i]=depth[i];
		w[cycle.x]+=delta;w[cycle.y]+=delta;
		dfs(1,-1);
		return ans;
	}
}

int main ()
{
	int i,x,y;
	n=getint();e=getint();
	for (i=1;i<=e;i++) x=getint(),y=getint(),v[x].pb(y),v[y].pb(x);
	if (e==n-1) {printf("%d\n",tree::solve());return 0;}
	depth[1]=1;cycle=mp(0,0);dfs(1,-1);
	if (depth[cycle.x]!=depth[cycle.y]) printf("%d\n",even::solve()); else printf("%d\n",odd::solve());
	return 0;
}
