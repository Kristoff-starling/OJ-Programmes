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

int n;
Pair edge1[MAXN+48],edge2[MAXN+48];
vector<int> v1[MAXN+48],v2[MAXN+48];
vector<int> ins[MAXN+48],del[MAXN+48];

int L[MAXN+48],R[MAXN+48],depth2[MAXN+48];
int ans[MAXN+48];

inline int getanother(int x,Pair edge) {return x==edge.x?edge.y:edge.x;}

int depth1[MAXN+48],anc1[MAXN+48][21],anc2[MAXN+48][21];
inline void dfs1(int cur,int father)
{
    for (register int i=0;i<int(v1[cur].size());i++)
    {
        int y=getanother(cur,edge1[v1[cur][i]]);
        if (y!=father)
        {
            depth1[y]=depth1[cur]+1;
            anc1[y][0]=cur;for (register int j=1;j<=20;j++) anc1[y][j]=anc1[anc1[y][j-1]][j-1];
            dfs1(y,cur);
        }
    }
}

inline int getlca1(int u,int v)
{
    if (depth1[u]<depth1[v]) swap(u,v);
    for (register int i=20;i>=0;i--) if (depth1[anc1[u][i]]>=depth1[v]) u=anc1[u][i];
    if (u==v) return u;
    for (register int i=20;i>=0;i--) if (anc1[u][i]!=anc1[v][i]) u=anc1[u][i],v=anc1[v][i];
    return anc1[u][0];
}

inline int jump1(int u,int v)
{
    for (register int i=20;i>=0;i--) if (depth1[anc1[u][i]]>depth1[v]) u=anc1[u][i];
    return u;
}

int ind=0;
inline void dfs2(int cur,int father)
{
    L[cur]=++ind;
    for (register int i=0;i<int(v2[cur].size());i++)
    {
        int y=getanother(cur,edge2[v2[cur][i]]);
        if (y!=father)
        {
            depth2[y]=depth2[cur]+1;
            anc2[y][0]=cur;
            for (register int j=1;j<=20;j++) anc2[y][j]=anc2[anc2[y][j-1]][j-1];
            dfs2(y,cur);
        }
    }
    R[cur]=ind;
}

inline int getlca2(int u,int v)
{
    if (depth2[u]<depth2[v]) swap(u,v);
    for (register int i=20;i>=0;i--) if (depth2[anc2[u][i]]>=depth2[v]) u=anc2[u][i];
    if (u==v) return u;
    for (register int i=20;i>=0;i--) if (anc2[u][i]!=anc2[v][i]) u=anc2[u][i],v=anc2[v][i];
    return anc2[u][0];
}

namespace BIT
{
    int c[MAXN+48];
    inline void init() {for (register int i=1;i<=n;i++) c[i]=0;}
    inline void update(int x,int delta)
    {
        while (x<=n) c[x]+=delta,x+=LOWBIT(x);
    }
    inline int query(int x)
    {
        int res=0;
        while (x) res+=c[x],x^=LOWBIT(x);
        return res;
    }
}

int faedge[MAXN+48];
inline void dfs(int cur,int father)
{
    int tmp;
    if (cur!=1)
    {
        int x=edge1[faedge[cur]].x,y=edge1[faedge[cur]].y,LCA=getlca2(x,y);
        tmp=BIT::query(L[x])+BIT::query(L[y])-2*BIT::query(L[LCA]);
    }
    for (register int i=0;i<int(v1[cur].size());i++)
    {
        int y=getanother(cur,edge1[v1[cur][i]]);
        if (y!=father)
        {
            faedge[y]=v1[cur][i];
            dfs(y,cur);
        }
    }
    for (auto id : ins[cur])
    {
        int x=edge2[id].x,y=edge2[id].y;
        if (depth2[x]>depth2[y]) swap(x,y);
        BIT::update(L[y],1);BIT::update(R[y]+1,-1);
    }
    if (cur!=1)
    {
        int x=edge1[faedge[cur]].x,y=edge1[faedge[cur]].y,LCA=getlca2(x,y);
        ans[faedge[cur]]=BIT::query(L[x])+BIT::query(L[y])-2*BIT::query(L[LCA])-tmp;
    }
    for (auto id : del[cur])
    {
        int x=edge2[id].x,y=edge2[id].y;
        if (depth2[x]>depth2[y]) swap(x,y);
        BIT::update(L[y],-1);BIT::update(R[y]+1,1);
    }
}

inline void Clear()
{
    for (register int i=1;i<=n;i++) v1[i].clear(),v2[i].clear(),ins[i].clear(),del[i].clear();
    ind=0;BIT::init();
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca;io.Get(ca);
    while (ca--)
    {
        io.Get(n);Clear();int x,y;
        for (register int i=1;i<=n-1;i++)
        {
            io.Get(x);io.Get(y);
            edge1[i]=mp(x,y);v1[x].pb(i);v1[y].pb(i);
        }
        for (register int i=1;i<=n-1;i++)
        {
            io.Get(x);io.Get(y);
            edge2[i]=mp(x,y);v2[x].pb(i);v2[y].pb(i);
        }
        depth1[1]=1;dfs1(1,-1);
        for (register int i=1;i<=n-1;i++)
        {
            x=edge2[i].x;y=edge2[i].y;int LCA=getlca1(x,y);
            if (x!=LCA) ins[x].pb(i),del[jump1(x,LCA)].pb(i);
            if (y!=LCA) ins[y].pb(i),del[jump1(y,LCA)].pb(i);
        }
        depth2[1]=1;dfs2(1,-1);
        dfs(1,-1);
        for (register int i=1;i<=n-1;i++) printf("%d ",ans[i]);
        printf("\n");
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}