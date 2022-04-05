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
int a[MAXN+48];

namespace SegmentTree
{
    LL lazy[MAXN*4],maxn[MAXN*4],minn[MAXN*4],sum[MAXN*4],sz[MAXN*4];
    inline void pushup(int cur)
    {
        maxn[cur]=max(maxn[cur<<1],maxn[cur<<1|1]);
        minn[cur]=min(minn[cur<<1],minn[cur<<1|1]);
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
    }
    inline void pushdown(int cur)
    {
        if (lazy[cur])
        {
            lazy[cur<<1]+=lazy[cur];maxn[cur<<1]+=lazy[cur];minn[cur<<1]+=lazy[cur];sum[cur<<1]+=sz[cur<<1]*lazy[cur];
            lazy[cur<<1|1]+=lazy[cur];maxn[cur<<1|1]+=lazy[cur];minn[cur<<1|1]+=lazy[cur];sum[cur<<1|1]+=sz[cur<<1|1]*lazy[cur];
            lazy[cur]=0;
        }
    }
    inline void build(int cur,int l,int r)
    {
        lazy[cur]=0;sz[cur]=r-l+1;
        if (l==r) {maxn[cur]=minn[cur]=sum[cur]=a[l];return;}
        int mid=(l+r)>>1;
        build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
        pushup(cur);
    }
    inline void modify_add(int cur,int left,int right,int delta,int l,int r)
    {
        if (left<=l && r<=right)
        {
            lazy[cur]+=delta;maxn[cur]+=delta;minn[cur]+=delta;sum[cur]+=sz[cur]*delta;
            return;
        }
        int mid=(l+r)>>1;
        pushdown(cur);
        if (left<=mid) modify_add(cur<<1,left,right,delta,l,mid);
        if (mid+1<=right) modify_add(cur<<1|1,left,right,delta,mid+1,r);
        pushup(cur);
    }
    inline void modify_sqrt(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right)
        {
            if (minn[cur]-(LL)sqrt(minn[cur])==maxn[cur]-(LL)sqrt(maxn[cur]))
            {
                LL delta=minn[cur]-(LL)sqrt(minn[cur]);
                lazy[cur]-=delta;maxn[cur]-=delta;minn[cur]-=delta;sum[cur]-=sz[cur]*delta;
                return;
            }
            else
            {
                int mid=(l+r)>>1;
                pushdown(cur);
                modify_sqrt(cur<<1,left,right,l,mid);
                modify_sqrt(cur<<1|1,left,right,mid+1,r);
                pushup(cur);
                return;
            }
        }
        int mid=(l+r)>>1;
        pushdown(cur);
        if (left<=mid) modify_sqrt(cur<<1,left,right,l,mid);
        if (mid+1<=right) modify_sqrt(cur<<1|1,left,right,mid+1,r);
        pushup(cur);
    }
    inline LL query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return sum[cur];
        int mid=(l+r)>>1;LL res=0;
        pushdown(cur);
        if (left<=mid) res+=query(cur<<1,left,right,l,mid);
        if (mid+1<=right) res+=query(cur<<1|1,left,right,mid+1,r);
        return res;
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
    scanf("%d%d",&n,&m);
    for (register int i=1;i<=n;i++) scanf("%d",a+i);
    SegmentTree::build(1,1,n);int op,l,r,d;
    while (m--)
    {
        scanf("%d%d%d",&op,&l,&r);if (op==1) scanf("%d",&d);
        if (op==1) SegmentTree::modify_add(1,l,r,d,1,n);
        if (op==2) SegmentTree::modify_sqrt(1,l,r,1,n);
        if (op==3) printf("%lld\n",SegmentTree::query(1,l,r,1,n));
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}