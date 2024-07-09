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

int n,q;
char s[MAXN+48];
int cc[27];

namespace SegmentTree
{
    int cnt[MAXN*4][27],lazy[MAXN*4],sz[MAXN*4];
    inline void pushdown(int cur)
    {
        if (lazy[cur])
        {
            lazy[cur<<1]=lazy[cur];lazy[cur<<1|1]=lazy[cur];
            for (register int i=1;i<=26;i++) cnt[cur<<1][i]=cnt[cur<<1|1][i]=0;
            cnt[cur<<1][lazy[cur]]=sz[cur<<1];cnt[cur<<1|1][lazy[cur]]=sz[cur<<1|1];
            lazy[cur]=0;
        }
    }
    inline void pushup(int cur)
    { 
        for (register int i=1;i<=26;i++)
            cnt[cur][i]=cnt[cur<<1][i]+cnt[cur<<1|1][i];
    }
    inline void build(int cur,int l,int r)
    {
        sz[cur]=r-l+1;lazy[cur]=0;
        if (l==r)
        {
            memset(cnt[cur],0,sizeof(cnt[cur]));
            cnt[cur][s[l]-'a'+1]=1;
        }
        else
        {
            int mid=(l+r)>>1;
            build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
            pushup(cur);
        }
    }
    inline void query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right)
        {
            for (register int i=1;i<=26;i++) cc[i]+=cnt[cur][i];
            return;
        }
        pushdown(cur);
        int mid=(l+r)>>1;
        if (left<=mid) query(cur<<1,left,right,l,mid);
        if (mid+1<=right) query(cur<<1|1,left,right,mid+1,r);
    }
    inline void update(int cur,int left,int right,int nw,int l,int r)
    {
        if (left>right) return;
        if (left<=l && r<=right)
        {
            lazy[cur]=nw;memset(cnt[cur],0,sizeof(cnt[cur]));
            cnt[cur][nw]=sz[cur];return;
        }
        pushdown(cur);
        int mid=(l+r)>>1;
        if (left<=mid) update(cur<<1,left,right,nw,l,mid);
        if (mid+1<=right) update(cur<<1|1,left,right,nw,mid+1,r);
        pushup(cur);
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
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);
    io.Get(n);io.Get(q);io.getstring(s+1);
    SegmentTree::build(1,1,n);int l,r;
    while (q--)
    {
        io.Get(l);io.Get(r);
        memset(cc,0,sizeof(cc));SegmentTree::query(1,l,r,1,n);
        int oddnum=0,ind=0;for (register int i=1;i<=26;i++) if (cc[i]&1) oddnum++,ind=i;
        if (oddnum>1) continue;
        int ptl=l,ptr=r,curlen;
        for (register int i=1;i<=26;i++)
        {
            curlen=cc[i]>>1;
            SegmentTree::update(1,ptl,ptl+curlen-1,i,1,n);
            SegmentTree::update(1,ptr-curlen+1,ptr,i,1,n);
            ptl+=curlen;ptr-=curlen;
        }
        if (ind) SegmentTree::update(1,ptl,ptr,ind,1,n);
    }
    for (register int i=1;i<=n;i++)
    {
        memset(cc,0,sizeof(cc));
        SegmentTree::query(1,i,i,1,n);
        for (register int j=1;j<=26;j++) if (cc[j]) printf("%c",'a'+j-1);
    }
    printf("\n");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}