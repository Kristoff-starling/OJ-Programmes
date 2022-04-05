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
#define DEBUG(...) 
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

int n,t;
int a[148][148],ans[148][148];

int head[400048],nxt[800048],to[800048],f[800048],cost[800048],tot=1;
inline void addedge(int s,int t,int cap,int cc)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
}

inline int getind(int x,int y)
{
	if (x>y) swap(x,y);
	return (x-1)*n+y;
}

inline Pair getpoint(int ind)
{
	int x1=ind/n;if (ind%n) x1++;
	int x2=ind-(x1-1)*n;
	return mp(x1,x2);
}

inline bool isedge(int ind) {return (n+1<=ind && ind<=t-1);}

bool visited[400048];int D[400048];
int mincost=0;

inline int aug(int x,int maxf)
{
	visited[x]=true;
	if (x==t) {mincost+=(-D[0]*maxf);return maxf;}
	if (!maxf) return maxf;
	int i,y,now,minf,res=0;
	for (i=head[x];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y] && f[i] && D[x]+cost[i]-D[y]==0)
		{
			minf=min(maxf-res,f[i]);
			now=aug(y,minf);
			f[i]-=now;f[i^1]+=now;res+=now;
		}
		if (res>=maxf) return res;
	}
	return res;
}

inline bool relabel()
{
	int d=INF,cur,i,y;
	for (cur=0;cur<=t;cur++)
		if (visited[cur])
			for (i=head[cur];i;i=nxt[i])
			{
				y=to[i];
				if (!visited[y] && f[i]) d=min(d,D[cur]+cost[i]-D[y]);
			}
	if (d>=INF) return false;
	for (cur=0;cur<=t;cur++) if (visited[cur]) D[cur]-=d;
	return true;
}

int main ()
{
	int i,j,cur,y;n=getint();t=n+n*(n-1)+1;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			a[i][j]=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=n-1;j++)
			addedge(0,i,1,j-1);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (a[i][j]>=1) addedge(i,n+getind(i,j),1,0);
	for (i=1;i<=n-1;i++)
		for (j=i+1;j<=n;j++)
			addedge(n+getind(i,j),t,1,0);
	memset(ans,0,sizeof(ans));
	do
		do
			memset(visited,false,sizeof(visited));
		while (aug(0,INF));
	while (relabel());
	printf("%d\n",n*(n-1)*(n-2)/6-mincost);
	for (cur=1;cur<=n;cur++)
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (isedge(y) && !f[i])
			{
				Pair xx=getpoint(y-n);
				if (cur==xx.x) ans[cur][xx.y]=1; else ans[cur][xx.x]=1;
			}
		}	
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=n;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
