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

const int MOD=1e9;
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

int n,e,t;

int d[300048];
int head[300048],to[300048],nxt[300048],f[300048],low[300048],high[300048],type[300048],tot=1;
inline void addedge(int s,int t,int lo,int hi,int ty)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;low[tot]=lo;high[tot]=hi;f[tot]=hi-lo;type[tot]=ty;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;low[tot]=lo;high[tot]=hi;f[tot]=0;type[tot]=2-ty;
}

inline void Clear() {tot=1;memset(head,0,sizeof(head));memset(d,0,sizeof(d));}

int depth[300048];queue<int> q;
inline bool bfs()
{
	int i,x,y;
	for (i=0;i<=t;i++) depth[i]=-1;
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
	if (depth[t]==-1) return false; else return true;
}

inline int dfs(int x,int maxf)
{
	if (x==t || !maxf) return maxf;
	int i,y,minf,now,ans=0;
	for (i=head[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
		if (ans>=maxf) return maxf;
	}
	if (!ans) depth[x]=0;
	return ans;
}

int main ()
{
	int i,ca,lo,hi,x,y;
	ca=getint();
	while (ca--)
	{
		Clear();
		n=getint();e=getint();t=n+1;
		for (i=1;i<=e;i++)
		{
			x=getint();y=getint();lo=getint();hi=getint();
			addedge(x,y,lo,hi,0);
			d[x]+=lo;d[y]-=lo;
		}
		int sum=0;
		for (i=1;i<=n;i++)
		{
			if (d[i]>0) sum+=d[i];
			if (d[i]>0) addedge(i,t,0,d[i],1); else addedge(0,i,0,-d[i],1);
		}
		int ans=0;
		while (bfs()) ans+=dfs(0,2e9);
		if (ans!=sum) {printf("NO\n");continue;}
		printf("YES\n");
		for (i=2;i<=tot;i++)
			if (type[i]==2) printf("%d\n",low[i]+f[i]);
	}
	return 0;
}
