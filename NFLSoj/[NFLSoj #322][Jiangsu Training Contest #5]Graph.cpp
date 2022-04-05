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
//#define LOCAL true

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

const int MAXN=5e5;

int n,m,k,q;
int id[MAXN+48],val[MAXN+48],itot;
vector<int> v[MAXN+48];int dtime[MAXN+48];
Pair edge[MAXN+48];int eid[MAXN+48];
int fans[MAXN+48];

LL ans=0;

inline int getanother(int cur,int id) {return cur==edge[id].x?edge[id].y:edge[id].x;}

int root[MAXN+48];
namespace SegmentTree
{
	int lson[MAXN*20+48],rson[MAXN*20+48],cnt[MAXN*20+48],tot;
	inline void init() {tot=0;for (register int i=1;i<=n;i++) root[i]=0;}
	inline int Create() {++tot;lson[tot]=rson[tot]=cnt[tot]=0;return tot;}
	inline void insert(int &cur,int pos,int delta,int l,int r)
	{
		if (!cur) cur=Create();
		if (l==r) {cnt[cur]+=delta;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) insert(lson[cur],pos,delta,l,mid); else insert(rson[cur],pos,delta,mid+1,r);
	}
	inline int merge(int root1,int root2,int l,int r)
	{
		if (!root1 || !root2) return root1^root2;
		if (l==r) {ans+=1ll*cnt[root1]*cnt[root2];cnt[root1]+=cnt[root2];return root1;}
		int mid=(l+r)>>1;
		lson[root1]=merge(lson[root1],lson[root2],l,mid);
		rson[root1]=merge(rson[root1],rson[root2],mid+1,r);
		return root1;
	}
}

int depth[MAXN+48];

namespace DSU
{
	int pre[MAXN+48],top[MAXN+48];
	inline void init()
	{
		SegmentTree::init();ans=0;
		for (register int i=1;i<=n;i++) pre[i]=top[i]=i,SegmentTree::insert(root[i],id[i],1,1,itot);
	}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void merge(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		pre[x]=y;if (depth[top[x]]<depth[top[y]]) top[y]=top[x];
		root[y]=SegmentTree::merge(root[y],root[x],1,itot);
	}
}

inline bool cmp_edge(int x,int y) {return dtime[x]>dtime[y];}

bool intree[MAXN+48];int fa[MAXN+48];
inline void dfs(int cur,int father)
{
	fa[cur]=father;
	for (auto edgeid : v[cur])
		if (intree[edgeid])
		{
			int y=getanother(cur,edgeid);
			if (!depth[y]) depth[y]=depth[cur]+1,dfs(y,cur);
		}
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);io.Get(k);io.Get(q);int x,y;
	for (register int i=1;i<=n;i++) io.Get(id[i]),val[i]=id[i];
	itot=n;sort(val+1,val+itot+1);itot=unique(val+1,val+itot+1)-(val+1);
	for (register int i=1;i<=n;i++) id[i]=lower_bound(val+1,val+itot+1,id[i])-val;
	for (register int i=1;i<=m;i++) io.Get(x),io.Get(y),edge[i]=mp(x,y),v[x].pb(i),v[y].pb(i),dtime[i]=q+1;
	for (register int i=1;i<=q;i++)
	{
		io.Get(x);
		for (auto edgeid : v[x]) check_min(dtime[edgeid],i);
	}
	for (register int i=1;i<=m;i++) eid[i]=i;
	sort(eid+1,eid+m+1,cmp_edge);memset(intree,false,sizeof(intree));
	DSU::init();
	for (register int i=1;i<=m;i++)
	{
		x=edge[eid[i]].x;y=edge[eid[i]].y;
		x=DSU::find_anc(x);y=DSU::find_anc(y);
		if (x==y) continue;
		intree[eid[i]]=true;
		DSU::merge(x,y);
	}
	for (register int i=1;i<=n;i++)
		if (!depth[i]) depth[i]=1,dfs(i,-1);
	DSU::init();int pt=1;
	for (register int i=q;i>=0;i--)
	{
		while (pt<=m && dtime[eid[pt]]>i)
		{
			if (intree[eid[pt]]) {++pt;continue;}
			x=edge[eid[pt]].x;y=edge[eid[pt]].y;
			while (DSU::find_anc(x)!=DSU::find_anc(y))
			{
				x=DSU::top[DSU::find_anc(x)];y=DSU::top[DSU::find_anc(y)];
				if (depth[x]<depth[y]) swap(x,y);
				while (depth[x]>=depth[y] && DSU::find_anc(x)!=DSU::find_anc(y))
				{
					DSU::merge(x,fa[x]);
					x=DSU::top[DSU::find_anc(x)];
				}
			}
			++pt;
		}
		fans[i]=ans;
	}
	for (register int i=0;i<=q;i++) printf("%d\n",fans[i]);
	puts("");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
