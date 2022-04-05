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
const int MOD=1e9+7;
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

const int MAXN=1e6;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

int n;
int fac[MAXN+48],val[MAXN+48],sz[MAXN+48];
int b[MAXN+48];
vector<int> v[MAXN+48];
int pos[MAXN+48];

inline void Clear()
{
	for (register int i=1;i<=n;i++) v[i].clear();
}

inline void calc(int cur,int father)
{
	val[cur]=1;int cnt=0;
	for (auto y : v[cur])
		if (y!=father) calc(y,cur),val[cur]=(1ll*val[cur]*val[y])%MOD,cnt++;
	sz[cur]=cnt;
	val[cur]=(1ll*val[cur]*fac[cnt])%MOD;
}

inline bool cmp(int x,int y) {return pos[x]<pos[y];}

int ans=0;
int step,prefix;

int root[MAXN+48];
namespace SegmentTree
{
	int lson[MAXN*20],rson[MAXN*20],sum[MAXN*20],tot;
	inline void init () {tot=0;}
	inline void clear(int cur) {lson[cur]=rson[cur]=sum[cur]=0;}
	inline void update(int &cur,int pos,int delta,int l,int r)
	{
		if (!cur) cur=++tot,clear(cur);
		if (delta>0) sum[cur]=add(sum[cur]+delta); else sum[cur]=sub(sum[cur]+delta);
		if (l==r) return;
		int mid=(l+r)>>1;if (pos<=mid) update(lson[cur],pos,delta,l,mid); else update(rson[cur],pos,delta,mid+1,r);
	}
	inline int query(int cur,int k,int l,int r)
	{
		if (!cur) return 0;
		if (l==r) return 0;
		int mid=(l+r)>>1;
		if (k<=mid) return query(lson[cur],k,l,mid); else return add(sum[lson[cur]]+query(rson[cur],k,mid+1,r));
	}
}

inline void construct(int cur,int father)
{
	root[cur]=0;
	for (auto y : v[cur])
		if (y!=father)
			SegmentTree::update(root[cur],y,1,1,n),construct(y,cur);
}

inline int dfs(int cur,int father)
{
	++step;
	if (!sz[cur]) return 1;
	int cnt=sz[cur];
	for (auto y : v[cur])
		if (y!=father)
		{
			prefix=(1ll*prefix*quick_pow(fac[cnt],MOD-2))%MOD;
			prefix=(1ll*prefix*fac[--cnt])%MOD;
			ans=add(ans+(1ll*SegmentTree::query(root[cur],b[step+1],1,n)*prefix)%MOD);
			SegmentTree::update(root[cur],y,-1,1,n);
			if (y!=b[step+1]) {--step;return -1;}
			int res=dfs(y,cur);
			if (res==-1) {--step;return -1;}
		}
	return 1;
}

inline void Dfs(int cur,int father,int Pre)
{
	if (cur<b[1])
	{
		if (father==-1) ans=add(ans+val[cur]);
		else ans=add(ans+(((1ll*val[cur]*quick_pow(fac[sz[cur]],MOD-2))%MOD*Pre)%MOD*fac[sz[cur]+1])%MOD);
	}
	for (auto y : v[cur])
		if (y!=father)
			if (father!=-1)
				Dfs(y,cur,((1ll*Pre*val[cur])%MOD*quick_pow(val[y],MOD-2))%MOD);
			else
				Dfs(y,cur,(((1ll*val[cur]*quick_pow(val[y],MOD-2))%MOD*quick_pow(fac[sz[cur]],MOD-2))%MOD*fac[sz[cur]-1])%MOD);
}

int main ()
{
//	freopen ("g.in","r",stdin);
//	freopen ("g.out","w",stdout);
	int ca,i,x,y;ca=getint();
	fac[0]=1;for (i=1;i<=MAXN;i++) fac[i]=(1ll*fac[i-1]*i)%MOD;
	while (ca--)
	{
		n=getint();Clear();
		for (i=1;i<=n;i++) b[i]=getint();
		ans=0;
		for (i=1;i<=n-1;i++)
		{
			x=getint();y=getint();
			v[x].pb(y);v[y].pb(x);
		}
		calc(1,-1);Dfs(1,-1,1);
		calc(b[1],-1);
		for (i=1;i<=n;i++) pos[b[i]]=i;
		for (i=1;i<=n;i++) sort(v[i].begin(),v[i].end(),cmp);
		SegmentTree::init();for (i=1;i<=n;i++) root[i]=0;
		construct(b[1],-1);
		prefix=val[b[1]];step=0;
		dfs(b[1],-1);
		printf("%d\n",ans);
	}
	return 0;
}
