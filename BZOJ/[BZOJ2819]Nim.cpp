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
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline char GetChar()
{
	char ch;
	while (!isalpha(ch=getchar())) {}
	return ch;
}

int n,q;
int depth[500048],anc[500048][21],sum[500048];
int a[500048];int L[500048],R[500048],ind=0;

namespace BIT
{
	int c[500048];
	inline void init() {for (register int i=1;i<=n+10;i++) c[i]=0;}
	inline void update(int x,int newval) {while (x<=n) {c[x]^=newval;x+=LOWBIT(x);}}
	inline int query(int x) {int res=0;while (x) {res^=c[x];x-=LOWBIT(x);}return res;}
	inline void Update(int left,int right,int newval) {update(left,newval);update(right+1,newval);}
}

int head[1000048],nxt[1500048],to[1500048],tot=1;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

inline void dfs(int cur)
{
	L[cur]=++ind;
	int i,j,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=anc[cur][0])
		{
			depth[y]=depth[cur]+1;anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y);
		}
	}
	R[cur]=ind;
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--)
		if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--)
		if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

int main ()
{
	int i,x,y,LCA,res;char type;n=getint();BIT::init();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		addedge(x,y);
	}
	depth[1]=1;dfs(1);
	for (i=1;i<=n;i++) BIT::Update(L[i],R[i],a[i]);
	q=getint();
	while (q--)
	{
		type=GetChar();x=getint();y=getint();
		if (type=='C')
		{
			BIT::Update(L[x],R[x],a[x]^y);
			a[x]=y;
		}
		else
		{
			LCA=getlca(x,y);	
			res=(BIT::query(L[x])^BIT::query(L[y])^a[LCA]);
			if (res) printf("Yes\n"); else printf("No\n");
		}
	}
	return 0;
}
