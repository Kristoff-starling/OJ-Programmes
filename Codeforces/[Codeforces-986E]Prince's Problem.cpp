#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
const int maxsqrt=3163;
const int maxcqrt=216;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,q;
int a[100048];
int anc[100048][21],depth[100048];
vector<int> v[100048];

int uplim[100048];
bool isprime[100048];int prime[100048],tot=0;
int cprime[100048],ctot;
inline void sieve()
{
	int i,j;memset(isprime,true,sizeof(isprime));
	for (i=2;i<=maxsqrt;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot && (long long)i*prime[j]<=maxsqrt;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) break;
		}
	}
	for (i=1;i<=tot;i++) if (prime[i]<=maxcqrt) cprime[++ctot]=prime[i];
	for (i=1;i<=23;i++) uplim[i]=int(pow(10000000,1.0/i));
}

int lson[25000048],rson[25000048],num[25000048],Ttot;
int root[100048][70];
struct SegmentTree
{
	/*inline void pushup(int cur)
	{
		sum[cur]=sum[lson[cur]]+sum[rson[cur]];
		num[cur]=num[lson[cur]]+num[rson[cur]];
	}*/
	inline void Insert(int last,int cur,int pos,int l,int r)
	{
		int mid;
		if (!(l<=pos && pos<=r)) return;
		while (l<=r)
		{
			lson[cur]=lson[last];rson[cur]=rson[last];num[cur]=num[last]+1;
			if (l==r) break;
			mid=(l+r)>>1;
			if (pos<=mid)
			{
				lson[cur]=++Ttot;
				last=lson[last];cur=lson[cur];r=mid;
			}
			else
			{
				rson[cur]=++Ttot;
				last=rson[last];cur=rson[cur];l=mid+1;
			}
		}
	}
	//first:sum; second:times
	inline int query(int last,int cur,int k,int l,int r)
	{
		if (!(l<=k && k<=r)) return 0;
		int res=0;int mid;
		while (l<=r)
		{
			if (l==r) return num[cur]-num[last];
			int mid=(l+r)>>1;
			if (k>mid)
				last=rson[last],cur=rson[cur],l=mid+1;
			else
				last=lson[last],cur=lson[cur],r=mid;
		}
		return res;
	}
}A;

int nlist[248];int plist[10],nnlist[10],ptot;
inline void Decompose(int x)
{
	int i;ptot=0;
	for (i=1;i<=tot;i++)
		if (x%prime[i]==0)
		{
			plist[++ptot]=prime[i];nlist[ptot]=0;
			while (x%prime[i]==0) nlist[ptot]++,x/=prime[i];
		}
	if (x!=1) plist[++ptot]=x,nlist[ptot]=1;
}

inline void dfs(int cur,int father)
{
	int i,j,y;
	Decompose(a[cur]);
	for (i=1;i<=23;i++) root[cur][i]=root[father][i];
	for (i=1;i<=ptot;i++)
	{
		int pre=root[cur][nlist[i]];
		root[cur][nlist[i]]=++Ttot;
		A.Insert(pre,root[cur][nlist[i]],plist[i],1,uplim[nlist[i]]);
	}
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		if (y!=father)
		{
			depth[y]=depth[cur]+1;
			anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs(y,cur);
		}
	}
}

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline LL quick_pow(LL x,LL y)
{
	LL res=1;x%=MOD;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

inline int gcd(int x,int y) {return y==0?x:gcd(y,x%y);}

int main ()
{
	int i,j,U,V,x,LCA;n=getint();
	for (i=1;i<=n-1;i++)
	{
		U=getint();V=getint();
		v[U].pb(V);v[V].pb(U);
	}
	for (i=1;i<=n;i++) a[i]=getint();
	sieve();
	for (i=1;i<=23;i++) root[0][i]=++Ttot;
	depth[1]=1;dfs(1,0);
	q=getint();
	LL ans;
	while (q--)
	{
		U=getint();V=getint();x=getint();LCA=getlca(U,V);
		Decompose(x);ans=1;
		for (i=1;i<=ptot;i++)
		{
			int Nn=0;
			for (j=1;j<=23;j++)
			{
				int nn=A.query(root[LCA][j],root[U][j],plist[i],1,uplim[j])+A.query(root[LCA][j],root[V][j],plist[i],1,uplim[j]);
				Nn+=nn*min(j,nlist[i]);
			}
			ans=(ans*quick_pow(plist[i],Nn))%MOD;
		}
		ans=(ans*gcd(x,a[LCA]))%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
