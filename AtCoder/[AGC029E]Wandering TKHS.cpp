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

int n,maxn[MAXN+48],fa[MAXN+48];vector<int> v[MAXN+48];
int dp[MAXN+48],ans[MAXN+48];

int L[MAXN+48],R[MAXN+48],ind;

int id[MAXN+48];
inline bool cmp(int x,int y)
{
    int xx=fa[fa[x]],yy=fa[fa[y]];
    return maxn[xx]<maxn[yy];
}

bool exist[MAXN+48];

namespace DSU
{
    int pre[MAXN+48];
    inline void init() {for (register int i=1;i<=n;i++) pre[i]=i;}
    inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
    inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

namespace BIT
{
    int c[MAXN+48];
    inline void init() {memset(c,0,sizeof(c));}
    inline void update(int x,int delta) {if (!x) return;while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
    inline int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
    inline int calc(int x,int y) {return query(y)-query(x-1);}
}

inline void dfs(int cur,int father)
{
    L[cur]=++ind;fa[cur]=father;
    for (auto y : v[cur]) if (y!=father) maxn[y]=max(maxn[cur],y),dfs(y,cur);
    R[cur]=ind;
}

inline void Dfs(int cur,int father,int curans)
{
    int cursum=0;
    for (auto y : v[cur]) if (y!=father) cursum+=dp[y];
    ans[cur]=curans+1+cursum;
    for (auto y : v[cur]) if (y!=father) Dfs(y,cur,curans+1+cursum-dp[y]);
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
    for (register int i=1;i<=n-1;i++)
    {
        int x,y;scanf("%d%d",&x,&y);
        v[x].pb(y);v[y].pb(x);
    }
    maxn[1]=1;dfs(1,0);
    for (register int i=1;i<=n;i++) id[i]=i;
    maxn[0]=INF;sort(id+1,id+n+1,cmp);
    DSU::init();BIT::init();int curpt=0;
    for (register int i=1;i<=n;i++)
    {
        if (fa[fa[id[i]]]==0) continue;
        int need=maxn[fa[fa[id[i]]]];
        while (curpt<need-1)
        {
            ++curpt;exist[curpt]=true;
            BIT::update(L[curpt],1);BIT::update(L[fa[curpt]],-1);
            for (auto y : v[curpt])
                if (exist[y])
                {
                    int xx=curpt,yy=y;if (fa[xx]==yy) swap(xx,yy);
                    int ynum=BIT::calc(L[yy],R[yy]),anc=DSU::find_anc(xx);
                    BIT::update(L[xx],ynum);BIT::update(L[fa[anc]],-ynum);
                    DSU::update(yy,xx);
                }
        }
        dp[id[i]]=BIT::calc(L[id[i]],R[id[i]]);
    }
    Dfs(1,0,0);
    for (register int i=2;i<=n;i++) printf("%d ",ans[i]-1);
    puts("");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}