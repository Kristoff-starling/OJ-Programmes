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
#pragma comment(linker, "/STACK:102400000,102400000")
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

int n,D;

int head[100048],to[200048],nxt[200048],tot;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

int w[100048];LL ans;
int sz[100048],Cnt[100048];
bool taboo[100048];
Pair cdlist[100048],dlist[100048];int cdtot,dtot;

inline void Clear()
{
	memset(head,0,sizeof(head));tot=1;
	memset(taboo,false,sizeof(taboo));
	ans=0;
}

inline void dfs(int cur,int father)
{
	sz[cur]=1;int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y])
		{
			dfs(y,cur);
			sz[cur]+=sz[y];
		}
	}
}

inline int getroot(int cur,int father,int cursz)
{
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y] && sz[y]>cursz/2) return getroot(y,cur,cursz);
	}
	return cur;
}

inline void Dfs(int cur,int father,int minn,int maxn)
{
	if (maxn-minn<=D)
	{
		ans++;
		cdlist[++cdtot]=mp(minn,maxn);
	}
	sz[cur]=1;
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y])
		{
			Dfs(y,cur,min(minn,w[y]),max(maxn,w[y]));
			sz[cur]+=sz[y];
		}
	}
}

inline void merge()
{
	int i;
	for (i=1;i<=cdtot;i++) dlist[++dtot]=cdlist[i];
}

inline int binsearch(int cmp)
{
	int l=1,r=cdtot,mid,res;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (cdlist[mid].x<cmp)
			l=mid+1;
		else
		{
			res=mid;
			r=mid-1;
		}
	}
	return res;
}

inline LL doit()
{
	sort(cdlist+1,cdlist+cdtot+1);
	int left=1,right,i;LL res=0;
	for (i=2;i<=cdtot;i++)
	{
		right=i-1;left=binsearch(cdlist[i].y-D);
		res+=right-left+1;
	}
	return res;
}		

inline void solve(int cur,int cursz)
{
	dfs(cur,-1);int i,y;
	int root=getroot(cur,-1,cursz);
	dtot=0;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!taboo[y])
		{
			cdtot=0;
			Dfs(y,root,min(w[root],w[y]),max(w[root],w[y]));
			Cnt[y]=sz[y];ans=ans-doit();
			merge();
		}
	}
	for (i=1;i<=dtot;i++) cdlist[i]=dlist[i];cdtot=dtot;
	ans+=doit();
	taboo[root]=true;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!taboo[y]) solve(y,Cnt[y]);
	}
}


int main ()
{
	int ca,i,x,y;ca=getint();
	while (ca--)
	{
		Clear();n=getint();D=getint();
		for (i=1;i<=n;i++) w[i]=getint();
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();
			addedge(x,y);
		}
		solve(1,n);
		printf("%lld\n",ans*2);
	}
	return 0;
}
