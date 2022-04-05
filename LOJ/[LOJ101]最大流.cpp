#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,Ll>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))
#define rep(i,a,b) for (register int i=a;i<=b;i++)
#define Rep(i,b,a) for (register int i=b;i>=a;i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar())) {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=1e5;

int n,m,s,t;

namespace flow
{
	int head[MAXN+48],cur[MAXN+48],to[MAXN+48],nxt[MAXN+48],tot;LL f[MAXN+48];
	int depth[MAXN+48],q[MAXN+48],Head,Tail;
	inline void init() {tot=1;}
	inline void addedge(int s,int t,int cap)
	{
		to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
		to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
	}
	inline bool bfs()
	{
		rep(i,1,n) depth[i]=-1;depth[s]=0;Head=Tail=1;q[1]=s;
		while (Head<=Tail)
		{
			int x=q[Head++];
			for (register int i=head[x];i;i=nxt[i])
			{
				int y=to[i];
				if (depth[y]==-1 && f[i]) depth[y]=depth[x]+1,q[++Tail]=y;
			}
		}
		if (depth[t]==-1) return false; else return true;
	}
	inline LL dfs(int x,int maxf)
	{
		if (x==t) return maxf;
		LL y,minf,now,ans=0;
		for (register int &i=cur[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==depth[x]+1 && f[i])
			{
				minf=min(maxf-ans,f[i]);now=dfs(y,minf);
				f[i]-=now;f[i^1]+=now;ans+=now;
			}
			if (ans>=maxf) break;
		}
		return ans;
	}
	inline LL dinic()
	{
		LL ans=0;
		while (bfs())
		{
			rep(i,1,n) cur[i]=head[i];
			ans+=dfs(s,INF);
		}
		return ans;
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	double T=clock();
	cerr<<"Running..."<<endl;
#endif
	flow::init();
	Get(n,m,s,t);int x,y,c;
	rep(i,1,m) Get(x,y,c),flow::addedge(x,y,c);
	printf("%lld\n",flow::dinic());
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
