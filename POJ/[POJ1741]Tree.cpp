#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define x first
#define y second
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-5;

inline int getint()
{
	bool f;int res;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m,k,ans=0;
int sz[100048];
int dlist[100048],dtot,cdlist[100048],cdtot;
int tmp[100048];
bool taboo[100048];
int Cnt[100048];

int head[100048],to[100048],nxt[100048],f[100048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=cap;
}

inline void Clear()
{
	ans=0;
	tot=1;memset(head,0,sizeof(head));
	memset(taboo,false,sizeof(taboo));
}

inline void dfs(int cur,int father)
{
	int i,y;sz[cur]=1;
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

inline int doit(int cmp)
{
	if (cmp>k) return 0;
	dlist[0]=0;
	int l=0,r=dtot,mid,rr=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (cmp+dlist[mid]<=k)
		{
			rr=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	return rr;
}

inline void Dfs(int cur,int father,int curdepth)
{
	int i,y;
	sz[cur]=1;cdlist[++cdtot]=curdepth;
	if (curdepth<=k) ans++;
	ans+=doit(curdepth);
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !taboo[y])
		{
			Dfs(y,cur,curdepth+f[i]);
			sz[cur]+=sz[y];
		}
	}
}

inline void merge()
{
	int i,pt1,pt2,ttot=0;
	for (pt1=1,pt2=1;!(pt1>dtot && pt2>cdtot);)
	{
		if (pt1>dtot) {tmp[++ttot]=cdlist[pt2++];continue;}
		if (pt2>cdtot) {tmp[++ttot]=dlist[pt1++];continue;}
		if (dlist[pt1]<cdlist[pt2])
			tmp[++ttot]=dlist[pt1++];
		else
			tmp[++ttot]=cdlist[pt2++];
	}
	for (i=1;i<=ttot;i++) dlist[i]=tmp[i];
	dtot=ttot;
}

inline void solve(int cur,int father,int cursz)
{	
	dfs(cur,-1);int i,y;
	int root=getroot(cur,-1,cursz);
	dtot=0;
	int pt=0;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!taboo[y])
		{
			cdtot=0;
			Dfs(y,root,f[i]);
			Cnt[y]=sz[y];
			sort(cdlist+1,cdlist+cdtot+1);
			merge();
		}
	}
	taboo[root]=true;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!taboo[y]) solve(y,cur,Cnt[y]);
	}
}

int main ()
{
	int i,x,y,c;
	while (scanf("%d%d",&n,&k))
	{
		if (!n && !k) break;
		Clear();
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();c=getint();
			addedge(x,y,c);
		}
		solve(1,-1,n);
		printf("%d\n",ans);
	}
	return 0;
}
