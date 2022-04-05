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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
int a[100048],b[100048],c[100048];
int dist[200048];
int head[200048],nxt[200048],to[200048],f[200048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
}
queue<int> q;bool inq[100048];

inline void spfa()
{
	int i,cur,y;
	memset(inq,false,sizeof(inq));
	for (i=0;i<=60000;i++) dist[i]=-1;
	dist[0]=0;q.push(0);inq[0]=true;
	while (!q.empty())
	{
		cur=q.front();q.pop();inq[cur]=false;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (dist[cur]+f[i]>dist[y])
			{
				dist[y]=dist[cur]+f[i];
				if (!inq[y]) inq[y]=true,q.push(y);
			}
		}
	}
}

int main ()
{
	int i;n=getint();
	for (i=1;i<=n;i++) a[i]=getint(),b[i]=getint(),c[i]=getint();
	for (i=1;i<=60000;i++) addedge(i-1,i,0),addedge(i,i-1,-1);
	for (i=1;i<=n;i++) addedge(a[i],b[i]+1,c[i]);
	spfa();
	printf("%d\n",dist[60000]);
	return 0;
}
