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
const LL LINF=4e18;
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

const int MAXM=6e5;

int n,m;

struct node
{
    int op,l,r,nl,nr;LL sta,d;
    inline void input()
    {
        io.Get(op);
        if (op==3) io.Get(l);
        else io.Get(l),io.Get(r),io.Get(d),io.Get(sta);
    }
}a[MAXM+48];

struct Pt
{
    int from,type,val;
    Pt () {}
    inline Pt(int ff,int tt,int vv) {from=ff;type=tt;val=vv;}
    inline bool operator < (const Pt &other) const {return val<other.val;}
}b[MAXM+48];int btot;

int topos[MAXM+48];

inline LL query_val(int id,int pos)
{
    if (!id) return -LINF;
    return a[id].sta+a[id].d*(topos[pos]-a[id].l);
}

namespace SegmentTree
{
    vector<int> ind[MAXM*4];
    inline void update(int cur,int left,int right,int id,int l,int r)
    {
        if (left<=l && r<=right) {ind[cur].pb(id);return;}
        int mid=(l+r)>>1;
        if (left<=mid) update(cur<<1,left,right,id,l,mid);
        if (mid+1<=right) update(cur<<1|1,left,right,id,mid+1,r);
    }
    inline LL query(int cur,int pos,int l,int r)
    {
        if (!cur) return 0;
        int mid=(l+r)>>1;LL res=0;
        for (register int i=0;i<int(ind[cur].size());i++) res+=query_val(ind[cur][i],pos);
        if (l==r) return res;
        if (pos<=mid) res+=query(cur<<1,pos,l,mid); else res+=query(cur<<1|1,pos,mid+1,r);
        return res;
    }
}

namespace LiChaoTree
{
    int maxind[MAXM*4];
    inline void modify(int cur,int id,int l,int r)
    {
        if (l==r)
        {
            if (query_val(id,l)>query_val(maxind[cur],l)) maxind[cur]=id;
            return;
        }
        if (!maxind[cur]) {maxind[cur]=id;return;}
        int mid=(l+r)>>1;
        if (a[id].d>a[maxind[cur]].d)
        {
            if (query_val(id,mid)>=query_val(maxind[cur],mid))
            {
                modify(cur<<1,maxind[cur],l,mid);
                maxind[cur]=id;
            }
            else
                modify(cur<<1|1,id,mid+1,r);
        }
        else
        {
            if (query_val(id,mid)>=query_val(maxind[cur],mid))
            {
                modify(cur<<1|1,maxind[cur],mid+1,r);
                maxind[cur]=id;
            }
            else
                modify(cur<<1,id,l,mid);
        }
    }
    inline void update(int cur,int left,int right,int id,int l,int r)
    {
        int mid=(l+r)>>1;
        if (left<=l && r<=right) {modify(cur,id,l,r);return;}
        if (left<=mid) update(cur<<1,left,right,id,l,mid);
        if (mid+1<=right) update(cur<<1|1,left,right,id,mid+1,r);
    }
    inline LL query(int cur,int pos,int l,int r)
    {
        LL ans=query_val(maxind[cur],pos);
        if (l==r) return ans;
        int mid=(l+r)>>1;
        if (pos<=mid) check_max(ans,query(cur<<1,pos,l,mid)); else check_max(ans,query(cur<<1|1,pos,mid+1,r));
        return ans;
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
    io.Get(n);io.Get(m);
    for (register int i=1;i<=m;i++)
    {
        a[i].input();
        if (a[i].op<3) b[++btot]=Pt(i,0,a[i].l),b[++btot]=Pt(i,1,a[i].r);
        else b[++btot]=Pt(i,0,a[i].l);
    }
    sort(b+1,b+btot+1);int itot=0;
    for (register int i=1;i<=btot;i++)
    {
        if (i==1 || b[i].val!=b[i-1].val) itot++;
        topos[itot]=b[i].val;
        if (!b[i].type) a[b[i].from].nl=itot; else a[b[i].from].nr=itot;
    }
    for (register int i=1;i<=m;i++)
    {
        if (a[i].op==1) LiChaoTree::update(1,a[i].nl,a[i].nr,i,1,itot);
        if (a[i].op==2) SegmentTree::update(1,a[i].nl,a[i].nr,i,1,itot);
        if (a[i].op==3)
        {
            LL res=LiChaoTree::query(1,a[i].nl,1,itot);
            if (res<=-LINF) {printf("NA\n");continue;}
            res+=SegmentTree::query(1,a[i].nl,1,itot);
            printf("%lld\n",res);
        }
    }
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}