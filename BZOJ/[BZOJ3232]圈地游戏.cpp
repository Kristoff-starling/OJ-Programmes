#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <cctype>
#include <functional>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <deque>
#include <stack>
#define LL long long
#define LB long double
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=998244353;
const int magic=348;
const int INF=2e9;
const LL LINF=2e16;
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

int n,m,t;
int row[148][148],col[148][148];
int val[148][148];
long double sum;

inline bool islarger(long double x,long double y) {return x-y>eps;}

int head[100048],cur[100048],nxt[100048],to[100048],tot;long double f[100048];
inline void addedge(int s,int t,long double cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

inline void Addedge(int s,int t,long double cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=cap;
}

int q[100048],Head,Tail,depth[100048];
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
			if (depth[y]==-1 && islarger(f[i],0))
			{
				depth[y]=depth[x]+1;
				q[++Tail]=y;
			}
		}
	}
	if (depth[t]==-1) return false; else return true;
}

bool visited[1048];
inline void print(int cur)
{
	cout<<cur<<"*"<<endl;visited[cur]=true;
	for (int i=head[cur];i;i=nxt[i])
	{
		if (f[i]>eps && !visited[to[i]]) print(to[i]);
	}
}

inline long double dfs(int x,long double maxf)
{
	if (x==t) return maxf;
	int y;long double now,minf,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && islarger(f[i],0))
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	if (!islarger(ans,0)) depth[x]=0;
	return ans;
}

inline int getind(int x,int y) {return (x-1)*m+y;}

inline bool check(long double c)
{
	int i,j;
	for (i=0;i<=t;i++) head[i]=0;tot=1;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			addedge(0,getind(i,j),val[i][j]);
	for (i=1;i<=n-1;i++)
		for (j=1;j<=m;j++)
			Addedge(getind(i,j),getind(i+1,j),c*row[i+1][j]);
	for (i=1;i<=n;i++)
		for (j=1;j<=m-1;j++)
			Addedge(getind(i,j),getind(i,j+1),c*col[i][j+1]);
	for (j=1;j<=m;j++)
	{
		addedge(getind(1,j),t,c*row[1][j]);
		addedge(getind(n,j),t,c*row[n+1][j]);
	}
	for (i=1;i<=n;i++)
	{
		addedge(getind(i,1),t,c*col[i][1]);
		addedge(getind(i,m),t,c*col[i][m+1]);
	}
	long double ans=0;
	while (bfs())
	{
		for (i=0;i<=t;i++) cur[i]=head[i];
		ans+=dfs(0,2e9);
	}
	//print(0);
	if (islarger(sum,ans)) return true; else return false;
}

int main ()
{
	int i,j;n=getint();m=getint();
	sum=0;t=n*m+1;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			val[i][j]=getint(),sum+=val[i][j];
	for (i=1;i<=n+1;i++)
		for (j=1;j<=m;j++)
			row[i][j]=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m+1;j++)
			col[i][j]=getint();
	long double l=0,r=250000,mid,ans;
	while (r-l>=1e-5)
	{
		mid=(l+r)/2;
		if (check(mid)) ans=mid,l=mid; else r=mid;
	}
	printf("%.3Lf\n",ans);
	return 0;
}
