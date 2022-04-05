#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define pLL pair<LL,LL>
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
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

// template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}

const int MAXN=3e5;

int n,m,q,h[MAXN+48],vv[MAXN+48],table[MAXN+48];

namespace DSU
{
	int pre[MAXN+48];
	inline void init() {rep(i,1,n) pre[i]=i;}
	inline void Create(int id) {pre[id]=id;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {pre[y]=x;}
}

struct Edge
{
	int x,y,c;
	inline void input() {Get(x);Get(y);Get(c);}
	inline bool operator < (const Edge &other) const {return c<other.c;}
}edge[500048];

int val[MAXN+48],a[MAXN+48],fa[MAXN+48],ind;vector<int> v[MAXN+48];
int in[MAXN+48],out[MAXN+48],seq[MAXN+48],anc[MAXN+48][21],tot;

int root[MAXN+48];
namespace SegmentTree
{
	int cnt[4000048],lson[4000048],rson[4000048],tot;
	inline void init() {lson[0]=rson[0]=cnt[0]=0;}
	inline int Create() {++tot;lson[tot]=rson[tot]=cnt[tot]=0;return tot;}
	inline void build() {root[0]=Create();}
	inline void pushup(int cur) {cnt[cur]=cnt[lson[cur]]+cnt[rson[cur]];}
	inline void insert(int cur,int last,int pos,int l,int r)
	{
		lson[cur]=lson[last];rson[cur]=rson[last];cnt[cur]=cnt[last];
		if (l==r) {cnt[cur]++;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) lson[cur]=Create(),insert(lson[cur],lson[last],pos,l,mid);
		else rson[cur]=Create(),insert(rson[cur],rson[last],pos,mid+1,r);
		pushup(cur);
	}
	inline int query(int cur,int last,int k,int l,int r)
	{
		if (l==r) return l;
		int mid=(l+r)>>1,cmp=cnt[rson[cur]]-cnt[rson[last]];
		if (k<=cmp) return query(rson[cur],rson[last],k,mid+1,r); else return query(lson[cur],lson[last],k-cmp,l,mid);
	}
}

inline void ex_kruskal()
{
	DSU::init();sort(edge+1,edge+m+1);ind=n;
	rep(i,1,n) val[i]=0,a[i]=h[i];
	for (register int i=1,cnt=0;i<=m && cnt<n-1;i++)
	{
		int x=edge[i].x,y=edge[i].y;x=DSU::find_anc(x);y=DSU::find_anc(y);
		if (x==y) continue;
		DSU::Create(++ind);DSU::update(ind,x);DSU::update(ind,y);
		v[ind].pb(x);v[ind].pb(y);fa[x]=ind;fa[y]=ind;val[ind]=edge[i].c;a[ind]=0;cnt++;
	}
}

inline void dfs(int cur)
{
	in[cur]=++tot;seq[tot]=cur;
	for (register int i=0;i<int(v[cur].size());i++)
	{
		int y=v[cur][i];
		anc[y][0]=cur;rep(i,1,20) anc[y][i]=anc[anc[y][i-1]][i-1];
		dfs(y);
	}
	out[cur]=tot;
}

inline int jump(int cur,int lim)
{
	Rep(i,20,0) if (anc[cur][i] && val[anc[cur][i]]<=lim) cur=anc[cur][i];
	return cur;
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	double T=clock();
	cerr<<"Running..."<<endl;
#endif
	Get(n);Get(m);Get(q);rep(i,1,n) Get(h[i]);rep(i,1,m) edge[i].input();
	memcpy(vv+1,h+1,n<<2);int t=n;sort(vv+1,vv+t+1);t=unique(vv+1,vv+t+1)-(vv+1);
	table[0]=-1;rep(i,1,n) {int pos=lower_bound(vv+1,vv+t+1,h[i])-vv;table[pos]=h[i];h[i]=pos;}
	ex_kruskal();rep(i,1,ind) if (!fa[i]) dfs(i);SegmentTree::build();
	rep(i,1,tot) root[i]=SegmentTree::Create(),SegmentTree::insert(root[i],root[i-1],a[seq[i]],0,t);
	int lastans=0,x,lim,k;
	while (q--)
	{
		Get(x);Get(lim);Get(k);if (lastans!=-1) x^=lastans,lim^=lastans,k^=lastans;
		int rt=jump(x,lim),ans=SegmentTree::query(root[out[rt]],root[in[rt]-1],k,0,t);
		ans=table[ans];printf("%d\n",ans);lastans=ans;
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-T)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
