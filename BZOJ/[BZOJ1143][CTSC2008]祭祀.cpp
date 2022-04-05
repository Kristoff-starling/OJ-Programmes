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

int n,e;
int ga[148][148];

inline void Floyd()
{
	int i,j,k;
	for (k=1;k<=n;k++)
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				if (i!=j && i!=k && k!=j && ga[i][k] && ga[k][j]) ga[i][j]=1;
}

int head[1048],cur[1048],to[100048],nxt[100048],f[100048],tot=1,t;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int depth[1048],q[1048],Head,Tail;
inline bool bfs()
{
	int i,x,y;
	for (i=0;i<=t;i++) depth[i]=-1;
	depth[0]=0;Head=Tail=1;q[1]=0;
	while (Head<=Tail)
	{
		x=q[Head++];
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && f[i])
			{
				depth[y]=depth[x]+1;
				q[++Tail]=y;
			}
		}
	}
	if (depth[t]==-1) return false; else return true;
}

inline int dfs(int x,int maxf)
{
	if (x==t) return maxf;
	int y,minf,now,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	if (!ans) depth[x]=0;
	return ans;
}

int main ()
{
	int i,j,x,y;n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		ga[x][y]=1;
	}
	Floyd();t=n*2+1;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (ga[i][j]) addedge(i,n+j,INF);
	for (i=1;i<=n;i++) addedge(0,i,1),addedge(n+i,t,1);
	int ans=0;
	while (bfs())
	{
		for (i=0;i<=t;i++) cur[i]=head[i];
		ans+=dfs(0,2e9);
	}
	printf("%d\n",n-ans);
	return 0;
}
