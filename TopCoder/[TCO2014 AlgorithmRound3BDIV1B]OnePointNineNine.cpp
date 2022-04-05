#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define x first
#define y second
#define LOWBIT(x) ((x) & (-x))
// #define LOCAL true

const int INF=1e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-12;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

int n;
bitset<1048> ga[1048];
bool del[1048],visited[1048];int num[1048],degree[1048];
vector<int> v[1048],vv[1048];
int seq[1048],tot;
int dp[1048][2];

class OnePointNineNine
{
	inline bool check_dist(int x1,int y1,int x2,int y2,int D)
	{
		LL d1=1ll*(x1-x2)*(x1-x2)+1ll*(y1-y2)*(y1-y2);
		long double d2=0.9;d2*=D;d2*=D;
		return d1<=d2;
	}
	inline bool Check_dist(int x1,int y1,int x2,int y2,int D)
	{
		LL d1=1ll*(x1-x2)*(x1-x2)+1ll*(y1-y2)*(y1-y2),d2=1ll*D*D;
		return d1<=d2;
	}
	inline void Clear()
	{
		for (register int i=1;i<=n;i++) ga[i]=0,v[i].clear(),num[i]=0,degree[i]=0,visited[i]=false,del[i]=false,vv[i].clear();
	}
	inline void dfs(int cur,int st,int &Num)
	{
		Num++;visited[cur]=true;if (cur!=st) del[cur]=true;
		for (auto y : vv[cur]) if (!visited[y]) dfs(y,st,Num);
	}
	inline void dfs_line(int cur)
	{
		visited[cur]=true;seq[++tot]=cur;
		for (register int i=0;i<int(v[cur].size());i++)
		{
			int y=v[cur][i];
			if (!visited[y]) dfs_line(y);
		}
	}
	inline int dp_line()
	{
		for (register int i=0;i<=tot;i++) dp[i][0]=dp[i][1]=0;
		dp[0][0]=1;
		for (register int i=1;i<=tot;i++)
		{
			dp[i][1]=1ll*dp[i-1][0]*num[seq[i]]%MOD;
			dp[i][0]=add(dp[i-1][0]+dp[i-1][1]);
		}
		return add(dp[tot][0]+dp[tot][1]);
	}
	inline void dfs_cycle(int cur)
	{
		visited[cur]=true;seq[++tot]=cur;
		for (register int i=0;i<int(v[cur].size());i++)
		{
			int y=v[cur][i];
			if (!visited[y]) dfs_cycle(y);
		}
	}
	inline int dp_cycle()
	{
		for (register int i=0;i<=tot;i++) dp[i][0]=dp[i][1]=0;
		dp[1][0]=1;int res=0;
		for (register int i=2;i<=tot;i++)
		{
			dp[i][1]=1ll*dp[i-1][0]*num[seq[i]]%MOD;
			dp[i][0]=add(dp[i-1][0]+dp[i-1][1]);
		}
		res=add(dp[tot][1]+dp[tot][0]);
		for (register int i=0;i<=tot;i++) dp[i][0]=dp[i][1]=0;
		dp[1][1]=num[seq[1]];
		for (register int i=2;i<=tot;i++)
		{
			dp[i][1]=1ll*dp[i-1][0]*num[seq[i]]%MOD;
			dp[i][0]=add(dp[i-1][0]+dp[i-1][1]);
		}
		Add(res,dp[tot][0]);return res;
	}
	public:
		inline int countSubsets(vector<int> X,vector<int> Y,int D)
		{
			n=int(X.size());Clear();int ans=1;
			for (register int i=0;i<n;i++)
			{
				for (register int j=0;j<n;j++)
				{
					LL d1=1ll*(X[i]-X[j])*(X[i]-X[j])+1ll*(Y[i]-Y[j])*(Y[i]-Y[j]);
					long double d2=D;d2*=D;
					if (d1<=d2) ga[i+1][j+1]=1;
					d2*=0.9;
					if (i!=j && d1<=d2) vv[i+1].pb(j+1);
				}
			}
			for (register int i=1;i<=n;i++) if (!del[i]) dfs(i,i,num[i]);
			memset(visited,false,sizeof(visited));
			for (register int i=1;i<=n;i++)
				if (!del[i])
					for (register int j=1;j<=n;j++)
						if (i!=j && ga[i][j] && !del[j]) degree[i]++,v[i].pb(j);
			for (register int i=1;i<=n;i++) if (!degree[i] && !del[i]) visited[i]=true,ans=1ll*ans*(num[i]+1)%MOD;
			for (register int i=1;i<=n;i++)
				if (degree[i]==1 && !visited[i] && !del[i])
				{
					tot=0;dfs_line(i);
					ans=1ll*ans*dp_line()%MOD;
				}
			for (register int i=1;i<=n;i++)
				if (!visited[i] && degree[i]==2 && !del[i])
				{
					tot=0;dfs_cycle(i);
					ans=1ll*ans*dp_cycle()%MOD;
				}
			return ans;
		}
};

#ifdef LOCAL
int main ()
{
	freopen ("a.in","r",stdin);
	OnePointNineNine A;
	int nn,dd;vector<int> xx,yy;
	while (cin>>nn)
	{
		xx.clear();yy.clear();int x,y;
		for (register int i=1;i<=nn;i++) cin>>x,xx.pb(x);
		for (register int i=1;i<=nn;i++) cin>>y,yy.pb(y);
		cin>>dd;cout<<A.countSubsets(xx,yy,dd)<<endl;
	}
	return 0;
}
#endif
