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

const int MOD=1e9+9;
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

int n,e;
vector<int> v[1048];
int pos[1048];
int depth[1048],anc[1048][20];
vector<int> valid[1048];

struct Edge
{
	int u,v,c;
	int Mask;
}edge[10048];int etot;

inline void dfs(int cur,int father)
{
	int i,j,y,ind=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];++ind;
		if (y!=father)
		{
			pos[y]=ind;
			anc[y][0]=cur;depth[y]=depth[cur]+1;
			for (j=1;j<=15;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=15;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=15;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline int getbelow(int u,int LCA)
{
	if (u==LCA) return 0;
	for (register int i=15;i>=0;i--) if (depth[anc[u][i]]>depth[LCA]) u=anc[u][i];
	return u;
}

int dp[1048],DP[6048][1048];
int dp2[1048][1048];

inline int calc(int u,int v,int LCA)
{
	int res=0,cur=u;
	while (depth[u]>depth[LCA]+1) res+=dp2[anc[u][0]][u],u=anc[u][0];
	while (depth[v]>depth[LCA]+1) res+=dp2[anc[v][0]][v],v=anc[v][0];
	return res;
}

inline void Dfs(int cur,int father)
{
	if (father!=-1 && int(v[cur].size())==1) {dp[cur]=0;return;}
	int i,y,Mask,toMask;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father) Dfs(y,cur);
	}
	int ctot=int(v[cur].size());
	memset(DP[0],0,sizeof(DP[0]));
	for (i=0;i<int(valid[cur].size());i++)
		for (Mask=0;Mask<=(1<<ctot)-1;Mask++)
		{
			DP[i+1][Mask]=DP[i][Mask];
			if ((Mask|edge[valid[cur][i]].Mask)==Mask)
			{
				toMask=(Mask^edge[valid[cur][i]].Mask);
				int add=edge[valid[cur][i]].c+dp[edge[valid[cur][i]].u];
				if (edge[valid[cur][i]].v!=cur) add+=dp[edge[valid[cur][i]].v];
				add+=calc(edge[valid[cur][i]].u,edge[valid[cur][i]].v,cur);
				DP[i+1][Mask]=max(DP[i+1][Mask],DP[i][toMask]+add);
			}
		}
	int fi=int(valid[cur].size());
	dp[cur]=0;
	for (i=1;i<=ctot;i++)
		if (v[cur][i-1]!=father) dp2[cur][v[cur][i-1]]=0;
	for (Mask=0;Mask<=(1<<ctot)-1;Mask++)
	{
		int val=DP[fi][Mask];
		for (i=1;i<=ctot;i++)
			if (v[cur][i-1]!=father && !(Mask&(1<<(i-1))))
				val+=dp[v[cur][i-1]];
		dp[cur]=max(dp[cur],val);
		for (i=1;i<=ctot;i++)
			if (v[cur][i-1]!=father && !(Mask&(1<<(i-1))))
				dp2[cur][v[cur][i-1]]=max(dp2[cur][v[cur][i-1]],val-dp[v[cur][i-1]]);
	}
}

int main ()
{
	int i,x,y,c;
	n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();c=getint();
		if (!c) v[x].pb(y),v[y].pb(x); else edge[++etot]=Edge{x,y,c,0};
	}
	depth[1]=1;dfs(1,0);
	for (i=1;i<=etot;i++)
	{
		if (depth[edge[i].u]<depth[edge[i].v]) swap(edge[i].u,edge[i].v);
		int LCA=getlca(edge[i].u,edge[i].v);
		int b1=getbelow(edge[i].u,LCA),b2=getbelow(edge[i].v,LCA);
		if (b2) edge[i].Mask=(1<<(pos[b1]-1))|(1<<(pos[b2]-1)); else edge[i].Mask=(1<<(pos[b1]-1));
		if ((depth[edge[i].u]+depth[edge[i].v]-depth[LCA]*2)%2==0) valid[LCA].pb(i);
	}
	Dfs(1,-1);
	int sum=0;
	for (i=1;i<=etot;i++) sum+=edge[i].c;
	printf("%d\n",sum-dp[1]);
}
/*
5 8 
2 1 0 
3 2 0 
4 3 0 
5 4 0 
1 3 2 
3 5 2 
2 4 5 
2 5 1
*/
