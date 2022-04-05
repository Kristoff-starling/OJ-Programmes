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

const int MAXN=8e5;

int n,m,q;
LL sum[MAXN+48];

namespace BIT
{
    LL c[MAXN+48];
    inline void init() {for (register int i=1;i<=n;i++) c[i]=LINF;}
    inline void modify(int x,LL nv) {while (x<=n) check_min(c[x],nv),x+=LOWBIT(x);}
    inline LL query(int x) {LL res=LINF;while (x) check_min(res,c[x]),x^=LOWBIT(x);return res;}
}

struct ele
{
    bool type;int ind;
    int from,to,len;
    ele () {}
    inline ele (bool _t,int _i,int _f,int _to,int _l) {type=_t;ind=_i;from=_f;to=_to;len=_l;}
    inline bool operator < (const ele &other) const
    {
        if (from!=other.from) return from>other.from;
        return type<other.type;
    }
}s[MAXN+48];int tot;

LL ans[MAXN+48];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        int x,y,l;tot=0;
        for (register int i=2;i<=n;i++) scanf("%d",&x),sum[i]=sum[i-1]+x;
        for (register int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&l);
            s[++tot]=ele(false,0,x,y,l);
        }
        scanf("%d",&q);
        for (register int i=1;i<=q;i++) ans[i]=LINF;
        for (register int i=1;i<=q;i++)
        {
            scanf("%d%d",&x,&y);
            if (x<=y) ans[i]=sum[y]-sum[x];
            s[++tot]=ele(true,i,x,y,0);
        }
        sort(s+1,s+tot+1);BIT::init();
        for (register int i=1;i<=tot;i++)
        {
            if (!s[i].type) BIT::modify(s[i].to,sum[s[i].from]-sum[s[i].to]+s[i].len);
            else check_min(ans[s[i].ind],BIT::query(s[i].to)-sum[s[i].from]+sum[s[i].to]);
        }
        for (register int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}