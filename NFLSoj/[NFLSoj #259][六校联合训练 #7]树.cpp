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
int val[MAXN+48],pre[MAXN+48];
int maxn[MAXN+48][21],anc[MAXN+48][21],Anc[MAXN+48][21],depth[MAXN+48];

int head[MAXN+48],to[MAXN*2+48],nxt[MAXN*2+48],tot=1;
inline void addedge(int s,int t)
{
    to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
    to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

inline void dfs(int cur,int father)
{
    for (register int i=head[cur];i;i=nxt[i])
    {
        register int y=to[i];
        if (y!=father)
        {
            depth[y]=depth[cur]+1;
            maxn[y][0]=val[cur];anc[y][0]=cur;
            for (register int j=1;j<=17;j++)
            {
                anc[y][j]=anc[anc[y][j-1]][j-1];
                maxn[y][j]=max(maxn[y][j-1],maxn[anc[y][j-1]][j-1]);
            }
            dfs(y,cur);
        }
    }
}

inline void init_pre()
{
    depth[1]=1;dfs(1,-1);
    for (register int i=1;i<=n;i++)
    {
        pre[i]=i;
        for (register int j=17;j>=0;j--)
            if (maxn[pre[i]][j]<=val[i]) pre[i]=anc[pre[i]][j];
        pre[i]=anc[pre[i]][0];
    }
}

inline void init_table()
{
    for (register int i=1;i<=n;i++) Anc[i][0]=pre[i];
    for (register int j=1;j<=17;j++)
        for (register int i=1;i<=n;i++)
            Anc[i][j]=Anc[Anc[i][j-1]][j-1];
}

inline int getfirst(int u,int c)
{
    if (val[u]>c) return u;
    int res=u;
    for (register int j=17;j>=0;j--)
        if (maxn[res][j]<=c) res=anc[res][j];
    return anc[res][0];
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(q);
    for (register int i=1;i<=n;i++) io.Get(val[i]);
    int x,y,u,v,c,ans;
    for (register int i=1;i<=n-1;i++)
    {
        io.Get(x);io.Get(y);
        addedge(x,y);
    }
    init_pre();init_table();
    while (q--)
    {
        io.Get(u);io.Get(v);io.Get(c);
        u=getfirst(u,c);
        if (depth[u]<depth[v]) {printf("0\n");continue;}
        ans=1;
        for (register int i=17;i>=0;i--)
            if (depth[Anc[u][i]]>=depth[v]) ans+=(1<<i),u=Anc[u][i];
        printf("%d\n",ans);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}