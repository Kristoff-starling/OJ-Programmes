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

const int MAXN=3e5;

int n,fa[MAXN+48];vector<int> v[MAXN+48];
int val[MAXN+48];

int vv[MAXN+48],tot;

namespace SegmentTree
{
	int sum[MAXN*20+48],lson[MAXN*20+48],rson[MAXN*20+48],lazy[MAXN*20+48],tot;
	inline void init() {sum[0]=lazy[0]=tot=0;}
	inline int Create() {++tot;lson[tot]=rson[tot]=sum[tot]=0;lazy[tot]=1;return tot;}
	inline void pushdown(int cur)
	{
		Mul(lazy[lson[cur]],lazy[cur]);Mul(sum[lson[cur]],lazy[cur]);
		Mul(lazy[rson[cur]],lazy[cur]);Mul(sum[rson[cur]],lazy[cur]);
		lazy[cur]=1;
	}
	inline void pushup(int cur) {sum[cur]=add(sum[lson[cur]]+sum[rson[cur]]);}
	inline void insert(int &cur,int pos,int vv,int l,int r)
	{
		if (!cur) cur=Create();
		if (l==r) {sum[cur]=vv;return;}
		int mid=(l+r)>>1;
		if (pos<=mid) insert(lson[cur],pos,vv,l,mid); else insert(rson[cur],pos,vv,mid+1,r);
		pushup(cur);
	}
	inline int merge(int root1,int root2,int sum1,int sum2,int p)
	{
		if (!root1 && !root2) return 0;
		if (!root2)
		{
			int w=add(sub(sum2-mul(mul(2,p),sum2))+p);
			Mul(lazy[root1],w);Mul(sum[root1],w);
			return root1;
		}
		if (!root1)
		{
			int w=add(sub(sum1-mul(mul(2,p),sum1))+p);
			Mul(lazy[root2],w);Mul(sum[root2],w);
			return root2;
		}
		pushdown(root1);pushdown(root2);
		lson[root1]=merge(lson[root1],lson[root2],add(sum1+sum[rson[root1]]),add(sum2+sum[rson[root2]]),p);
		rson[root1]=merge(rson[root1],rson[root2],sum1,sum2,p);
		pushup(root1);return root1;
	}
	inline int solve(int cur,int l,int r)
	{
		if (l==r) return mul(mul(l,vv[l]),mul(sum[cur],sum[cur]));
		pushdown(cur);int mid=(l+r)>>1;
		return add(solve(lson[cur],l,mid)+solve(rson[cur],mid+1,r));
	}
}

int root[MAXN+48];
inline void dfs(int cur)
{
	if (!int(v[cur].size()))
	{
		SegmentTree::insert(root[cur],val[cur],1,1,tot);
		return;
	}
	if (int(v[cur].size())==1)
	{
		int y=v[cur][0];dfs(y);
		root[cur]=root[y];
		return;
	}
	int y1=v[cur][0],y2=v[cur][1];
	dfs(y1);dfs(y2);root[cur]=SegmentTree::merge(root[y1],root[y2],0,0,val[cur]);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n);rep(i,1,n) Get(fa[i]),v[fa[i]].pb(i);
	SegmentTree::init();
	int Inv=quick_pow(10000,MOD-2);
	rep(i,1,n) {Get(val[i]);if (int(v[i].size())) val[i]=1ll*val[i]*Inv%MOD; else vv[++tot]=val[i];}
	sort(vv+1,vv+tot+1);rep(i,1,n) if (!int(v[i].size())) val[i]=lower_bound(vv+1,vv+tot+1,val[i])-vv;
	dfs(1);printf("%d\n",SegmentTree::solve(root[1],1,tot));
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
