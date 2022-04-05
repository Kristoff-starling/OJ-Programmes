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
  
inline LL getLL()
{
    bool f;char ch;LL res;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

const int MAXN=20000;

int n,e;
int d[MAXN+48];
struct Edge
{
	int x,y,type;
	inline void input() {x=getint();y=getint();type=getint();}
}edge[MAXN+48];

int head[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],cur[MAXN+48],tot=1,t;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int depth[MAXN+48],q[MAXN+48],Head,Tail;
inline bool bfs()
{
	int i,x,y;
	for (i=0;i<=t;i++) depth[i]=-1;
	depth[0]=0;q[1]=0;Head=Tail=1;
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

inline int dinic()
{
	int ans=0,i;
	while (bfs())
	{
		for (i=0;i<=t;i++) cur[i]=head[i];
		ans+=dfs(0,INF);
	}
	return ans;
}

inline void Clear()
{
	tot=1;memset(head,0,sizeof(head));
	memset(d,0,sizeof(d));
}

int main ()
{
	int i,ca;ca=getint();
	while (ca--)
	{
		n=getint();e=getint();Clear();
		for (i=1;i<=e;i++)
		{
			edge[i].input();
			d[edge[i].x]--;d[edge[i].y]++;
		}
		bool f=true;
		for (i=1;i<=n;i++)
			if (d[i]%2==1) {f=false;break;}
		if (!f) {puts("impossible");continue;}
		for (i=1;i<=e;i++)
			if (!edge[i].type) addedge(edge[i].y,edge[i].x,1);
		t=n+1;int sum=0;
		for (i=1;i<=n;i++)
		{
			if (d[i]>0) addedge(0,i,d[i]/2),sum+=d[i]/2;
			if (d[i]<0) addedge(i,t,-d[i]/2);
		}
		int ans=dinic();
		if (ans==sum) puts("possible"); else puts("impossible");
	}
	return 0;
}
