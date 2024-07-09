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

int n,e;
int ansnum;vector<int> ans;
vector<Pair> v[10048];
int dfn[10048],low[10048],ind;
int depth[10048],fa[10048],fa_ind[10048];
bool iseven[10048];
int anc[10048][21];
struct Edge
{
	int x,y;
	int ind;
};vector<Edge> tedge,ntedge;
Pair edge[10048];

void Tarjan(int cur)
{
	dfn[cur]=low[cur]=++ind;
	int i,j,to;
	for (i=0;i<int(v[cur].size());i++)
	{
		to=v[cur][i].x;
		if (!dfn[to])
		{
			fa[to]=cur;fa_ind[to]=v[cur][i].y;
			depth[to]=depth[cur]+1;
			tedge.pb(Edge{cur,to,v[cur][i].y});
			anc[to][0]=cur;
			for (j=1;j<=20;j++) anc[to][j]=anc[anc[to][j-1]][j-1];
			Tarjan(to);
			low[cur]=min(low[cur],low[to]);
		}
		else
		{
			if (to!=fa[cur] && depth[cur]>depth[to] && (depth[cur]-depth[to])&1)
				low[cur]=min(low[cur],dfn[to]);
			if (to!=fa[cur] && depth[cur]>depth[to] && !((depth[cur]-depth[to])&1))
				ntedge.pb(Edge{to,cur,v[cur][i].y});
		}
	}
}

int lca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	int i;
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

int Low(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	int LCA=lca(u,v);
	if (LCA!=u && LCA!=v) return -1;
	return u;
}

bool isanc(int u,int v)
{
	if (u==v) return false;
	return lca(u,v)==u;
}

int main ()
{
	int i,cur,x,y;
	n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		edge[i]=mp(x,y);
		v[x].pb(mp(y,i));v[y].pb(mp(x,i));
	}
	int all_cnt=0,superf=true;
	for (cur=1;cur<=n;cur++)
		if (!dfn[cur])
		{
			tedge.clear();ntedge.clear();
			fa[cur]=0;ind=0;depth[cur]=1;
			Tarjan(cur);
			for (i=0;i<int(tedge.size());i++)
			{
				if (depth[tedge[i].x]>depth[tedge[i].y]) swap(edge[i].x,edge[i].y);
				if (low[tedge[i].y]!=dfn[tedge[i].y]) iseven[tedge[i].ind]=true;
			}
			if (int(ntedge.size())) all_cnt++;
			if (int(ntedge.size())==1)
			{
				ansnum++;
				ans.pb(ntedge[0].ind);
			}
			int curu=-2,curv=-2;
			for (i=0;i<int(ntedge.size());i++)
			{
				if (depth[ntedge[i].x]>depth[ntedge[i].y]) swap(ntedge[i].x,ntedge[i].y);
				if (curu==-2)
				{
					curu=ntedge[i].x;
					curv=ntedge[i].y;
					continue;
				}
				curu=Low(ntedge[i].x,curu);
				if (curu==-1)
				{
					superf=false;
					break;
				}
				curv=lca(ntedge[i].y,curv);
				if (!isanc(curu,curv))
				{
					superf=false;
					break;
				}
			}
			if (!superf) break;
			for (;curv!=curu;curv=fa[curv])
				if (!iseven[fa_ind[curv]])
				{
					ansnum++;
					ans.pb(fa_ind[curv]);
				}
		}
	if (!superf)
	{
		printf("0\n");
		return 0;
	}
	if (all_cnt==0)
	{
		printf("%d\n",e);
		for (i=1;i<=e;i++) printf("%d ",i);
		printf("\n");return 0;
	}
	if (all_cnt>1)
	{
		printf("0\n");
		return 0;
	}
	printf("%d\n",ansnum);
	if (ansnum)
	{
		sort(ans.begin(),ans.end());
		for (i=0;i<int(ans.size());i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}