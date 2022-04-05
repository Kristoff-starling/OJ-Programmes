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

const int MAXN=2e5;

int n,q,ind;
int a[MAXN+48],val[MAXN+48];

namespace SegmentTree
{
    int lson[MAXN*20+48],rson[MAXN*20+48],minn[MAXN*20+48],root[MAXN+48],tot;
    inline int Create() {++tot;lson[tot]=rson[tot]=0;return tot;}
    inline int Create(int last) {++tot;lson[tot]=lson[last];rson[tot]=rson[last];return tot;}
    inline void pushup(int cur) {minn[cur]=min(minn[lson[cur]],minn[rson[cur]]);}
    inline void build(int &cur,int l,int r)
    {
        if (!cur) cur=Create();
        if (l==r) {minn[cur]=-1;return;}
        int mid=(l+r)>>1;
        build(lson[cur],l,mid);build(rson[cur],mid+1,r);
        pushup(cur);
    }
    inline void insert(int last,int &cur,int pos,int nv,int l,int r)
    {
        if (!cur) cur=Create(last);
        if (l==r) {minn[cur]=nv;return;}
        int mid=(l+r)>>1;
        if (pos<=mid) lson[cur]=0,insert(lson[last],lson[cur],pos,nv,l,mid);
        else rson[cur]=0,insert(rson[last],rson[cur],pos,nv,mid+1,r);
        pushup(cur);
    }
    inline int query(int cur,int pos,int l,int r)
    {
        if (l==r) return l;
        int mid=(l+r)>>1;
        if (minn[lson[cur]]>=pos) return query(rson[cur],pos,mid+1,r); else return query(lson[cur],pos,l,mid);
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
    scanf("%d%d",&n,&q);int l,r;
    for (register int i=1;i<=n;i++) scanf("%d",a+i),val[i]=a[i];
    sort(val+1,val+n+1);ind=0;
    for (register int i=1;i<=n;ind++)
    {
        while (i<=n && val[i]<ind) i++;
        if (i>n || val[i]>ind) break;
    }
    SegmentTree::build(SegmentTree::root[0],0,ind);
    for (register int i=1;i<=n;i++)
        if (a[i]>ind) SegmentTree::root[i]=SegmentTree::root[i-1]; else SegmentTree::insert(SegmentTree::root[i-1],SegmentTree::root[i],a[i],i,0,ind);
    while (q--)
    {
        scanf("%d%d",&l,&r);
        printf("%d\n",SegmentTree::query(SegmentTree::root[r],l,0,ind));
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}