#include <cassert>
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

const LL MOD=1e9+7;
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

int n,q,X,Y,LCA;
vector<Pair> v[20048];
vector<Pair> vv[20048];
int depth[20048],fa[20048],faedge[20048];
int sz[20048];
int L[20048],R[20048],pos[20048],anc[20048][21];
int ind=0;
int Len[20048],sta[20048];
int seq[20048];

inline void dfs(int cur,int father)
{
	int i,j,y;sz[cur]=1;L[cur]=++ind;pos[cur]=ind;seq[ind]=cur;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			depth[y]=depth[cur]+1;fa[y]=cur;faedge[y]=v[cur][i].y;
			anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);sz[cur]+=sz[y];
		}
	}
	R[cur]=ind;
}

int ans=0;
int List[20048],tmp[20048],tot,ttot;
inline void getlist(int u,int v)
{
	tot=ttot=0;
	while (u!=v) if (depth[u]>depth[v]) List[++tot]=faedge[u],u=fa[u]; else tmp[++ttot]=faedge[v],v=fa[v];
	for (register int i=ttot;i>=1;i--) List[++tot]=tmp[i];
}

int main ()
{
	int i,j,x,y;char c;
	n=getint();q=getint();
	for (i=1;i<=n-1;i++)
	{
		cin>>x>>y>>c;
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	depth[1]=1;dfs(1,-1);
	for (i=1;i<=n;i++)
		for (j=0;j<int(v[i].size());j++)
			if (v[i][j].x!=fa[i]) vv[i].pb(v[i][j]);
	while (q--)
	{
		x=getint();y=getint();X=x;Y=y;
		ans=0;
		getlist(x,y);
		memset(Len,-1,sizeof(Len));
		sta[x]=0;Len[x]=0;
		for (register int cur=x;fa[cur];cur=fa[cur])
		{
			Len[fa[cur]]=Len[cur]+1;
			if (sta[cur]) {sta[fa[cur]]=sta[cur];continue;}
			if (faedge[cur]==List[Len[fa[cur]]])
			{
				if (Len[fa[cur]]==tot) sta[fa[cur]]=1; else sta[fa[cur]]=0;
			}
			if (faedge[cur]<List[Len[fa[cur]]]) sta[fa[cur]]=2;
			if (faedge[cur]>List[Len[fa[cur]]]) sta[fa[cur]]=1;
		}
		int ans=0;
		for (i=1;i<=n;i++)
		{
			int cur=seq[i];
			if (Len[cur]==-1)
			{
				Len[cur]=Len[fa[cur]]+1;
				if (sta[fa[cur]]) sta[cur]=sta[fa[cur]];
				else
				{
				if (faedge[cur]==List[Len[cur]])
				{
					if (Len[cur]==tot) sta[cur]=1; else sta[cur]=0;
				}
				if (faedge[cur]<List[Len[cur]]) sta[cur]=2;
				if (faedge[cur]>List[Len[cur]]) sta[cur]=1;
				}
			}
			if (sta[cur]!=1) ans++;
		}
		printf("%d\n",ans-1);
	}
	return 0;
}
