#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

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

const int MAXN=3e5;

int n,m;
vector<Pair> v[MAXN+48];
int sz[MAXN+48],fa[MAXN+48],falen[MAXN+48];
LL a[MAXN+48],tot=0;
LL sum[MAXN+48];
int cnt[MAXN+48];
int b[MAXN+48],tt;
int visited[MAXN+48];
int ff[MAXN+48];
LL M[MAXN+48],mpos[MAXN+48];

inline void dfs(int cur,int father)
{
	sz[cur]=1;
	int i;Pair y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y.x!=father)
			fa[y.x]=cur,falen[y.x]=y.y,dfs(y.x,cur),sz[cur]+=sz[y.x];
	}
}

int main ()
{
	int i,x,y,c;n=getint();m=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();c=getint();
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	dfs(1,-1);int pre=0;
	for (int cur=n;cur!=1;cur=fa[cur])
	{
		a[++tot]=falen[cur];
		cnt[tot]=sz[cur]-1-sz[pre];
		pre=cur;
		visited[cur]=tot;
	}
	visited[1]=tot+1;
	for (i=1;i<=n;i++)
		if (!visited[i] && visited[fa[i]]) ff[visited[fa[i]]]=falen[i];
	cnt[tot+1]=sz[1]-1-sz[pre];
	bool f=false;
	for (i=1;i<=tot+1;i++)
		if (cnt[i]>1) {f=true;break;}
	if (f)
	{
		LL ans=0;
		for (i=1;i<=tot;i++) ans+=a[i];
		while (m--)
		{
			x=getint();
			printf("%I64d\n",ans);
		}
		return 0;
	}
	sum[1]=0;
	for (i=2;i<=tot+1;i++)
		sum[i]=sum[i-1]+a[i-1];
	for (i=1;i<=tot+1;i++)
		sum[i]-=ff[i];
	M[tot+1]=sum[tot+1];
	for (i=tot;i>=1;i--)
		M[i]=min(M[i+1],sum[i]);
	tt=0;
	for (i=1;i<=tot+1;i++)
		if (cnt[i]) b[++tt]=i;
	LL minn=LINF;
	for (i=1;i<=tot-1;i++) minn=min(minn,a[i]+a[i+1]);
	for (i=1;i<=tt;i++)
	{
		if (b[i]!=1)
			minn=min(minn,a[b[i]-1]-ff[b[i]]);
		if (b[i]!=tot+1)
			minn=min(minn,a[b[i]]-ff[b[i]]);
	}
	for (i=1;i<=tt-1;i++)
		minn=min(minn,M[b[i]+1]-(sum[b[i]]+ff[b[i]])-ff[b[i]]);
	LL ans=0;
	for (i=1;i<=tot;i++) ans+=a[i];
	while (m--)
	{
		x=getint();
		if (x>=minn) printf("%I64d\n",ans); else printf("%I64d\n",ans+x-minn);
	}
	return 0;
}
