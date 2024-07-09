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

int n,m,num;
int a[148][148];

int head[100048],to[200048],nxt[200048],f[200048],cost[200048],tot=1;
inline void addedge(int s,int t,int cap,int c)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=c;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-c;
}

inline int PairToInd(int x,int y)
{
	return (x-1)*m+y;
}

int flow,mincost;
bool visited[100048];int D[100048];

int aug(int cur,int maxf)
{
	visited[cur]=true;
	if (cur==num) {mincost+=(-D[0])*maxf;return maxf;}
	int i,y,minf,ans=0,now;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y] && f[i] && (D[cur]+cost[i]-D[y]==0))
		{
			minf=min(f[i],maxf-ans);
			now=aug(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
			if (ans>=maxf) return ans;
		}
	}
	return ans;
}

int cc=0;
bool relabel()
{
	int d=INF,i,j;cc++;
	for (i=0;i<=num;i++)
		if (visited[i])
			for (j=head[i];j;j=nxt[j])
				if (!visited[to[j]] && f[j]) d=min(d,D[i]+cost[j]-D[to[j]]);
	if (d==INF) return false;
	for (i=0;i<=num;i++) if (visited[i]) D[i]-=d;
	return true;
}

int main ()
{
	int i,j,s,t;
	n=getint();m=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			a[i][j]=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m-1;j++)
		{
			s=PairToInd(i,j);t=PairToInd(i,j+1);
			if ((i+j)%2==1) swap(s,t);
			if (a[i][j]==a[i][j+1]) addedge(s,t,1,0); else addedge(s,t,1,1);
		}
	for (i=1;i<=n-1;i++)
		for (j=1;j<=m;j++)
		{
			s=PairToInd(i,j);t=PairToInd(i+1,j);
			if ((i+j)%2==1) swap(s,t);
			if (a[i][j]==a[i+1][j]) addedge(s,t,1,0); else addedge(s,t,1,1);
		}
	num=n*m+1;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if ((i+j)%2==0) addedge(0,PairToInd(i,j),1,0); else addedge(PairToInd(i,j),num,1,0);
	int res;
	do
		do
		{
			memset(visited,false,sizeof(visited));
		}
		while (aug(0,INF));
	while (relabel());
	printf("%d\n",mincost);
	return 0;
}
