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

const int MAXN=200;

int n,m;
Pair edge[MAXN+48];
vector<int> v[MAXN+48],anslist;

int cnt,visited[MAXN+48];
int mark[MAXN+48],pre[MAXN+48],mat[MAXN+48];
int head,tail,q[MAXN+48];

int fa[MAXN+48];
inline int find_anc(int x) {if (fa[x]!=x) fa[x]=find_anc(fa[x]);return fa[x];}

int tx,ty;

inline void augment(int x)
{
    while (x!=-1)
    {
        int tmp=mat[pre[x]];
        mat[x]=pre[x];mat[pre[x]]=x;
        x=tmp;
    }
}

inline void rebuild(int x,int y,int LCA)
{
    while (find_anc(x)!=LCA)
    {
        pre[x]=y;
        if (fa[x]==x) fa[x]=LCA;
        if (fa[mat[x]]==mat[x]) fa[mat[x]]=LCA;
        if (mark[mat[x]]==1) mark[mat[x]]=0,q[++tail]=mat[x];
        y=mat[x];x=pre[y];
    }
}

inline int find_lca(int x,int y)
{
    ++cnt;int p=find_anc(x);
    for (;;)
    {
        visited[p]=cnt;
        p=mat[p];if (p==-1) break;
        p=find_anc(pre[p]);
    }
    p=find_anc(y);
    for (;;p=find_anc(pre[mat[p]])) if (visited[p]==cnt) return p;
}

inline void doit(int x,int y)
{
    int LCA=find_lca(x,y);
    rebuild(x,y,LCA);rebuild(y,x,LCA);
}

inline int bfs(int st)
{
    for (register int i=1;i<=n;i++) mark[i]=pre[i]=-1,fa[i]=i;
    head=tail=1;q[1]=st;mark[st]=0;
    while (head<=tail)
    {
        int cur=q[head++];
        for (auto y : v[cur])
        {
            if (y==tx || y==ty || find_anc(cur)==find_anc(y)) continue;
            if (mark[y]==-1)
            {
                mark[y]=1;pre[y]=cur;
                if (mat[y]==-1) {augment(y);return 1;}
                mark[mat[y]]=0;q[++tail]=mat[y];
            }
            else if (mark[y]==0) doit(cur,y);
        }
    }
    return 0;
}

inline int max_match()
{
    int res=0;
    for (register int i=1;i<=n;i++) mat[i]=-1;
    for (register int i=1;i<=n;i++) if (mat[i]==-1 && i!=tx && i!=ty) res+=bfs(i);
    return res;
}

inline void Clear()
{
    memset(visited,0,sizeof(visited));cnt=0;
    for (register int i=1;i<=n;i++) v[i].clear();
    anslist.clear();
}

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
        Clear();int x,y;
        for (register int i=1;i<=m;i++) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x),edge[i]=mp(x,y);
        tx=ty=0;int ans=max_match(),fans=0;
        for (register int i=1;i<=m;i++)
        {
            tx=edge[i].x;ty=edge[i].y;
            int curans=max_match();
            if (curans<ans-1) fans++,anslist.pb(i);
        }
        printf("%d\n",fans);
        for (register int i=0;i<int(anslist.size());i++)
        {
            printf("%d",anslist[i]);
            if (i!=int(anslist.size())-1) printf(" ");
        }
        puts("");
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}