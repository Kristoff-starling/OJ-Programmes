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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m;
int a[148];
int table[148][148];

int head[1000048],nxt[1000048],to[1000048],f[1000048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int ntot=0;
int ind[148][148];
int indtype[1048];

int depth[100048];queue<int> q;
bool bfs()
{
	int i,x,y;
	for (i=0;i<=ntot;i++) depth[i]=-1;
	depth[0]=0;q.push(0);
	while (!q.empty())
	{
		x=q.front();q.pop();
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && f[i])
			{
				depth[y]=depth[x]+1;
				q.push(y);
			}
		}
	}
	return depth[ntot]==-1?false:true;
}

int dfs(int x,int maxf)
{
	if (x==ntot) return maxf;
	int i,y,ans=0,minf,now;
	for (i=head[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;
			f[i^1]+=now;
			ans+=now;
		}
	}
	if (ans==0) depth[x]=0;
	return ans;
}

int main ()
{
	int i,j;
	n=getint();m=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=n-i+1;j++)
		{
			table[i][i+j-1]=getint();
			ind[i][i+j-1]=++ntot;
		}
	for (i=1;i<=1000;i++) indtype[i]=++ntot;
	++ntot;
	LL ans=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=n-i+1;j++)
		{
			int left=i,right=i+j-1;
			if (left!=right) 
			{
				addedge(ind[left][right],ind[left+1][right],INF);
				addedge(ind[left][right],ind[left][right-1],INF);
			}
			else
				addedge(ind[left][right],indtype[a[left]],INF);
			int val=table[left][right]-(left!=right?0:a[left]);
			if (val>0) ans+=val;	
			if (val>=0)
				addedge(0,ind[left][right],val);
			else
				addedge(ind[left][right],ntot,-val);
		}
	for (i=1;i<=1000;i++)
		addedge(indtype[i],ntot,m*i*i);
	while (bfs()) ans-=dfs(0,INF);
	printf("%lld\n",ans);
	return 0;
}
