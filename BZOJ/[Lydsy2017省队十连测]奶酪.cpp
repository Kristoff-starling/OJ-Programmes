#include <bits/stdc++.h>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pii pair<double,double>
#define pLL pair<LL,LL>
#define LOWBIT(x) x & (-x)
using namespace std;

const LL MOD=2333333333333333LL;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
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

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

LL Dp[4000048][4];
LL dp[4000048][4];
LL dp2[4000048];
LL DP[4000048];

vector<pair<Pair,int> > v[4000048];
int n;

inline void update(LL val,int cur)
{
	int i;
	if (val>=dp[cur][1])
	{
		dp[cur][3]=dp[cur][2];dp[cur][2]=dp[cur][1];
		dp[cur][1]=val;
		return;
	}
	if (val>=dp[cur][2])
	{
		dp[cur][3]=dp[cur][2];
		dp[cur][2]=val;
		return;
	}
	if (val>=dp[cur][3]) dp[cur][3]=val;
}

inline void Update(LL val,int cur)
{
	int i;
	if (val>=Dp[cur][1])
	{
		Dp[cur][3]=Dp[cur][2];Dp[cur][2]=Dp[cur][1];
		Dp[cur][1]=val;
		return;
	}
	if (val>=Dp[cur][2])
	{
		Dp[cur][3]=Dp[cur][2];
		Dp[cur][2]=val;
		return;
	}
	if (val>=Dp[cur][3]) Dp[cur][3]=val;
}

inline LL Get(int y,int cur,int i)
{
	if (dp[cur][1]==dp[y][1]+v[cur][i].x.y) return dp[cur][2]; else return dp[cur][1];
}

int cnt=0;
inline void dfs(int cur,int father)
{
	if (int(v[cur].size())==1 && father!=-1)
	{
		dp[cur][1]=dp[cur][2]=dp[cur][3]=0;
		Dp[cur][1]=Dp[cur][2]=Dp[cur][3]=0;
		dp2[cur]=0;
		return;
	}
	int i,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x.x;
		if (y!=father)
		{
			dfs(y,cur);
			update(dp[y][1]+v[cur][i].x.y,cur);
			Update(dp2[y],cur);
			dp2[cur]=max(dp2[cur],dp2[y]);
		}
	}
	dp2[cur]=max(dp2[cur],dp[cur][1]+dp[cur][2]);
}

inline LL calc(int cur,int y,int i)
{
	if (dp[cur][1]==dp[y][1]+v[cur][i].x.y) return dp[cur][2]+dp[cur][3];
	if (dp[cur][2]==dp[y][1]+v[cur][i].x.y) return dp[cur][1]+dp[cur][3];
	return dp[cur][1]+dp[cur][2];
}

LL ans=0;
inline LL getans(LL P,LL Q,LL i)
{
	return ((max(P,Q)*23333ll)%MOD+(min(P,Q)*2333ll)%MOD+(i*i*233ll)%MOD+i*23ll+2ll)%MOD;
}

inline LL gg(int y,int cur)
{
	if (dp2[y]==Dp[cur][1]) return Dp[cur][2]; else return Dp[cur][1];
}

inline void Dfs(int cur,int father,LL maxn)
{
	int i,y;LL curmaxn,curans;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x.x;
		if (y==father) continue;
		curmaxn=max(maxn,calc(cur,y,i));
		curans=max(curmaxn,DP[cur]+Get(y,cur,i));
		curans=max(curans,gg(y,cur));
		DP[y]=max(DP[cur]+v[cur][i].x.y,Get(y,cur,i)+v[cur][i].x.y);
		ans=(ans+getans(dp2[y],curans,v[cur][i].y))%MOD;
		Dfs(y,cur,curans);
	}
}

int main ()
{
	freopen ("cheese.in","r",stdin);
	freopen ("cheese.out","w",stdout);
	int i,x,y,c;
	n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();c=getint();
		v[x].pb(mp(mp(y,c),i));v[y].pb(mp(mp(x,c),i));
	}
	DP[1]=0;dfs(1,-1);
	Dfs(1,-1,0);
	printf("%lld\n",ans);
	return 0;
}
