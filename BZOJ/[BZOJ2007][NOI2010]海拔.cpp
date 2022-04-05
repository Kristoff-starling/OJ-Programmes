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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
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
 
inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int st,ed,n;
int head[1000048],to[2000048],nxt[2000048],f[2000048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
}

inline int PairToInd(int x,int y)
{
	return (x-1)*n+y;
}

LL dist[1000048];
priority_queue<pair<LL,int> > q;
LL dijkstra()
{
	int i,cur,y;LL dd;
	for (i=1;i<=ed;i++) dist[i]=LINF;
	dist[st]=0;q.push(mp(0,st));
	while (!q.empty())
	{
		cur=q.top().y;dd=-q.top().x;q.pop();
		if (dd>dist[cur]) continue;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (dist[cur]+f[i]<dist[y])
			{
				dist[y]=dist[cur]+f[i];
				q.push(mp(-dist[y],y));
			}
		}
	}
	return dist[ed];
}

int main ()
{
	int i,j,c;
	n=getint();
	st=n*n+1;ed=n*n+2;
	for (i=1;i<=n+1;i++)
		for (j=1;j<=n;j++)
		{
			c=getint();
			if (i==1) {addedge(st,PairToInd(i,j),c);continue;}
			if (i==n+1) {addedge(PairToInd(n,j),ed,c);continue;}
			addedge(PairToInd(i-1,j),PairToInd(i,j),c);
		}
	for (i=1;i<=n;i++)
		for (j=1;j<=n+1;j++)
		{
			c=getint();
			if (j==1) {addedge(PairToInd(i,j),ed,c);continue;}
			if (j==n+1) {addedge(st,PairToInd(i,n),c);continue;}
			addedge(PairToInd(i,j),PairToInd(i,j-1),c);
		}
	for (i=1;i<=n+1;i++)
		for (j=1;j<=n;j++)
		{
			c=getint();
			if (i==1 || i==n+1) continue;
			addedge(PairToInd(i,j),PairToInd(i-1,j),c);
		}
	for (i=1;i<=n;i++)
		for (j=1;j<=n+1;j++)
		{
			c=getint();
			if (j==1 || j==n+1) continue;
			addedge(PairToInd(i,j-1),PairToInd(i,j),c);
		}
	printf("%lld\n",dijkstra());
	return 0;
}
