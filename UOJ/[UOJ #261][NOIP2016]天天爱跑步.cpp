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

int n,m;int w[MAXN+48];
int depth[MAXN+48],anc[MAXN+48][21],fa[MAXN+48];
vector<int> v[MAXN+48];
struct Query
{
    int x,y,lca;
}q[MAXN+48];

inline void dfs(int cur,int father)
{
    fa[cur]=father;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father)
        {
            depth[y]=depth[cur]+1;
            anc[y][0]=cur;for (register int j=1;j<=17;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
            dfs(y,cur);
        }
    }
}

inline int getlca(int u,int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    for (register int i=17;i>=0;i--)
        if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
    if (u==v) return u;
    for (register int i=17;i>=0;i--)
        if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
    return anc[u][0];
}

vector<int> ins[MAXN+48],del[MAXN+48];
int cnt[MAXN*3+48],ans[MAXN+48];

inline void Dfs(int cur,int father,int type)
{
    int cmp;
    if (!type) cmp=cnt[w[cur]+depth[cur]]; else cmp=cnt[w[cur]-depth[cur]+MAXN];
    for (register int i=0;i<int(ins[cur].size());i++)
        cnt[ins[cur][i]]++;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father) Dfs(y,cur,type);
    }
    for (register int i=0;i<int(del[cur].size());i++)
        cnt[del[cur][i]]--;
    if (!type) ans[cur]+=cnt[w[cur]+depth[cur]]-cmp; else ans[cur]+=cnt[w[cur]-depth[cur]+MAXN]-cmp;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);int x,y;
    for (register int i=1;i<=n-1;i++)
    {
        io.Get(x);io.Get(y);
        v[x].pb(y);v[y].pb(x);
    }
    for (register int i=1;i<=n;i++) io.Get(w[i]);
    depth[1]=1;dfs(1,-1);
    for (register int i=1;i<=m;i++) io.Get(q[i].x),io.Get(q[i].y),q[i].lca=getlca(q[i].x,q[i].y);
    for (register int i=1;i<=m;i++)
    {
        ins[q[i].x].pb(depth[q[i].x]);
        if (q[i].lca!=1) del[fa[q[i].lca]].pb(depth[q[i].x]);
    }
    Dfs(1,-1,0);
    for (register int i=1;i<=n;i++) ins[i].clear(),del[i].clear();
    memset(cnt,0,sizeof(cnt));
    for (register int i=1;i<=m;i++)
    {
        int T=depth[q[i].x]+depth[q[i].y]-2*depth[q[i].lca];
        ins[q[i].y].pb(T-depth[q[i].y]+MAXN);
        del[q[i].lca].pb(T-depth[q[i].y]+MAXN);
    }
    Dfs(1,-1,1);
    for (register int i=1;i<=n;i++) printf("%d ",ans[i]);
    printf("\n");
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}