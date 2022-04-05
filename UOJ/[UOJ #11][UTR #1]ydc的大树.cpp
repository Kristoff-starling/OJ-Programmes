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

struct Edge
{
    int x,y,l;
    Edge () {}
    inline Edge (int _x,int _y,int _l) {x=_x;y=_y;l=_l;}
}edge[MAXN+48];

int n,m,color[MAXN+48];
vector<Pair> v[MAXN+48];int depth[MAXN+48];
int anc[MAXN+48][21];

inline void reconstruct()
{
    for (register int i=1;i<=n;i++) v[i].clear();
    for (register int i=1;i<=n-1;i++)
    {
        int x=edge[i].x,y=edge[i].y,l=edge[i].l;
        if (anc[x][0]==y) swap(x,y);
        v[x].pb(mp(y,l));
    }
}

inline void dfs(int cur,int father)
{
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        if (y!=father)
        {
            depth[y]=depth[cur]+1;
            anc[y][0]=cur;for (register int j=1;j<=17;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
            dfs(y,cur);
        }
    }
}

int f[MAXN+48],flca[MAXN+48];
inline void dfs_f(int cur)
{
    f[cur]=-INF;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        dfs_f(y);
        if (f[y]+v[cur][i].y>f[cur])
        {
            f[cur]=f[y]+v[cur][i].y;
            flca[cur]=flca[y];
        }
        else if (f[y]+v[cur][i].y==f[cur]) flca[cur]=cur;
    }
    if (color[cur] && f[cur]<0) f[cur]=0,flca[cur]=cur;
}

int g[MAXN+48],glca[MAXN+48];
inline void dfs_g(int cur,int gg,int gl)
{
    g[cur]=gg;glca[cur]=gl;
    vector<Pair> pre,suf;pre.clear();suf.clear();
    int cf=-INF,clca=-1;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        if (f[y]+v[cur][i].y>cf)
        {
            cf=f[y]+v[cur][i].y;
            clca=flca[y];
        }
        else if (f[y]+v[cur][i].y==cf) clca=cur;
        pre.pb(mp(cf,clca));
    }
    cf=-INF;clca=-1;
    for (register int i=int(v[cur].size())-1;i>=0;i--)
    {
        int y=v[cur][i].x;
        if (f[y]+v[cur][i].y>cf)
        {
            cf=f[y]+v[cur][i].y;
            clca=flca[y];
        }
        else if (f[y]+v[cur][i].y==cf) clca=cur;
        suf.pb(mp(cf,clca));
    }
    int ng,ngl,g1,gl1,g2,gl2;
    for (register int i=0,j=int(suf.size())-1;i<int(v[cur].size());i++,j--)
    {
        int y=v[cur][i].x;
        ng=gg;ngl=gl;
        if (i) g1=pre[i-1].x,gl1=pre[i-1].y; else g1=-INF,gl1=-1;
        if (j) g2=suf[j-1].x,gl2=suf[j-1].y; else g2=-INF,gl2=-1;
        if (g1>ng) ng=g1,ngl=gl1; else if (g1==ng) ngl=cur;
        if (g2>ng) ng=g2,ngl=gl2; else if (g2==ng) ngl=cur;
        if (color[cur] && ng<0) ng=0,ngl=cur;
        dfs_g(y,ng+v[cur][i].y,ngl);
    }
}

inline int query_lca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    for (register int i=17;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return u;
    for (register int i=17;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return anc[u][0];
}

int mark[MAXN+48],sum[MAXN+48];
inline void doit(int x,int y)
{
    int LCA=query_lca(x,y);
    mark[x]++;mark[y]++;mark[LCA]--;mark[anc[LCA][0]]--;
}

inline void dfs_sum(int cur)
{
    sum[cur]=mark[cur];
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        dfs_sum(y);sum[cur]+=sum[y];
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
    scanf("%d%d",&n,&m);int x,y,l;
    for (register int i=1;i<=m;i++) scanf("%d",&x),color[x]=1;
    for (register int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&x,&y,&l);edge[i]=Edge(x,y,l);
        v[x].pb(mp(y,l));v[y].pb(mp(x,l));
    }
    depth[1]=1;dfs(1,-1);reconstruct();
    dfs_f(1);dfs_g(1,-INF,-1);
    for (register int i=1;i<=n;i++)
        if (color[i])
        {
            if (max(f[i],g[i])<=0) continue;
            if (f[i]==g[i]) continue;
            if (f[i]>g[i]) mark[flca[i]]++,mark[i]--; else doit(anc[i][0],glca[i]);
        }
    dfs_sum(1);
    int maxn=-1,maxcnt=0;
    for (register int i=1;i<=n;i++)
    {
        if (color[i]) continue;
        if (sum[i]>maxn) maxn=sum[i],maxcnt=1;
        else if (sum[i]==maxn) maxcnt++;
    }
    printf("%d %d\n",maxn,maxcnt);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}