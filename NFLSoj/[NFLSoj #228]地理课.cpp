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
#define LOWBIT(x) x & (-x)
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=1e5;

int n,m;
int fans[MAXN+48];

int ans=1;

int inv[MAXN+48];
inline void init_inv()
{
	inv[0]=inv[1]=1;
	for (register int i=2;i<=n;i++)
		inv[i]=MOD-1ll*(MOD/i)*inv[MOD%i]%MOD;
}

namespace DSU
{
	int pre[MAXN+48],sz[MAXN+48];
	int ptx[MAXN*20+48],pty[MAXN*20+48],szx[MAXN*20+48],szy[MAXN*20+48],tot;
	inline void init() {tot=0;for (register int i=1;i<=n;i++) pre[i]=i,sz[i]=1;}
	inline int find_anc(int x) {if (pre[x]==x) return x; return find_anc(pre[x]);}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (sz[x]>sz[y]) swap(x,y);
		++tot;ptx[tot]=x;pty[tot]=y;szx[tot]=sz[x];szy[tot]=sz[y];
		ans=1ll*ans*inv[sz[x]]%MOD;ans=1ll*ans*inv[sz[y]]%MOD;
		pre[x]=y;sz[y]+=sz[x];
		ans=1ll*ans*sz[y]%MOD;
	}
	inline void undo()
	{
		int x=ptx[tot],y=pty[tot];
		ans=1ll*ans*inv[sz[y]]%MOD;
		pre[x]=x;sz[x]=szx[tot];sz[y]=szy[tot];tot--;
		ans=1ll*ans*sz[x]%MOD;ans=1ll*ans*sz[y]%MOD;
	}
}

namespace SegmentTree
{
	vector<Pair> edge[MAXN*4+48];
	inline void init() {for (register int i=1;i<=MAXN*4;i++) edge[i].clear();}
	inline void update(int cur,int left,int right,Pair curedge,int l,int r)
	{
		if (left<=l && r<=right) {edge[cur].pb(curedge);return;}
		int mid=(l+r)>>1;
		if (left<=mid) update(cur<<1,left,right,curedge,l,mid);
		if (mid+1<=right) update(cur<<1|1,left,right,curedge,mid+1,r);
	}
	inline void dfs(int cur,int l,int r)
	{
		int cnt=0;
		for (register int i=0;i<int(edge[cur].size());i++)
			if (!DSU::issame(edge[cur][i].x,edge[cur][i].y))
			{
				cnt++;
				DSU::update(edge[cur][i].x,edge[cur][i].y);
			}
		if (l==r) fans[l]=ans;
		else
		{
			int mid=(l+r)>>1;
			dfs(cur<<1,l,mid);dfs(cur<<1|1,mid+1,r);
		}
		while (cnt--) DSU::undo();
	}
}

map<Pair,int> Mp;

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);int op,x,y;
	SegmentTree::init();DSU::init();Mp.clear();init_inv();
	for (register int i=1;i<=m;i++)
	{
		io.Get(op);io.Get(x);io.Get(y);
		assert(x!=y);
		if (x>y) swap(x,y);
		if (op==1) Mp[mp(x,y)]=i; else SegmentTree::update(1,Mp[mp(x,y)],i-1,mp(x,y),1,m),Mp[mp(x,y)]=0;
	}
	for (map<Pair,int>::iterator iter=Mp.begin();iter!=Mp.end();iter++)
		if (iter->y) SegmentTree::update(1,iter->y,m,iter->x,1,m);
	SegmentTree::dfs(1,1,m);
	for (register int i=1;i<=m;i++) io.Print(fans[i],'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}