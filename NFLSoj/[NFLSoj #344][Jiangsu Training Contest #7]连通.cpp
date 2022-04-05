#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return (!y)?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=1e5;

int n,m;
int c[MAXN+48],cnt[MAXN+48],d[MAXN+48];
vector<int> v[MAXN+48];
LL ans;

namespace DSU
{
	namespace SegmentTree
	{
		int lson[MAXN*300],rson[MAXN*300],sum[MAXN*300],tot=0;
		inline int Create() {++tot;lson[tot]=rson[tot]=sum[tot]=0;return tot;}
		inline void insert(int &cur,int val,int l,int r)
		{
			if (!cur) cur=Create();
			if (l==r) {sum[cur]++;return;}
			int mid=(l+r)>>1;
			if (val<=mid) insert(lson[cur],val,l,mid); else insert(rson[cur],val,mid+1,r);
		}
		inline void merge(int root1,int root2,int &root,int l,int r,LL &curans)
		{
			if (!root1 && !root2) return;
			if (!root) root=Create();
			if (!root1 || !root2) {root=(root1^root2);return;}
			if (l==r)
			{
				curans+=1ll*sum[root1]*sum[root2];
				sum[root]=sum[root1]+sum[root2];
				return;
			}
			int mid=(l+r)>>1;
			merge(lson[root1],lson[root2],lson[root],l,mid,curans);
			merge(rson[root1],rson[root2],rson[root],mid+1,r,curans);
		}
	}
	int pre[MAXN+48],rnk[MAXN+48];
	vector<int> root[MAXN+48];
	struct info
	{
		int x,y;LL curans;
		int rx,num;
		info () {}
		inline info (int _x,int _y,LL _curans,int _rx,int _num) {x=_x;y=_y;curans=_curans;rx=_rx;num=_num;}
	};vector<info> ope;
	inline void init()
	{
		for (register int i=1;i<=n;i++)
		{
			pre[i]=i,rnk[i]=1;
			int tmp=0;SegmentTree::insert(tmp,c[i],1,n);
			root[i].pb(tmp);
		}
	}
	inline int find_anc(int x) {while (pre[x]!=x) x=pre[x];return x;}
	inline void merge(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (rnk[x]>rnk[y]) swap(x,y);
		pre[x]=y;int root1=root[x].back(),root2=root[y].back(),cr=0;LL curans=0;
		int ct=SegmentTree::tot;
		SegmentTree::merge(root1,root2,cr,1,n,curans);root[y].pb(cr);
		ans+=curans;ope.pb(info(x,y,curans,rnk[x],SegmentTree::tot-ct));rnk[y]+=rnk[x];
	}
	inline void undo()
	{
		info tmp=ope.back();ope.pop_back();
		int x=tmp.x,y=tmp.y,rx=tmp.rx,num=tmp.num;LL curans=tmp.curans;
		pre[x]=x;rnk[y]-=rx;ans-=curans;root[y].pop_back();
		SegmentTree::tot-=num;
	}
}

LL Ans,fans[MAXN+48];

inline void solve(int l,int r)
{
	if (l==r) {fans[l]=ans;return;}
	int ss=0;for (register int i=l;i<=r;i++) ss+=d[i];
	int mid=(l+r)>>1,cnt=0;
	for (register int i=l;i<=mid;i++)
	{
		for (register int j=0;j<int(v[i].size());j++)
		{
			int to=v[i][j];
			if (((1<=to && to<=i-1) || (r+1<=to && to<=n)) && DSU::find_anc(i)!=DSU::find_anc(to))
				cnt++,DSU::merge(i,to);
		}
	}
	solve(mid+1,r);
	while (cnt--) DSU::undo();
	cnt=0;
	for (register int i=r;i>=mid+1;i--)
	{
		for (register int j=0;j<int(v[i].size());j++)
		{
			int to=v[i][j];
			if (((1<=to && to<=l-1) || (i+1<=to && to<=n)) && (DSU::find_anc(i)!=DSU::find_anc(to)))
				cnt++,DSU::merge(i,to);
		}
	}
	solve(l,mid);
	while (cnt--) DSU::undo();
}

int val[MAXN+48],tot;
inline void doit()
{
	for (register int i=1;i<=n;i++) val[i]=c[i];
	sort(val+1,val+n+1);
	tot=unique(val+1,val+n+1)-(val+1);
	for (register int i=1;i<=n;i++) c[i]=lower_bound(val+1,val+tot+1,c[i])-val;
}

int main ()
{
	scanf("%d%d",&n,&m);int x,y;
	for (register int i=1;i<=n;i++) scanf("%d",c+i);
	doit();
	for (register int i=1;i<=n;i++) cnt[c[i]]++;
	for (register int i=1;i<=n;i++) Ans+=1ll*cnt[i]*(cnt[i]-1)/2;
	for (register int i=1;i<=m;i++) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x),d[x]++,d[y]++;
	DSU::init();solve(1,n);
	for (register int i=1;i<=n;i++) printf("%lld\n",Ans-fans[i]);
	return 0;
}
