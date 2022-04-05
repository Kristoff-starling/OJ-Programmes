#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

int head[60048],to[100048],nxt[100048],tot=0;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

int n,k;
int ans=0;
int sum[100048],Cnt[648],depth[100048];
bool visited[100048];

void dfs(int cur,int father)
{
	int i,y;
	sum[cur]=1;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !visited[y])
		{
			dfs(y,cur);
			sum[cur]+=sum[y];
		}
	}
}

int find_mid(int cur,int father,int sz)
{
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !visited[y] && sum[y]>sz/2)
			return find_mid(y,cur,sz);
	}
	return cur;
}

vector<int> v;
void Dfs(int cur,int father)
{
	int i,y;
	v.pb(depth[cur]);
	if (depth[cur]>=k) return;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !visited[y])
		{
			depth[y]=depth[cur]+1;
			Dfs(y,cur);
		}
	}
}

void solve(int root,int sz)
{
	dfs(root,-1);
	int i,j,y,mid=find_mid(root,-1,sz);
	root=mid;visited[root]=true;
	memset(Cnt,0,sizeof(Cnt));
	dfs(root,-1);
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y])
		{
			depth[y]=1;v.clear();
			Dfs(y,root);
			for (j=0;j<v.size();j++)
				if (v[j]==k) ans++; else ans+=Cnt[k-v[j]];
			for (j=0;j<v.size();j++) Cnt[v[j]]++;
		}
	}
	for (i=head[root];i;i=nxt[i])
		if (!visited[to[i]]) solve(to[i],sum[to[i]]);	
}

int main ()
{
	int i,x,y;
	n=getint();k=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		addedge(x,y);
	}
	solve(1,n);
	printf("%d\n",ans);
	return 0;
}
