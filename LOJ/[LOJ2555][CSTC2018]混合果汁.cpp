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

const int MAXN=1e5;

int n,m;

struct juice
{
	int d,p,l;
	inline void input() {Get(d,p,l);}
	inline bool operator < (const juice &other) {return d>other.d;}
}a[MAXN+48];

int root[MAXN+48];
namespace SegmentTree
{
	int tot,lson[MAXN*20+48],rson[MAXN*20+48];LL psum[MAXN*20+48],lsum[MAXN*20+48];
	inline int Create() {++tot;lson[tot]=rson[tot]=psum[tot]=lsum[tot]=0;return tot;}
	inline void init() {tot=0;psum[0]=lsum[0]=lson[0]=rson[0]=0;root[0]=Create();}
	inline void pushup(int cur) {psum[cur]=psum[lson[cur]]+psum[rson[cur]];lsum[cur]=lsum[lson[cur]]+lsum[rson[cur]];}
	inline void insert(int cur,int last,int curp,int curl,int l,int r)
	{
		lson[cur]=lson[last];rson[cur]=rson[last];psum[cur]=psum[last];lsum[cur]=lsum[last];int mid=(l+r)>>1;
		if (l==r) {psum[cur]+=1ll*curp*curl;lsum[cur]+=curl;return;}
		if (curp<=mid) lson[cur]=Create(),insert(lson[cur],lson[last],curp,curl,l,mid); else rson[cur]=Create(),insert(rson[cur],rson[last],curp,curl,mid+1,r);
		pushup(cur);
	}
	inline bool query(int cur,LL G,LL L,int l,int r)
	{
		if (l==r) return (lsum[cur]>=L && L*l<=G);
		int mid=(l+r)>>1;
		if (lsum[lson[cur]]>=L) return query(lson[cur],G,L,l,mid);
		else
		{
			if (psum[lson[cur]]>G) return false;
			return query(rson[cur],G-psum[lson[cur]],L-lsum[lson[cur]],mid+1,r);
		}
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
	Get(n,m);rep(i,1,n) a[i].input();sort(a+1,a+n+1);int l,r,mid,ans;LL G,L;
	SegmentTree::init();rep(i,1,n) root[i]=SegmentTree::Create(),SegmentTree::insert(root[i],root[i-1],a[i].p,a[i].l,1,MAXN);
	while (m--)
	{
		Get(G,L);l=1;r=n;ans=-1;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (SegmentTree::query(root[mid],G,L,1,MAXN)) ans=a[mid].d,r=mid-1; else l=mid+1;
		}
		printf("%d\n",ans);
	}
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}


