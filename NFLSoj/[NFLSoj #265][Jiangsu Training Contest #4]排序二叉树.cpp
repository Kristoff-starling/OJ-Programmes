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

int n,m;
LL ans[MAXN+48];int arr[MAXN+48];

struct node
{
    int val,from;
    node () {}
    inline node (int vv,int ff) {val=vv;from=ff;}
    inline bool operator < (const node &other) const {return val<other.val;}
}b[MAXN+48];int itot;
int table[MAXN+48];

struct Operation
{
    int op,l,r,x,nx;
    inline void input()
    {
        io.Get(op);
        if (op==1) io.Get(l),io.Get(r),io.Get(x);
        else io.Get(l),io.Get(x);
    }
}a[MAXN+48];

int curt;
namespace SegmentTree
{
    int minn[MAXN*4];LL L[MAXN*4],R[MAXN*4];
    inline LL goL(int cur,int l,int r,int t)
    {
        if (l==r) return (t<=minn[cur])?0:table[l];
        int mid=(l+r)>>1;
        if (t<=minn[cur<<1|1]) return goL(cur<<1,l,mid,t); else return L[cur]+goL(cur<<1|1,mid+1,r,t);
    }
    inline LL goR(int cur,int l,int r,int t)
    {
        if (l==r) return (t<=minn[cur])?0:table[l];
        int mid=(l+r)>>1;
        if (t<=minn[cur<<1]) return goR(cur<<1|1,mid+1,r,t); else return R[cur]+goR(cur<<1,l,mid,t);
    }
    inline void pushup(int cur,int l,int r)
    {
        minn[cur]=min(minn[cur<<1],minn[cur<<1|1]);
        int mid=(l+r)>>1;
        L[cur]=goL(cur<<1,l,mid,minn[cur<<1|1]);
        R[cur]=goR(cur<<1|1,mid+1,r,minn[cur<<1]);
    }
    inline void modify(int cur,int pos,int nv,int l,int r)
    {
        if (l==r) {minn[cur]=nv;return;}
        int mid=(l+r)>>1;
        if (pos<=mid) modify(cur<<1,pos,nv,l,mid); else modify(cur<<1|1,pos,nv,mid+1,r);
        pushup(cur,l,r);
    }
    inline LL queryL(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right)
        {
            LL res=goL(cur,l,r,curt);
            check_min(curt,minn[cur]);
            return res;
        }
        int mid=(l+r)>>1;LL res=0;
        if (mid+1<=right) res+=queryL(cur<<1|1,left,right,mid+1,r);
        if (left<=mid) res+=queryL(cur<<1,left,right,l,mid);
        return res;
    }
    inline LL queryR(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right)
        {
            LL res=goR(cur,l,r,curt);
            check_min(curt,minn[cur]);
            return res;
        }
        int mid=(l+r)>>1;LL res=0;
        if (left<=mid) res+=queryR(cur<<1,left,right,l,mid);
        if (mid+1<=right) res+=queryR(cur<<1|1,left,right,mid+1,r);
        return res;
    }
}

vector<Pair> addmark[MAXN+48],delmark[MAXN+48],qu[MAXN+48];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);
    for (register int i=1;i<=m;i++)
    {
        a[i].input();
        b[i]=node(a[i].x,i);
    }
    sort(b+1,b+m+1);itot=0;
    for (register int i=1;i<=m;i++)
    {
        if (i==1 || b[i].val!=b[i-1].val) ++itot;
        a[b[i].from].nx=itot;table[itot]=a[b[i].from].x;
    }
    for (register int i=1;i<=m;i++)
        if (a[i].op==1)
        {
            addmark[a[i].l].pb(mp(a[i].nx,i));
            delmark[a[i].r].pb(mp(a[i].nx,i));
        }
        else
            qu[a[i].l].pb(mp(a[i].nx,i));
    for (register int i=1;i<=itot;i++) SegmentTree::modify(1,i,INF,1,itot),arr[i]=INF;
    memset(ans,-1,sizeof(ans));
    for (register int i=1;i<=n;i++)
    {
        for (register int j=0;j<int(addmark[i].size());j++)
        {
            Pair item=addmark[i][j];
            SegmentTree::modify(1,item.x,item.y,1,itot),arr[item.x]=item.y;
        }
        for (register int j=0;j<int(qu[i].size());j++)
        {
            Pair item=qu[i][j];
            ans[item.y]=0;
            curt=item.y;ans[item.y]+=SegmentTree::queryL(1,1,item.x,1,itot);
            curt=min(item.y,arr[item.x]);ans[item.y]+=SegmentTree::queryR(1,item.x,itot,1,itot);
        }
        for (register int j=0;j<int(delmark[i].size());j++)
        {
            Pair item=delmark[i][j];
            SegmentTree::modify(1,item.x,INF,1,itot),arr[item.x]=INF;
        }
    }
    for (register int i=1;i<=m;i++) if (ans[i]!=-1) printf("%lld\n",ans[i]);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}