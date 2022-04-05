#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

int n,m;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

namespace flow
{
	const int MAXN=1e5;
	int head[MAXN+48],cur[MAXN+48],nxt[MAXN+48],to[MAXN+48],f[MAXN+48],tot=1,t;
	inline void init(int _t) {t=_t;tot=1;memset(head,0,sizeof(head));}
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	int Head,Tail,q[MAXN+48],depth[MAXN+48];
	inline bool bfs()
	{
		for (register int i=0;i<=t;i++) depth[i]=-1;
		depth[0]=0;Head=Tail=1;q[1]=0;
		while (Head<=Tail)
		{
			int x=q[Head++];
			for (register int i=head[x];i;i=nxt[i])
			{
				int y=to[i];
				if (depth[y]==-1 && f[i])
				{
					depth[y]=depth[x]+1;
					q[++Tail]=y;
				}
			}
		}
		return depth[t]!=-1;
	}
	inline int dfs(int x,int maxf)
	{
		if (x==t) return maxf;
		int y,minf,now,ans=0;
		for (register int &i=cur[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);
				now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
			}
		}
		if (!ans) depth[x]=0;
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
}

class SurroundingGame
{
	inline int getind(int x,int y,int op) {return (x-1)*m+y+op*n*m;}
	inline int getval(char ch)
	{
		if (isdigit(ch)) return ch-'0';
		if (islower(ch)) return ch-'a'+10;
		return ch-'A'+36;
	}
	public:
		inline int maxScore(vector<string> cost,vector<string> benefits)
		{
			n=int(cost.size());m=int(cost[0].size());
			flow::init(n*m*2+1);int ans=0;
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
				{
					int B=getval(benefits[i-1][j-1]),C=getval(cost[i-1][j-1]);
					ans+=B;flow::addedge(getind(i,j,0),getind(i,j,1),B);
					if ((i+j)&1)
					{
						flow::addedge(0,getind(i,j,0),C);
						for (register int dir=0;dir<=3;dir++)
						{
							int x=i+dx[dir],y=j+dy[dir];
							if (1<=x && x<=n && 1<=y && y<=m)
							{
								flow::addedge(getind(i,j,0),getind(x,y,0),INF);
								flow::addedge(getind(i,j,1),getind(x,y,1),INF);
							}
						}
					}
					else
						flow::addedge(getind(i,j,1),flow::t,C);
				}
			return ans-flow::dinic();
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int nn;vector<string> v1,v2;string s;
	SurroundingGame A;
	while (cin>>nn)
	{
		v1.clear();v2.clear();
		for (register int i=1;i<=nn;i++) cin>>s,v1.pb(s);
		for (register int i=1;i<=nn;i++) cin>>s,v2.pb(s);
		cout<<A.maxScore(v1,v2)<<endl;
	}
	return 0;
}
*/
