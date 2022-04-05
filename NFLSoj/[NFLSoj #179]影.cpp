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

const int MOD=123456789;
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

int n,A,B,C,t;
int F[148][148];

inline int getind(int x,int y)
{
	return n+(x-1)*n+y;
}

int head[100048],cur[100048],nxt[800048],to[800048],f[800048],cost[800048],tot=1;
inline void addedge(int s,int t,int cap,int cc)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
}

int maxflow,mincost;
int D[100048];bool visited[100048];

inline int aug(int x,int maxf)
{
	if (x==t)
	{
		maxflow+=maxf;
		mincost+=(-D[0])*maxf;
		return maxf;
	}
	visited[x]=true;
	int y,minf,now,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y] && f[i] && D[x]+cost[i]-D[y]==0)
		{
			minf=min(maxf-ans,f[i]);
			now=aug(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	return ans;
}

inline bool relabel()
{
	int cur,i,d=INF;
	for (cur=0;cur<=t;cur++)
		if (visited[cur])
			for (i=head[cur];i;i=nxt[i])
				if (!visited[to[i]] && f[i]) d=min(d,D[cur]+cost[i]-D[to[i]]);
	if (d>=INF) return false;
	for (cur=0;cur<=t;cur++)
		if (visited[cur]) D[cur]-=d;
	return true;
}

int main ()
{
	int i,j;
	n=getint();A=getint();B=getint();C=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=i;j++)
			F[i][j]=getint();
	t=n+n*n+1;
	for (i=1;i<=n;i++)
		for (j=1;j<=i;j++)
		{
			addedge(getind(i,j),t,1,0);
			if (F[i][j]==-1 || F[i][j]==0) addedge(i,getind(i,j),1,0);
			if (F[i][j]==1 || F[i][j]==0) addedge(j,getind(i,j),1,0);
		}
	for (i=1;i<=n;i++)
		for (j=1;j<=n*4-1;j+=2)
			addedge(0,i,1,j*A);
	do
	{
		for (i=0;i<=t;i++) cur[i]=head[i];
		do
			memset(visited,false,sizeof(visited));
		while (aug(0,INF));
	}
	while (relabel());
	printf("%d\n",mincost+n*(n+1)/2*B+n*C);
	return 0;
}
