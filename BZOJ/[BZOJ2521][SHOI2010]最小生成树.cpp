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
#define LOWBIT(x) x & (-x)

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

const int MAXN=1e5;

int n,m,ind;
struct Edge
{
	int x,y,c;
	inline void input() {x=getint();y=getint();c=getint();}
}edge[MAXN+48];

int head[MAXN+48],cur[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],tot=1;
inline void addedge(int s,int t,int cap) {to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;}
int S,T;

int depth[MAXN+48],q[MAXN+48],Head,Tail;
inline bool bfs()
{
	int i,x,y;
	for (i=1;i<=n;i++) depth[i]=-1;
	depth[S]=0;q[1]=S;Head=Tail=1;
	while (Head<=Tail)
	{
		x=q[Head++];
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && f[i])
			{
				depth[y]=depth[x]+1;
				q[++Tail]=y;
			}
		}
	}
	if (depth[T]==-1) return false; else return true;
}

inline int dfs(int x,int maxf)
{
	if (x==T) return maxf;
	int y,minf,now,ans=0;
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
	if (ans==0) depth[x]=0;
	return ans;
}

int main ()
{
	n=getint();m=getint();ind=getint();int i;
	for (i=1;i<=m;i++) edge[i].input();
	for (i=1;i<=m;i++)
	{
		if (i==ind) continue;
		if (edge[i].c<=edge[ind].c)
		{
			addedge(edge[i].x,edge[i].y,edge[ind].c+1-edge[i].c);
			addedge(edge[i].y,edge[i].x,edge[ind].c+1-edge[i].c);
		}
	}
	S=edge[ind].x;T=edge[ind].y;
	int ans=0;
	while (bfs())
	{
		for (i=1;i<=n;i++) cur[i]=head[i];
		ans+=dfs(S,2e9);
	}
	printf("%d\n",ans);
	return 0;
}
