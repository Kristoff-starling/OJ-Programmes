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

const int MAXN=4e5;

int n,k;
char ga[148][148];

int head[MAXN+48],cur[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],tot=1,t;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int q[MAXN+48],Head,Tail,depth[MAXN+48];
inline bool bfs()
{
	int i,x,y;
	for (i=0;i<=t;i++) depth[i]=-1;
	depth[0]=0;q[1]=0;Head=Tail=1;
	while (Head<=Tail)
	{
		x=q[Head++];
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (f[i] && depth[y]==-1)
			{
				depth[y]=depth[x]+1;
				q[++Tail]=y;
			}
		}
	}
	if (depth[t]==-1) return false; else return true;
}

inline int dfs(int x,int maxf)
{
	if (x==t) return maxf;
	int y,now,minf,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
	}
	return ans;
}

inline int dinic()
{
	int res=0;
	while (bfs())
	{
		for (register int i=0;i<=t;i++) cur[i]=head[i];
		res+=dfs(0,INF);
	}
	return res;
}

int main ()
{
	int i,j;n=getint();k=getint();t=n*6+1;
	for (i=1;i<=n;i++) scanf("%s",ga[i]+1);
	for (i=1;i<=n;i++) addedge(i,n+i,INF),addedge(i,n*2+i,k);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (ga[i][j]=='Y') addedge(n+i,n*3+j,1); else addedge(n*2+i,n*4+j,1);
	for (i=1;i<=n;i++) addedge(n*3+i,n*5+i,INF),addedge(n*4+i,n*5+i,k);
	int ans=-1,aug;
	do
	{
		++ans;
		for (i=1;i<=n;i++) addedge(0,i,1);
		for (i=1;i<=n;i++) addedge(n*5+i,t,1);
		aug=dinic();
	}
	while (aug==n);
	printf("%d\n",ans);
	return 0;
}
