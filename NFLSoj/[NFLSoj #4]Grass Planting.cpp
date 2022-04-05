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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,q,ind=0;
vector<int> v[100048];
int Left[100048],Right[100048];
int seq[100048],Pos[100048];
int depth[100048],anc[100048][21];
string type;

int c[100048];
inline void update(int x,int delta)
{
	while (x<=n)
	{
		c[x]+=delta;
		x+=LOWBIT(x);
	}
}
inline int query(int x)
{
	int res=0;
	while (x)
	{
		res+=c[x];
		x-=LOWBIT(x);
	}
	return res;
}
inline int calc(int left,int right)
{
	return query(right)-query(left-1);
}

void dfs(int cur,int father)
{
	int i,j,to;
	Left[cur]=++ind;seq[ind]=cur;Pos[cur]=ind;
	for (i=0;i<v[cur].size();i++)
	{
		to=v[cur][i];
		if (to!=father)
		{
			depth[to]=depth[cur]+1;
			anc[to][0]=cur;
			for (j=1;j<=20;j++) anc[to][j]=anc[anc[to][j-1]][j-1];
			dfs(to,cur);
		}
	}
	Right[cur]=ind;
}

int get_lca(int u,int v)
{
	int i;
	if (depth[u]<depth[v]) swap(u,v);
	for (i=20;i>=0;i--)
		if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (i=20;i>=0;i--)
		if (anc[u][i]!=anc[v][i])
		{
			u=anc[u][i];
			v=anc[v][i];
		}
	return anc[u][0];
}

int main ()
{
	int i,x,y,LCA;
	n=getint();q=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
	}
	depth[1]=1;dfs(1,0);
	for (i=1;i<=q;i++)
	{
		cin>>type;
		if (type[0]=='P')
		{
			x=getint();y=getint();
			LCA=get_lca(x,y);
			update(Pos[x],1);update(Pos[y],1);update(Pos[LCA],-2);
		}
		else
		{
			x=getint();y=getint();
			if (depth[x]<depth[y]) swap(x,y);
			printf("%d\n",calc(Left[x],Right[x]));
		}
	}
	return 0;
}

