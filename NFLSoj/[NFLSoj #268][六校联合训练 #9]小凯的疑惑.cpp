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

const int MAXN=3e5;

int n,q;
char s[MAXN+48];

struct Matrix
{
    int b[3][3];
    inline void init() {memset(b,0x3f,sizeof(b));}
    inline void init_I() {init();b[1][1]=b[2][2]=0;}
    inline Matrix operator * (Matrix ma)
    {
        Matrix res;res.init();
        for (register int i=1;i<=2;i++)
            for (register int j=1;j<=2;j++)
                for (register int k=1;k<=2;k++)
                    check_min(res.b[i][j],b[i][k]+ma.b[k][j]);
        return res;
    }
}base[2],sta;

inline void init_base()
{
    base[0].b[1][1]=0;base[0].b[1][2]=1;base[0].b[2][1]=2;base[0].b[2][2]=1;
    base[1].b[1][1]=1;base[1].b[1][2]=0;base[1].b[2][1]=2;base[1].b[2][2]=0;
    sta.b[1][1]=0;sta.b[1][2]=INF;
}

namespace SegmentTree
{
    Matrix ma[MAXN*4];
    inline void pushup(int cur) {ma[cur]=ma[cur<<1]*ma[cur<<1|1];}
    inline void build(int cur,int l,int r)
    {
        if (l==r) {ma[cur]=base[s[l]-'0'];return;}
        int mid=(l+r)>>1;
        build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
        pushup(cur);
    }
    inline void update(int cur,int pos,int nw,int l,int r)
    {
        if (l==r) {ma[cur]=base[nw];return;}
        int mid=(l+r)>>1;
        if (pos<=mid) update(cur<<1,pos,nw,l,mid); else update(cur<<1|1,pos,nw,mid+1,r);
        pushup(cur);
    }
    inline Matrix query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return ma[cur];
        int mid=(l+r)>>1;Matrix res;res.init_I();
        if (left<=mid) res=res*query(cur<<1,left,right,l,mid);
        if (mid+1<=right) res=res*query(cur<<1|1,left,right,mid+1,r);
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
    init_base();
    io.Get(n);io.getstring(s+1);
    SegmentTree::build(1,1,n);
    io.Get(q);int op,x,l,r;
    while (q--)
    {
        io.Get(op);
        if (op==1)
        {
            io.Get(l);io.Get(r);
            Matrix trans=SegmentTree::query(1,l,r,1,n);
            Matrix res=sta*trans;
            io.Print(res.b[1][1],'\n');
        }
        else
        {
            io.Get(l);io.Get(x);
            SegmentTree::update(1,l,x,1,n);
        }
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}