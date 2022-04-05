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

const int MAXN=2e5;

int n,k;

namespace BIT
{
	int c[MAXN+48];int history[MAXN*20+48],htot;
	inline void init() {htot=0;}
	inline void modify(int x,int delta) {while (x<=k) c[x]+=delta,history[++htot]=x,x+=LOWBIT(x);}
	inline int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
	inline void undo() {rep(i,1,htot) c[history[i]]=0;}
}

struct node
{
	int a,b,c,ind,cnt;
	node () {}
	inline node(int _a,int _b,int _c,int _ind,int _cnt) {a=_a;b=_b;c=_c;ind=_ind;cnt=_cnt;}
	inline bool operator < (const node &other) const
	{
		if (a!=other.a) return a<other.a;
		if (b!=other.b) return b<other.b;
		if (c!=other.c) return c<other.c;
		assert(false);
	}
}a[MAXN+48],tmp1[MAXN+48],tmp2[MAXN+48];int tot;
int ans[MAXN+48],cnt[MAXN+48];

map<pair<pair<int,int>,int>,int> Mp;

inline bool cmpy(node x,node y) {if (x.b!=y.b) return x.b<y.b; return x.c<y.c;}

inline void cdq(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;cdq(l,mid);
	int tot1=mid-l+1,tot2=r-mid;
	rep(i,1,tot1) tmp1[i]=a[l+i-1];rep(i,1,tot2) tmp2[i]=a[mid+i];
	sort(tmp1+1,tmp1+tot1+1,cmpy);sort(tmp2+1,tmp2+tot2+1,cmpy);BIT::init();
	for (register int k1=1,k2=1;k2<=tot2;)
	{
		if (k1<=tot1 && tmp1[k1].b<=tmp2[k2].b) BIT::modify(tmp1[k1].c,tmp1[k1].cnt),k1++;
		else ans[tmp2[k2].ind]+=BIT::query(tmp2[k2].c),k2++;
	}
	BIT::undo();cdq(mid+1,r);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n,k);int x,y,z;
	rep(i,1,n)
	{
		Get(x,y,z);if (Mp.find(mp(mp(x,y),z))!=Mp.end()) {a[Mp[mp(mp(x,y),z)]].cnt++;continue;}
		Mp[mp(mp(x,y),z)]=++tot;a[tot]=node(x,y,z,0,1);
	}
	sort(a+1,a+tot+1);rep(i,1,tot) a[i].ind=i;cdq(1,tot);
	rep(i,1,tot) cnt[ans[i]+a[i].cnt-1]+=a[i].cnt;
	rep(i,0,n-1) printf("%d\n",cnt[i]);
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
