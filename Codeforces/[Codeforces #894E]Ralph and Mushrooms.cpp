#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

struct Edge
{
	int ind;
	int to;
	int len;
};

struct EE
{
	int x,y,len;
};

vector<Edge> v[1000048];
struct node
{
	int ind;
	int lowlink;
}a[1000048];

int ss;
int n,e,starter;
EE edgelen[1000048];
stack<pair<bool,int> > s;
bool visited[1000048];
LL sum[2000048],tot=0;
int ind=0;
LL totlen[1000048];
LL dp[1000048];
vector<Pair> vv[1000048];

int pre[1000048];
inline int find_anc(int x)
{
	if (pre[x]!=x) pre[x]=find_anc(pre[x]);
	return pre[x];
}

void tarjan(int cur)
{
	visited[cur]=true;
	a[cur].ind=a[cur].lowlink=++ind;
	int i,to,edge_ind;
	for (i=0;i<v[cur].size();i++)
	{
		to=v[cur][i].to;edge_ind=v[cur][i].ind;
		if (!a[to].ind)
		{
			s.push(mp(true,edge_ind));s.push(mp(false,to));
			tarjan(to);
			a[cur].lowlink=min(a[cur].lowlink,a[to].lowlink);
		}
		else if (visited[to])
		{
			s.push(mp(true,edge_ind));
			a[cur].lowlink=min(a[cur].lowlink,a[to].lowlink);
		}
	}
	if (a[cur].ind==a[cur].lowlink)
	{
		tot++;sum[tot]=0;int v1;
		do
		{
			v1=s.top().y;
			if (s.top().x && (!pre[edgelen[v1].x] || pre[edgelen[v1].x]==tot) && (!pre[edgelen[v1].y] || pre[edgelen[v1].y]==tot)) sum[tot]+=totlen[v1];
			if (!s.top().x) pre[v1]=tot;
			if (!s.top().x) visited[v1]=false;
			if (!s.top().x && v1==starter) ss=tot;
			if (!s.top().x && v1==cur)
			{
				s.pop();break;
			}
			s.pop();
		}
		while (true);
	}
}

LL p[20048];
LL pref[20048];

void init()
{
	int i;
	p[0]=0;
	for (i=1;i<=20000;i++) p[i]=p[i-1]+i;
	pref[0]=0;
	for (i=1;i<=20000;i++) pref[i]=pref[i-1]+p[i];
	int l,r,mid,ans;
	for (i=1;i<=e;i++)
	{
		l=0;r=20000;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (edgelen[i].len>=p[mid])
			{
				ans=mid;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		totlen[i]=edgelen[i].len;
		totlen[i]*=(ans+1);
		totlen[i]-=pref[ans];
	}
}

LL solve(int cur)
{
	if (dp[cur]!=-1) return dp[cur];
	int i;
	dp[cur]=sum[cur];
	LL add=0;
	for (i=0;i<vv[cur].size();i++)
		add=max(add,solve(vv[cur][i].x)+(LL)vv[cur][i].y);
	dp[cur]+=add;
	return dp[cur];
}

int main ()
{
	int i,j,x,y,c;
	n=getint();e=getint();
	Edge ins;
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();c=getint();
		edgelen[i].x=x;edgelen[i].y=y;
		edgelen[i].len=c;
		ins.to=y;ins.len=c;ins.ind=i;
		v[x].pb(ins);
	}
	starter=getint();
	init();
	for (i=1;i<=n;i++)
		if (a[i].ind==0)
		{
			s.push(mp(0,i));
			tarjan(i);
		}
	for (i=1;i<=n;i++)
		for (j=0;j<v[i].size();j++)
		{
			x=i;y=v[i][j].to;
			if (pre[x]!=pre[y]) vv[pre[x]].pb(mp(pre[y],v[i][j].len));
		}
	for (i=1;i<=tot;i++) dp[i]=-1;
	printf("%I64d\n",solve(ss));
	return 0;
}
