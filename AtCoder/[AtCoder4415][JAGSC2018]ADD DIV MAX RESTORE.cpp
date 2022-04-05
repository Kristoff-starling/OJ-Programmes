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

const int INF=1e9;
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

const int MAXN=2e5;

int n,q;
int a[MAXN+48];

namespace SegmentTree
{
    struct Tag
    {
        LL a,d,e;
        Tag () {}
        inline void clear() {a=1;d=1;e=0;}
        inline Tag(LL _a,LL _d,LL _e) {a=_a;d=_d;e=_e;}
        inline Tag operator + (LL other) {return Tag(a,d,e+other);}
        inline Tag operator / (LL other)
        {
            LL tmp=d-a+d*e,nd=d*other;
            LL ne=tmp/nd,na=nd-tmp%nd;
            check_min(nd,1ll*INF);check_min(na,1ll*INF);
            return Tag(na,nd,ne);
        }
        inline void merge(Tag other)
        {
            Tag tmp=(*this);
            tmp=(tmp+(other.d-other.a))/other.d+other.e;
            (*this)=tmp;
        }
        inline int getval(int x) {return (x+d-a)/d+e;}
    };
    Tag lazy[MAXN*4];int ori[MAXN*4],maxn[MAXN*4];bool flushed[MAXN*4];
    inline void pushup(int cur)
    {
        maxn[cur]=max(maxn[cur<<1],maxn[cur<<1|1]);
    }
    inline void pushdown(int cur)
    {
        if (flushed[cur])
        {
            flushed[cur<<1]=flushed[cur<<1|1]=true;
            lazy[cur<<1].clear();lazy[cur<<1|1].clear();
            maxn[cur<<1]=ori[cur<<1];maxn[cur<<1|1]=ori[cur<<1|1];
            flushed[cur]=false;
        }
        lazy[cur<<1].merge(lazy[cur]);lazy[cur<<1|1].merge(lazy[cur]);
        maxn[cur<<1]=lazy[cur].getval(maxn[cur<<1]);
        maxn[cur<<1|1]=lazy[cur].getval(maxn[cur<<1|1]);
        lazy[cur].clear();
    }
    inline void build(int cur,int l,int r)
    {
        lazy[cur].clear();flushed[cur]=false;
        if (l!=r)
        {
            int mid=(l+r)>>1;
            build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
            pushup(cur);ori[cur]=maxn[cur];
        }
        else
        {
            maxn[cur]=ori[cur]=a[l];
        }
    }
    inline void modify(int op,int cur,int left,int right,int x,int l,int r)
    {
        if (left<=l && r<=right)
        {
            if (!op) {lazy[cur]=lazy[cur]+x;maxn[cur]+=x;return;}
            if (op==1) {lazy[cur]=lazy[cur]/x;maxn[cur]/=x;return;}
            if (op==3) {flushed[cur]=true;maxn[cur]=ori[cur];lazy[cur].clear();return;}
        }
        pushdown(cur);int mid=(l+r)>>1;
        if (left<=mid) modify(op,cur<<1,left,right,x,l,mid);
        if (mid+1<=right) modify(op,cur<<1|1,left,right,x,mid+1,r);
        pushup(cur);
    }
    inline int query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return maxn[cur];
        pushdown(cur);int mid=(l+r)>>1,res=-1;
        if (left<=mid) check_max(res,query(cur<<1,left,right,l,mid));
        if (mid+1<=right) check_max(res,query(cur<<1|1,left,right,mid+1,r));
        pushup(cur);return res;
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
    scanf("%d%d",&n,&q);
    for (register int i=1;i<=n;i++) scanf("%d",a+i);
    SegmentTree::build(1,1,n);
    int op,l,r,x;
    while (q--)
    {
        scanf("%d%d%d%d",&op,&l,&r,&x);++l;++r;
        if (op!=2) SegmentTree::modify(op,1,l,r,x,1,n); else printf("%d\n",SegmentTree::query(1,l,r,1,n));
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}