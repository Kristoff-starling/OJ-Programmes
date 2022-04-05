#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	char ch;bool f;T res;
	while (!isdigit(ch=getchar()) & ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1000;
const int MAXM=2500;

int n,c,k;
int C0,C1,D0,D1;
int num[MAXN+48];
vector<int> v[MAXN+48];int cnt[MAXN+48],bel[MAXN+48];
int type[MAXN+48];bool spe[MAXN+48];

vector<int> city1,school1,city2;

int dp1[MAXN+48][MAXM+48],dp2[MAXN+48][MAXM+48];
int sum1[MAXM+48],sum2[MAXM+48];
int dp[2][31][MAXM+48][301];

int all;

inline void Clear()
{
	all=0;
	for (register int i=1;i<=n;i++) cnt[i]=0,v[i].clear(),type[i]=-1,spe[i]=false,bel[i]=0;
	city1.clear();city2.clear();school1.clear();
	for (register int i=0;i<=c;i++)
		for (register int j=0;j<=C0;j++)
			dp1[i][j]=0;
	for (register int i=0;i<=n;i++)
		for (register int j=0;j<=D0;j++)
			dp2[i][j]=0;
	for (register int i=0;i<=C0;i++) sum1[i]=0;
	for (register int i=0;i<=D0;i++) sum2[i]=0;
	for (register int op=0;op<=1;op++)
		for (register int i=0;i<=k;i++)
			for (register int j=0;j<=C0;j++)
				for (register int m=0;m<=i*10;m++)
					dp[op][i][j][m]=0;
}

inline void doit_dp1()
{
	dp1[0][0]=1;
	int numc=int(city1.size());
	for (register int i=0;i<numc;i++)
	{
		int cur=city1[i];
		for (register int j=0;j<=C0;j++)
			if (dp1[i][j])
			{
				if (cnt[cur] && j+cnt[cur]<=C0) Add(dp1[i+1][j+cnt[cur]],dp1[i][j]);
				Add(dp1[i+1][j],dp1[i][j]);
			}
	}
	sum1[0]=dp1[numc][0];
	for (register int i=1;i<=C0;i++) sum1[i]=add(sum1[i-1]+dp1[numc][i]);
	dp2[0][0]=1;
	int numn=int(school1.size());
	for (register int i=0;i<numn;i++)
	{
		int cur=school1[i];
		for (register int j=0;j<=D0;j++)
			if (dp2[i][j])
			{
				if (j+num[cur]<=D0) Add(dp2[i+1][j+num[cur]],dp2[i][j]);
				Add(dp2[i+1][j],dp2[i][j]);
			}
	}
	sum2[0]=dp2[numn][0];
	for (register int i=1;i<=D0;i++) sum2[i]=add(sum2[i-1]+dp2[numn][i]);
}

inline int query1(int l,int r)
{
	if (l>r) return 0;
	l=max(l,0);
	return sub(sum1[r]-((l==0)?0:sum1[l-1]));
}

inline int query2(int l,int r)
{
	if (l>r) return 0;
	l=max(l,0);
	return sub(sum2[r]-((l==0)?0:sum2[l-1]));
}

int seq[MAXN+48],block[MAXN+48],tot;

inline void doit_dp2()
{
	dp[0][0][0][0]=1;
	for (register int i=0;i<tot;i++)
		for (register int j=0;j<=C0;j++)
			for (register int m=0;m<=300;m++)
			{
				if (dp[0][i][j][m])
				{
					if (block[i+1]==block[i])
					{
						if (type[seq[i+1]]!=0) Add(dp[0][i+1][j][m+num[seq[i+1]]],dp[0][i][j][m]);
						if (type[seq[i+1]]!=1) Add(dp[0][i+1][j][m],dp[0][i][j][m]);
					}
					else
					{
						if (j+cnt[block[i+1]]<=C0)
						{
							if (type[seq[i+1]]!=0) Add(dp[0][i+1][j+cnt[block[i+1]]][m+num[seq[i+1]]],dp[0][i][j][m]);
							if (type[seq[i+1]]!=1) Add(dp[0][i+1][j+cnt[block[i+1]]][m],dp[0][i][j][m]);
						}
						if (type[seq[i+1]]!=2) Add(dp[1][i+1][j][m+num[seq[i+1]]],dp[0][i][j][m]);
						if (type[seq[i+1]]!=3) Add(dp[1][i+1][j][m],dp[0][i][j][m]);
					}
				}
				if (dp[1][i][j][m])
				{
					if (block[i+1]==block[i])
					{
						if (type[seq[i+1]]!=2) Add(dp[1][i+1][j][m+num[seq[i+1]]],dp[1][i][j][m]);
						if (type[seq[i+1]]!=3) Add(dp[1][i+1][j][m],dp[1][i][j][m]);
					}
					else
					{
						if (j+cnt[block[i+1]]<=C0)
						{
							if (type[seq[i+1]]!=0) Add(dp[0][i+1][j+cnt[block[i+1]]][m+num[seq[i+1]]],dp[1][i][j][m]);
							if (type[seq[i+1]]!=1) Add(dp[0][i+1][j+cnt[block[i+1]]][m],dp[1][i][j][m]);
						}
						if (type[seq[i+1]]!=2) Add(dp[1][i+1][j][m+num[seq[i+1]]],dp[1][i][j][m]);
						if (type[seq[i+1]]!=3) Add(dp[1][i+1][j][m],dp[1][i][j][m]);
					}
				}
			}
}

inline void solve()
{
	Get(n,c);
	Get(C0,C1,D0,D1);
	Clear();
	int b,s,id;
	for (register int i=1;i<=n;i++)
	{
		Get(b,s);all+=s;
		v[b].pb(i);cnt[b]+=s;
		num[i]=s;bel[i]=b;
	}
	Get(k);
	for (register int i=1;i<=k;i++)
	{
		Get(id);Get(type[id]);
		spe[bel[id]]=true;
	}
	for (register int i=1;i<=c;i++) if (!spe[i]) city1.pb(i); else city2.pb(i);
	for (register int i=1;i<=n;i++) if (type[i]==-1) school1.pb(i);
	doit_dp1();
	tot=0;
	for (register int i=0;i<int(city2.size());i++)
	{
		int curcity=city2[i];
		for (register int j=0;j<int(v[curcity].size());j++)
			if (type[v[curcity][j]]!=-1)
			{
				seq[++tot]=v[curcity][j];
				block[tot]=curcity;
			}
	}
	doit_dp2();
	int ans=0,l,r;
	for (register int op=0;op<=1;op++)
		for (register int j=0;j<=C0;j++)
			for (register int m=0;m<=300;m++)
			{
				int tmpans=dp[op][tot][j][m];
				if (tmpans==0) continue;
				l=all-C1-j;r=C0-j;
				tmpans=1ll*tmpans*query1(l,r)%MOD;
				l=all-D1-m;r=D0-m;
				tmpans=1ll*tmpans*query2(l,r)%MOD;
				Add(ans,tmpans);
			}
	printf("%d\n",ans);
}

int main ()
{
	int ca;Get(ca);
	while (ca--)
	{
		solve();
	}
	return 0;
}
