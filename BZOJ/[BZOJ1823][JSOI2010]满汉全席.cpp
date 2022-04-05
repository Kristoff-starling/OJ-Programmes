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

int n,m;
int table[248];
int ind=0,bel[MAXN+48];

int head[MAXN+48],to[MAXN+48],nxt[MAXN+48],tot;
inline void addedge(int s,int t) {to[++tot]=t;nxt[tot]=head[s];head[s]=tot;}

inline int getind(int type,int x) {return (type-1)*n+x;}

stack<int> s;int dfn[MAXN+48],low[MAXN+48],Index;
bool visited[MAXN+48];

inline void Clear()
{
	tot=1;memset(head,0,sizeof(head));
	ind=0;memset(bel,0,sizeof(bel));
	memset(dfn,0,sizeof(dfn));memset(visited,false,sizeof(visited));
	Index=0;
}

inline void tarjan(int cur)
{
	dfn[cur]=low[cur]=++Index;s.push(cur);
	visited[cur]=true;
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (!dfn[y])
		{
			tarjan(y);
			low[cur]=min(low[cur],low[y]);
		}
		else if (visited[y]) low[cur]=min(low[cur],dfn[y]);
	}
	if (dfn[cur]==low[cur])
	{
		++ind;int vv;
		do
		{
			vv=s.top();s.pop();
			visited[vv]=false;
			bel[vv]=ind;
		}
		while (vv!=cur);
	}
}

int main ()
{
	int i,ca;ca=getint();
	char s1,s2;int d1,d2;
	table['m']=1;table['h']=2;
	while (ca--)
	{
		n=getint();m=getint();Clear();
		for (i=1;i<=m;i++)
		{
			scanf("\n%c%d %c%d",&s1,&d1,&s2,&d2);
			addedge(getind(3-table[s1],d1),getind(table[s2],d2));
			addedge(getind(3-table[s2],d2),getind(table[s1],d1));
		}
		for (i=1;i<=n*2;i++)
			if (!dfn[i]) tarjan(i);
		bool f=true;
		for (i=1;i<=n;i++)
			if (bel[getind(1,i)]==bel[getind(2,i)]) {f=false;break;}
		if (f) printf("GOOD\n"); else printf("BAD\n");
	}
	return 0;
}
