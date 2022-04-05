#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
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
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

const int MAXN=1e5;

int n,d[MAXN+48];
vector<int> v[MAXN+48];

int depth[MAXN+48],level[MAXN+48],son[MAXN+48],top[MAXN+48],fa[MAXN+48];
int anc[MAXN+48][21];

const int p1=1e5+3,p2=1e5+19;
const int m1=19260817,m2=998244353;

LL hsh1[MAXN+48][21],hsh2[MAXN+48][21];
LL pw1[MAXN+48],pw2[MAXN+48];

inline void init_hash()
{
	pw1[0]=pw2[0]=1;
	for (register int i=1;i<=n;i++) pw1[i]=pw1[i-1]*p1%m1,pw2[i]=pw2[i-1]*p2%m2;
}

int seq[MAXN+48],pos[MAXN+48],tot;
vector<int> Anc[MAXN+48];int maxbit[MAXN+48];

inline void dfs1(int cur,int father)
{
	son[cur]=0;fa[cur]=father;anc[cur][0]=father;
	depth[cur]=depth[father]+1;level[cur]=depth[cur];
	hsh1[cur][0]=hsh2[cur][0]=d[cur];
	for (register int i=1;i<=17;i++)
	{
		anc[cur][i]=anc[anc[cur][i-1]][i-1];
		hsh1[cur][i]=(hsh1[cur][i-1]*pw1[1<<(i-1)]%m1+hsh1[anc[cur][i-1]][i-1])%m1;
		hsh2[cur][i]=(hsh2[cur][i-1]*pw2[1<<(i-1)]%m2+hsh2[anc[cur][i-1]][i-1])%m2;
	}
	for (auto y : v[cur])
		if (y!=father)
		{
			dfs1(y,cur);
			if (level[y]>level[cur]) son[cur]=y,level[cur]=level[y];	
		}
}

inline void dfs2(int cur,int tp)
{
	top[cur]=tp;seq[++tot]=cur;pos[cur]=tot;
	if (son[cur]) dfs2(son[cur],tp);
	for (auto y : v[cur])
		if (y!=fa[cur] && y!=son[cur]) dfs2(y,y);
}

inline void init_anc()
{
	for (register int i=1;i<=n;i++)
		if (top[i]==i)
		{
			int cur=i,step=min(depth[cur]-1,level[cur]-depth[cur]+1);
			while (step--) cur=fa[cur],Anc[i].pb(cur);
		}
	int pw=1,cnt=0;while (pw<=n) pw<<=1,cnt++;
	for (register int i=n;i>=1;i--)
	{
		while (pw>i) pw>>=1,cnt--;
		maxbit[i]=cnt;
	}
}

inline int find_anc(int x,int k)
{
	int y=anc[x][maxbit[k]],r=k-(1<<maxbit[k]);
	int tp=top[y],delta=depth[y]-depth[tp];
	if (r>delta) return Anc[tp][r-delta-1]; else return seq[pos[tp]+(delta-r)];
}

inline int jump(int x,int k)
{
	for (register int i=17;i>=0;i--)
		if (k>=(1<<i)) x=anc[x][i],k-=(1<<i);
	return x;
}

int lcp[MAXN+48];

namespace SA
{
	int sa[MAXN+48],tmp[MAXN+48],fir[MAXN+48],sec[MAXN+48],cnt[MAXN+48],maxind;
	inline bool compare_sa(int x,int y,int k)
	{
		if (fir[x]!=fir[y]) return fir[x]<fir[y];
		int tmp1=(depth[x]>k?fir[find_anc(x,k)]:-1),tmp2=(depth[y]>k?fir[find_anc(y,k)]:-1);
		return tmp1<tmp2;
	}
	inline void construct_sa()
	{
		maxind=n;memset(cnt,0,(maxind+1)<<2);
		for (register int i=1;i<=n;i++) cnt[d[i]]++;
		for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
		for (register int i=n;i>=1;i--) sa[cnt[d[i]]--]=i;
		fir[sa[1]]=1;for (register int i=2;i<=n;i++) fir[sa[i]]=fir[sa[i-1]]+(d[sa[i]]!=d[sa[i-1]]);
		for (register int len=1;len<=n;len<<=1)
		{
			memset(cnt,0,(maxind+1)<<2);
			for (register int i=1;i<=n;i++) if (depth[i]<=len) cnt[0]++; else cnt[fir[find_anc(i,len)]]++;
			for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
			for (register int i=n;i>=1;i--)
			{
				int pos=((depth[i]<=len)?0:fir[find_anc(i,len)]);
				sec[cnt[pos]--]=i;
			}
			memset(cnt,0,(maxind+1)<<2);
			for (register int i=1;i<=n;i++) cnt[fir[sec[i]]]++;
			for (register int i=1;i<=maxind;i++) cnt[i]+=cnt[i-1];
			for (register int i=n;i>=1;i--) sa[cnt[fir[sec[i]]]--]=sec[i];
			tmp[sa[1]]=1;for (register int i=2;i<=n;i++) tmp[sa[i]]=tmp[sa[i-1]]+compare_sa(sa[i-1],sa[i],len);
			memcpy(fir+1,tmp+1,n<<2);maxind=fir[sa[n]];if (maxind>=n) break;
		}
	}
	inline void construct_lcp()
	{
		for (register int i=1;i<=n-1;i++)
		{
			int x=sa[i],y=sa[i+1],len=min(depth[x],depth[y]),res=0;
			if (d[x]!=d[y]) {lcp[i]=0;continue;}
			for (register int j=17;j>=0;j--)
			{
				if (res+(1<<j)>len) continue;
				if (hsh1[x][j]==hsh1[y][j] && hsh2[x][j]==hsh2[y][j]) res+=(1<<j),x=anc[x][j],y=anc[y][j];
			}
			lcp[i]=res;
		}
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(n);int x,y;
	for (register int i=1;i<=n-1;i++) Get(x,y),v[x].pb(y),v[y].pb(x),d[x]++,d[y]++;
	init_hash();
	dfs1(1,0);dfs2(1,1);init_anc();
	SA::construct_sa();SA::construct_lcp();
	LL ans=0;
	for (register int i=1;i<=n;i++) ans+=depth[i];
	for (register int i=1;i<=n-1;i++) ans-=lcp[i];
	printf("%lld\n",ans);return 0;
}

