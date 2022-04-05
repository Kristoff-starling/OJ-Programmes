//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

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

const int MAXN=2000;

int n,X[MAXN+48],Y[MAXN+48],w[MAXN+48],val[MAXN+48],tot;
vector<Pair> v[MAXN+48];

namespace SegmentTree
{
    LL sum[MAXN*4],lmax[MAXN*4],rmax[MAXN*4],maxn[MAXN*4];
    inline void build(int cur,int l,int r)
    {
        sum[cur]=lmax[cur]=rmax[cur]=maxn[cur]=0;
        if (l==r) return;
        int mid=(l+r)>>1;build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
    }
    inline void pushup(int cur)
    {
        sum[cur]=sum[cur<<1]+sum[cur<<1|1];
        lmax[cur]=max(lmax[cur<<1],sum[cur<<1]+lmax[cur<<1|1]);
        rmax[cur]=max(rmax[cur<<1|1],sum[cur<<1|1]+rmax[cur<<1]);
        maxn[cur]=max(max(maxn[cur<<1],maxn[cur<<1|1]),rmax[cur<<1]+lmax[cur<<1|1]);
    }
    inline void modify(int cur,int pos,int delta,int l,int r)
    {
        if (l==r) {sum[cur]+=delta;lmax[cur]=rmax[cur]=maxn[cur]=max(sum[cur],0ll);return;}
        int mid=(l+r)>>1;
        if (pos<=mid) modify(cur<<1,pos,delta,l,mid); else modify(cur<<1|1,pos,delta,mid+1,r);
        pushup(cur);
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
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d%d%d",X+i,Y+i,w+i);
        tot=n;rep(i,1,n) val[i]=X[i];
        sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
        rep(i,1,n) X[i]=lower_bound(val+1,val+tot+1,X[i])-val;
        tot=n;rep(i,1,n) val[i]=Y[i];
        sort(val+1,val+tot+1);tot=unique(val+1,val+tot+1)-(val+1);
        rep(i,1,n) Y[i]=lower_bound(val+1,val+tot+1,Y[i])-val;
        rep(i,1,n) v[i].clear();rep(i,1,n) v[X[i]].pb(mp(Y[i],w[i]));
        LL ans=0;
        rep(i,1,n)
        {
            SegmentTree::build(1,1,n);
            rep(j,i,n)
            {
                for (auto item : v[j]) SegmentTree::modify(1,item.x,item.y,1,n);
                check_max(ans,SegmentTree::maxn[1]);
            }
        }
        printf("%lld\n",ans);
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}