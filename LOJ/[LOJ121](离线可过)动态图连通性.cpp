// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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
    template<typename T> inline void Get(T &x)
    {
        char ch;bool f;T res;
        while (!isdigit(ch=Getchar()) && ch!='-') {}
        if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
        while (isdigit(ch=Getchar())) res=res*10+ch-'0';
        x=(f?res:(-res));
    }
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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
    template<typename T> inline void Print(T x,char ch)
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
	template<typename T1,typename ...T2> inline void Print(T1 &x,T2 &...y) {Print(x,' ');Print(y...,' ');Writechar('\n');}
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
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=5e5;

int n,m,tot=0;

map<Pair,int> Mp;
int st[MAXN+48],ed[MAXN+48];Pair edge[MAXN+48];
Pair query[MAXN+48];

namespace DSU
{
	int sz[MAXN+48],pre[MAXN+48];
	int sx[MAXN+48],sy[MAXN+48],szx[MAXN+48],stot;
	inline void init() {stot=0;rep(i,1,n) pre[i]=i,sz[i]=1;}
	inline int find_anc(int x) {if (pre[x]==x) return x; else return find_anc(pre[x]);}
	inline bool update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);if (x==y) return false;
		if (sz[x]>sz[y]) swap(x,y);
		sx[++stot]=x;sy[stot]=y;szx[stot]=sz[x];
		pre[x]=y;sz[y]+=sz[x];
		return true;
	}
	inline bool issame(int x,int y) {return find_anc(x)==find_anc(y);}
	inline void undo()
	{
		int x=sx[stot],y=sy[stot];
		pre[x]=x;sz[x]=szx[stot];sz[y]-=szx[stot--];
	}
}

namespace SegmentTree
{
	vector<int> edgeid[MAXN*4];
	inline void insert(int cur,int left,int right,int id,int l,int r)
	{
		if (left<=l && r<=right) {edgeid[cur].pb(id);return;}
		int mid=(l+r)>>1;
		if (left<=mid) insert(cur<<1,left,right,id,l,mid);
		if (mid+1<=right) insert(cur<<1|1,left,right,id,mid+1,r);
	}
	inline void dfs(int cur,int l,int r)
	{
		int mid=(l+r)>>1,cnt=0;
		for (auto id : edgeid[cur])
		{
			int x=edge[id].x,y=edge[id].y;
			if (DSU::update(x,y)) cnt++;
		}
		if (l==r && query[l]!=mp(0,0)) printf(DSU::issame(query[l].x,query[l].y)?"Y\n":"N\n");
		if (l<r) dfs(cur<<1,l,mid),dfs(cur<<1|1,mid+1,r);
		while (cnt--) DSU::undo();
	}
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n,m);int op,x,y;
	rep(i,1,m)
	{
		Get(op,x,y);if (x>y) swap(x,y);
		if (op==2) {query[i]=mp(x,y);continue;}
		if (Mp.find(mp(x,y))!=Mp.end()) ed[Mp[mp(x,y)]]=i,Mp.erase(mp(x,y));
		else edge[++tot]=mp(x,y),st[tot]=i,Mp[mp(x,y)]=tot;
	}
	rep(i,1,tot)
	{
		if (!ed[i]) ed[i]=m;
		SegmentTree::insert(1,st[i],ed[i],i,1,m);
	}
	DSU::init();SegmentTree::dfs(1,1,m);
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
