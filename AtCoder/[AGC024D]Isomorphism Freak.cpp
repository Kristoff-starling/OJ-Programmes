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
const int INF=1e9;
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

int n,tot;
vector<int> v[5000048];
int d[5000048];
int depth[5000048],fa[100048];
int dia[100048],dtot;
bool visited[5000048];

inline void dfs(int cur,int father)
{
	int i,y;fa[cur]=father;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			dfs(y,cur);
		}
	}
}

struct node
{
	int ind,d,depth;
};
queue<node> q;
node clist[5000048];int ctot;

inline LL solve(int root)
{
	memset(depth,0,sizeof(depth));
	depth[root]=1;q.push(node{root,int(v[root].size()),1});
	int curdepth=0,maxdegree,i,j;
	LL res=1;
	while (!q.empty())
	{
		++curdepth;ctot=0;
		while (!q.empty() && q.front().depth==curdepth) clist[++ctot]=q.front(),q.pop();
		maxdegree=0;
		for (i=1;i<=ctot;i++) maxdegree=max(maxdegree,clist[i].d),depth[clist[i].ind]=clist[i].depth;
		if (!maxdegree) maxdegree++;res*=maxdegree;
		for (i=1;i<=ctot;i++)
			for (j=0;j<int(v[clist[i].ind].size());j++)
			{
				int y=v[clist[i].ind][j];
				if (!depth[y]) q.push(node{y,int(v[y].size())-1,depth[clist[i].ind]+1});
			}
	}
	return res;
}

inline void solve1(int buttom)
{
	dtot=0;for (int cur=buttom;cur!=-1;cur=fa[cur]) dia[++dtot]=cur;
	int rt1=dia[dtot/2],rt2=dia[dtot/2+1],i;
	for (i=0;i<int(v[rt1].size());i++)
		if (v[rt1][i]==rt2) {v[rt1].erase(v[rt1].begin()+i);break;}
	for (i=0;i<int(v[rt2].size());i++)
		if (v[rt2][i]==rt1) {v[rt2].erase(v[rt2].begin()+i);break;}
	v[++tot].pb(rt1);v[tot].pb(rt2);
	v[rt1].pb(tot);v[rt2].pb(tot);
	printf("%lld\n",solve(tot));
}

vector<int> vv[100048];
int fm[5000048],sm[5000048],fmind[5000048],smind[5000048];

inline void check_max(int val,int ind,int d)
{
	if (val>=fm[d])
	{
		sm[d]=fm[d];smind[d]=fmind[d];
		fm[d]=val;fmind[d]=ind;
	}
	else if (val>sm[d])
	{
		sm[d]=val;smind[d]=ind;
	}
}

vector<int> maxdeg[100048];
int sufmax[100048];

int tt=0;
inline void bfs(int root)
{
	++tt;
	q.push(node{root,int(v[root].size())-1,2});int i,y,curdepth=1;
	while (!q.empty())
	{
		++curdepth;int maxdegree=0;
		while (!q.empty() && q.front().depth==curdepth)
		{
			maxdegree=max(maxdegree,q.front().d);
			depth[q.front().ind]=curdepth;
			for (i=0;i<int(v[q.front().ind].size());i++)
			{
				y=v[q.front().ind][i];
				if (!depth[y]) q.push(node{y,int(v[y].size())-1,curdepth+1});
			}
			q.pop();
		}
		check_max(maxdegree,tt,curdepth);
		maxdeg[tt].pb(maxdegree);
	}
}

inline int getmax(int d,int ind) {return fmind[d]==ind?sm[d]:fm[d];}

inline void solve2(int buttom)
{
	int i;
	dtot=0;for (int cur=buttom;cur!=-1;cur=fa[cur]) dia[++dtot]=cur;
	for (i=1;i<=n;i++) vv[i]=v[i];LL ans=LINF,cnt;
	ans=min(ans,solve(dia[dtot/2+1]));
	tot=n;for (i=1;i<=n;i++) v[i]=vv[i];
	memset(depth,0,sizeof(depth));
	memset(fm,0,sizeof(fm));memset(sm,0,sizeof(sm));
	int rt=dia[dtot/2+1];depth[rt]=1;
	for (i=0;i<int(v[rt].size());i++) bfs(v[rt][i]);
	fm[1]=int(v[rt].size())-1;fmind[1]=0;
	sufmax[n+10]=1;
	for (i=n+9;i>=1;i--)
		sufmax[i]=sufmax[i+1]*(fm[i]+(fm[i]?0:1));
	for (int cur=1;cur<=tt;cur++)
	{
		LL lnum=1;
		for (i=0;i<int(maxdeg[cur].size());i++)
		{
			int other=getmax(i+1,cur);other=max(other,maxdeg[cur][i]);
			if (!other) other++;
			lnum*=other;
		}
		int other=getmax(i+1,cur);if (!other) other++;lnum*=other;
		lnum*=sufmax[i+2];
		ans=min(ans,lnum*2);
	}
	printf("%lld\n",ans);
}

int main ()
{
	int i,x,y,maxdepth,maxind;
	n=getint();tot=n;
	for (i=1;i<=n-1;i++) x=getint(),y=getint(),v[x].pb(y),v[y].pb(x);
	depth[1]=1;dfs(1,-1);
	maxdepth=-1;for (i=1;i<=n;i++) if (depth[i]>maxdepth) maxdepth=depth[i],maxind=i;
	depth[maxind]=1;dfs(maxind,-1);
	maxdepth=-1;for (i=1;i<=n;i++) if (depth[i]>maxdepth) maxdepth=depth[i],maxind=i;
	memset(visited,false,sizeof(visited));
	if (maxdepth%2==0) printf("%d ",maxdepth/2),solve1(maxind); else printf("%d ",maxdepth/2+1),solve2(maxind);
	int cnt=0;for (i=1;i<=tot;i++) if (int(v[i].size())==1) cnt++;
	return 0;
}
