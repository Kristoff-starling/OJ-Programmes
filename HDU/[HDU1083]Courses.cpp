#include <cstdio> 
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <cmath>
#include <cctype>
#include <stack>
#include <sstream>
#define LL long long
#define LB long double
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int p,n;

int t,head[100048],to[200048],nxt[200048],f[200048],tot=1;
inline int addedge(int s,int t,int l)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

void Clear()
{
	int i;
	for (i=0;i<=t;i++) head[i]=0;
	tot=1;
}

int depth[100048];queue<int> q;
bool bfs()
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

int dfs(int x,int maxf)
{
	if (x==t) return maxf;
	int i,y,minf,now,ans=0;
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
	return ans;
}

int main ()
{
	int i,num,j,x,ca,ans;
	ca=getint();
	while (ca--)
	{
		p=getint();n=getint();
		t=n+p+1;
		Clear();
		for (i=1;i<=p;i++)
		{
			num=getint();
			for (j=1;j<=num;j++)
			{
				x=getint();
				addedge(x,n+i,1);
			}
		}
		for (i=1;i<=n;i++) addedge(0,i,1);
		for (i=1;i<=p;i++) addedge(n+i,t,1);
		ans=0;
		while (bfs()) ans+=dfs(0,2e9);
		if (ans==p) printf("YES\n"); else printf("NO\n");
	}
	return 0;
}
