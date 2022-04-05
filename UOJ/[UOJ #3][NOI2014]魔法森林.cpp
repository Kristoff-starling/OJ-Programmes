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

int n,m;

struct Edge
{
    int u,v,a,b;
    inline void input() {scanf("%d%d%d%d",&u,&v,&a,&b);}
    inline bool operator < (const Edge &other) const {return a<other.a;}
}edge[MAXN+48];

namespace LCT
{
    struct node
    {
        int ch[2],val,maxn,maxind,flip,father;
    }tree[MAXN+48];
    inline void update(int x,int y)
    {
        if (!y) return;
        if (tree[y].maxn>tree[x].maxn) tree[x].maxn=tree[y].maxn,tree[x].maxind=tree[y].maxind;
    }
    inline void pushup(int cur)
    {
        tree[cur].maxn=tree[cur].val;tree[cur].maxind=cur;
        update(cur,tree[cur].ch[0]);update(cur,tree[cur].ch[1]);
    }
    inline void pushdown(int cur)
    {
        if (tree[cur].flip)
        {
            tree[tree[cur].ch[0]].flip^=1;
            tree[tree[cur].ch[1]].flip^=1;
            tree[cur].flip=0;swap(tree[cur].ch[0],tree[cur].ch[1]);
        }
    }
    inline void Create(int cur,int val)
    {
        tree[cur].val=val;tree[cur].ch[0]=tree[cur].ch[1]=tree[cur].flip=tree[cur].father=0;
        pushup(cur);
    }
    inline bool isroot(int cur) {return tree[tree[cur].father].ch[0]!=cur && tree[tree[cur].father].ch[1]!=cur;}
    inline void rotate(int x)
    {
        int y=tree[x].father,z=tree[y].father;
        pushdown(y);pushdown(x);
        int k=(tree[y].ch[1]==x);
        if (!isroot(y)) tree[z].ch[tree[z].ch[1]==y]=x;
        tree[y].ch[k]=tree[x].ch[k^1];tree[x].ch[k^1]=y;
        tree[tree[y].ch[k]].father=y;tree[y].father=x;tree[x].father=z;
        pushup(y);pushup(x);
    }
    inline void splay(int x)
    {
        pushdown(x);
        while (!isroot(x))
        {
            int y=tree[x].father,z=tree[y].father;
            if (!isroot(y)) ((tree[y].ch[1]==x)^(tree[z].ch[1]==y))?rotate(x):rotate(y);
            rotate(x);
        }
    }
    inline void access(int cur)
    {
        for (register int pre=0;cur;pre=cur,cur=tree[cur].father)
        {
            splay(cur);
            tree[cur].ch[1]=pre;pushup(cur);
        }
    }
    inline void makeroot(int cur)
    {
        access(cur);splay(cur);
        tree[cur].flip^=1;
    }
    inline int find_root(int x)
    {
        access(x);splay(x);
        while (tree[x].ch[0]) x=tree[x].ch[0];
        return x;
    }
    inline bool issame(int x,int y)
    {
        return find_root(x)==find_root(y);
    }
    inline void link(int x,int y)
    {
        makeroot(x);
        tree[x].father=y;
    }
    inline void cut(int x,int y)
    {
        makeroot(x);access(y);splay(y);
        tree[x].father=0;tree[y].ch[0]=0;pushup(y);
    }
    inline Pair query(int x,int y)
    {
        makeroot(x);access(y);splay(y);
        return mp(tree[y].maxn,tree[y].maxind);
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
    scanf("%d%d",&n,&m);
    for (register int i=1;i<=m;i++) edge[i].input();
    sort(edge+1,edge+m+1);
    for (register int i=1;i<=n;i++) LCT::Create(i,0);
    for (register int i=1;i<=m;i++) LCT::Create(n+i,edge[i].b);
    int ans=INF;
    for (register int i=1;i<=m;i++)
    {
        if (edge[i].a>=ans) break;
        if (edge[i].u!=edge[i].v)
        {
            if (!LCT::issame(edge[i].u,edge[i].v))
                LCT::link(n+i,edge[i].u),LCT::link(n+i,edge[i].v);
            else
            {
                Pair res=LCT::query(edge[i].u,edge[i].v);
                if (res.x>edge[i].b)
                {
                    LCT::cut(res.y,edge[res.y-n].u);LCT::cut(res.y,edge[res.y-n].v);
                    LCT::link(n+i,edge[i].u);LCT::link(n+i,edge[i].v);
                }
            }
        }
        if (LCT::issame(1,n)) check_min(ans,edge[i].a+LCT::query(1,n).x);
    }
    if (ans>=INF) ans=-1;
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}