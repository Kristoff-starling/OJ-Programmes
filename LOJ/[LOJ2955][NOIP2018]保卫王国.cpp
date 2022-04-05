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
#define Online true

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

int n,m,val[MAXN+48];
vector<int> v[MAXN+48];

struct Matrix
{
    LL b[3][3];
    Matrix () {}
    inline Matrix (LL _v1,LL _v2,LL _v3,LL _v4) {b[1][1]=_v1;b[1][2]=_v2;b[2][1]=_v3;b[2][2]=_v4;}
    inline void clear() {for (register int i=1;i<=2;i++) for (register int j=1;j<=2;j++) b[i][j]=LINF;}
    inline void init_I() {clear();b[1][1]=b[2][2]=0;}
    inline Matrix operator * (Matrix other)
    {
        Matrix res;res.clear();
        for (register int i=1;i<=2;i++)
            for (register int j=1;j<=2;j++)
                for (register int k=1;k<=2;k++)
                    check_min(res.b[i][j],b[i][k]+other.b[k][j]);
        return res;
    }
};

int fa[MAXN+48],son[MAXN+48],sz[MAXN+48];
int top[MAXN+48],ed[MAXN+48],pos[MAXN+48],totree[MAXN+48],ind=0;

inline void dfs1(int cur,int father)
{
    fa[cur]=father;son[cur]=0;sz[cur]=1;
    for (auto y : v[cur])
        if (y!=father)
        {
            dfs1(y,cur);sz[cur]+=sz[y];
            if ((!son[cur]) || (sz[son[cur]]<sz[y])) son[cur]=y;
        }
}

inline int dfs2(int cur,int tp)
{
    top[cur]=tp;pos[cur]=++ind;totree[ind]=cur;
    if (son[cur]) ed[cur]=dfs2(son[cur],tp); else ed[cur]=cur;
    for (auto y : v[cur])
        if (y!=fa[cur] && y!=son[cur]) dfs2(y,y);
    return ed[cur];
}

LL f[MAXN+48][2],g[MAXN+48][2];
inline void dfs(int cur,int father)
{
    for (auto y : v[cur])
        if (y!=father)
        {
            dfs(y,cur);
            f[cur][0]+=f[y][1];f[cur][1]+=min(f[y][0],f[y][1]);
            if (y!=son[cur]) g[cur][0]+=f[y][1],g[cur][1]+=min(f[y][0],f[y][1]);
        }
    f[cur][1]+=val[cur];g[cur][1]+=val[cur];
}

namespace SegmentTree
{
    Matrix info[MAXN*4];
    inline void pushup(int cur) {info[cur]=info[cur<<1|1]*info[cur<<1];}
    inline void build(int cur,int l,int r)
    {
        if (l==r)
        {
            int pt=totree[l];
            info[cur]=Matrix(g[pt][1],g[pt][0],g[pt][1],LINF);
            return;
        }
        int mid=(l+r)>>1;
        build(cur<<1,l,mid);build(cur<<1|1,mid+1,r);
        pushup(cur);
    }
    inline void modify(int cur,int pos,int l,int r)
    {
        if (l==r)
        {
            int pt=totree[l];
            info[cur]=Matrix(g[pt][1],g[pt][0],g[pt][1],LINF);
            return;
        }
        int mid=(l+r)>>1;
        if (pos<=mid) modify(cur<<1,pos,l,mid); else modify(cur<<1|1,pos,mid+1,r);
        pushup(cur);
    }
    inline Matrix query(int cur,int left,int right,int l,int r)
    {
        if (left<=l && r<=right) return info[cur];
        int mid=(l+r)>>1;Matrix res;res.init_I();
        if (mid+1<=right) res=res*query(cur<<1|1,left,right,mid+1,r);
        if (left<=mid) res=res*query(cur<<1,left,right,l,mid);
        return res;
    }
}

inline Matrix query(int u)
{
    return SegmentTree::query(1,pos[u],pos[ed[u]],1,n);
}

inline void update(int u,int op,LL nv)
{
    Matrix od,nw;g[u][op]=nv;
    while (u)
    {
        od=query(top[u]);
        SegmentTree::modify(1,pos[u],1,n);
        nw=query(top[u]);
        u=fa[top[u]];
        g[u][0]+=nw.b[1][1]-od.b[1][1];
        g[u][1]+=min(nw.b[1][1],nw.b[1][2])-min(od.b[1][1],od.b[1][2]);
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
#ifdef Online
    freopen ("defense.in","r",stdin);
    freopen ("defense.out","w",stdout);
#endif
    char type[5];int a,b,x,y;scanf("%d%d%s",&n,&m,type+1);
    for (register int i=1;i<=n;i++) scanf("%d",val+i);
    for (register int i=1;i<=n-1;i++) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    dfs1(1,0);dfs2(1,1);dfs(1,0);SegmentTree::build(1,1,n);
    while (m--)
    {
        scanf("%d%d%d%d",&a,&x,&b,&y);
        LL tmpa=g[a][x^1],tmpb=g[b][y^1];
        update(a,x^1,LINF);update(b,y^1,LINF);
        Matrix res=query(1);LL ans=min(res.b[1][1],res.b[1][2]);
        if (ans>=LINF) puts("-1"); else printf("%lld\n",ans);
        update(a,x^1,tmpa);update(b,y^1,tmpb);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}