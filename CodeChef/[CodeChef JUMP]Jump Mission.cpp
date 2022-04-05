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
const LL LINF=2e18;
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

const int MAXN=6e5;

int n;LL p[MAXN+48],a[MAXN+48],h[MAXN+48];
LL dp[MAXN+48];

inline LL Query(LL k,LL b,LL pos)
{
    if (k>0) return LINF;
    return k*pos+b;
}

namespace LiChaoTree
{
    int lson[MAXN*20+48],rson[MAXN*20+48];LL k[MAXN*20+48],b[MAXN*20+48];int Root,tot;
    inline int Create()
    {
        ++tot;lson[tot]=rson[tot]=0;
        k[tot]=1;b[tot]=0;return tot;
    }
    inline void build() {tot=Root=0;}
    inline void modify(int &cur,LL curk,LL curb,int l,int r)
    {
        if (!cur) cur=Create();
        if (k[cur]>0) {k[cur]=curk;b[cur]=curb;return;}
        if (l==r)
        {
            if (Query(curk,curb,l)<=Query(k[cur],b[cur],l)) k[cur]=curk,b[cur]=curb;
            return;
        }
        int mid=(l+r)>>1;
        if (curk<=k[cur])
        {
            if (Query(curk,curb,mid)<=Query(k[cur],b[cur],mid))
            {
                modify(lson[cur],k[cur],b[cur],l,mid);
                k[cur]=curk;b[cur]=curb;
            }
            else
                modify(rson[cur],curk,curb,mid+1,r);
        }
        else
        {
            if (Query(curk,curb,mid)<=Query(k[cur],b[cur],mid))
            {
                modify(rson[cur],k[cur],b[cur],mid+1,r);
                k[cur]=curk;b[cur]=curb;
            }
            else
                modify(lson[cur],curk,curb,l,mid);
        }
    }
    inline LL query(int cur,int pos,int l,int r)
    {
        if (!cur) return LINF;
        LL res=Query(k[cur],b[cur],pos);
        if (l==r) return res;
        int mid=(l+r)>>1;
        if (pos<=mid) check_min(res,query(lson[cur],pos,l,mid)); else check_min(res,query(rson[cur],pos,mid+1,r));
        return res;
    }
}

int seq[MAXN+48];
inline bool cmp(int x,int y) {return p[x]<p[y];}

inline void solve(int l,int r)
{
    if (l==r) {if (l!=1) dp[l]+=h[l]*h[l]+a[l];return;}
    int mid=(l+r)>>1;solve(l,mid);LiChaoTree::build();
    for (register int i=l;i<=r;i++) seq[i]=i;
    sort(seq+l,seq+mid+1,cmp);sort(seq+mid+1,seq+r+1,cmp);
    int k1,k2;
    for (k1=l,k2=mid+1;k1<=mid && k2<=r;)
    {
        int x=seq[k1],y=seq[k2];
        if (p[x]<p[y]) LiChaoTree::modify(LiChaoTree::Root,h[x]*(-2),h[x]*h[x]+dp[x],1,MAXN),k1++;
        else check_min(dp[y],LiChaoTree::query(LiChaoTree::Root,h[y],1,MAXN)),k2++;
    }
    while (k2<=r)
    {
        int y=seq[k2++];
        check_min(dp[y],LiChaoTree::query(LiChaoTree::Root,h[y],1,MAXN));
    }
    solve(mid+1,r);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d",&n);
    for (register int i=1;i<=n;i++) scanf("%lld",p+i);
    for (register int i=1;i<=n;i++) scanf("%lld",a+i);
    for (register int i=1;i<=n;i++) scanf("%lld",h+i);
    for (register int i=2;i<=n;i++) dp[i]=LINF;dp[1]=a[1];
    solve(1,n);
    printf("%lld\n",dp[n]);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}