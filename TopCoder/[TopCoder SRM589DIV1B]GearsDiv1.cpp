#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
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

int n;
Pair edge[10048];int tot;
char col[148];
int table[148];

namespace dinic
{
	const int MAXN=2e5;
	int head[MAXN+48],cur[MAXN+48],to[MAXN+48],nxt[MAXN+48],f[MAXN+48],tot=1,t;
	inline void init (int mm) {for (register int i=0;i<=t;i++) head[i]=0;tot=1;t=mm;}
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	int q[MAXN+48],Head,Tail;int depth[MAXN+48];
	inline bool bfs()
	{
		int i,x,y;
		for (i=0;i<=t;i++) depth[i]=-1;depth[0]=0;
		Head=Tail=1;q[1]=0;
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
		if (depth[t]==-1) return false; else return true;
	}
	inline int dfs(int x,int maxf)
	{
		if (x==t) return maxf;
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
		return ans;
	}
	inline int flow()
	{
		int res=0;
		while (bfs())
		{
			memcpy(cur,head,(t+1)*sizeof(int));
			res+=dfs(0,INF);
		}
		return res;
	}
}

int ind[148],itot;
inline int solve(int u)
{
	itot=0;int i,res=0;
	for (i=1;i<=n;i++)
		if (table[col[i]]==u) ind[i]=++itot;
	dinic::init(itot*2+1);
	for (i=1;i<=itot;i++) dinic::addedge(0,i,1);
	for (i=1;i<=itot;i++) dinic::addedge(itot+i,itot*2+1,1);
	for (i=1;i<=tot;i++)
		if (table[col[edge[i].x]]==u && table[col[edge[i].y]]==u)
		{
			dinic::addedge(ind[edge[i].x],itot+ind[edge[i].y],1);
			dinic::addedge(ind[edge[i].y],itot+ind[edge[i].x],1);
		}
	res+=dinic::flow()/2;itot=0;
	for (i=1;i<=n;i++)
		if (table[col[i]]!=u) ind[i]=++itot;
	dinic::init(itot*2+1);
	for (i=1;i<=itot;i++) dinic::addedge(0,i,1);
	for (i=1;i<=itot;i++) dinic::addedge(itot+i,itot*2+1,1);
	for (i=1;i<=tot;i++)
		if (table[col[edge[i].x]]!=u && table[col[edge[i].y]]!=u)
		{
			dinic::addedge(ind[edge[i].x],itot+ind[edge[i].y],1);
			dinic::addedge(ind[edge[i].y],itot+ind[edge[i].x],1);
		}
	res+=dinic::flow()/2;
	return res;
}

class GearsDiv1
{
	public:
		inline int getmin(string color,vector<string> graph)
		{
			int i,j;n=int(graph.size());tot=0;
			for (i=1;i<=n;i++) col[i]=color[i-1];
			for (i=1;i<=n;i++)
				for (j=1;j<=i;j++)
					if (graph[i-1][j-1]=='Y') edge[++tot]=mp(i,j);
			table['R']=1;table['G']=2;table['B']=3;
			int res=INF;
			for (i=1;i<=3;i++) res=min(res,solve(i));
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	string s;int n;
	GearsDiv1 A;vector<string> vv;
	while (cin>>n>>s)
	{
		string ss;
		for (int i=1;i<=n;i++) cin>>ss,vv.pb(ss);
		printf("%d\n",A.getmin(s,vv));
	}
	return 0;
}*/
/*
4
RGBR
NYNN
YNYN
NYNY
NNYN
4
RGBR
NNNN
NNNN
NNNN
NNNN
3
RGB
NYY
YNY
YYN
30
RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG
NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY
NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY
NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY
NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN
NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN
YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN
NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY
NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN
NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY
YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN
NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY
NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN
YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN
NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY
NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY
NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN
YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN
NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN
NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY
NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY
NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY
NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN
NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN
NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY
NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY
YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN
NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN
NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY
YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN
YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN
*/
