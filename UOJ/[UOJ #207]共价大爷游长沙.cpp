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

const int INF=1e9;
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

int n,m;
vector<pair<Pair,int> > S;int xorsum=0;

namespace LCT
{
    struct node
    {
        int ch[2],flip;
        int father,sum,val,vsum;
        inline void clear()
        {
            ch[0]=ch[1]=flip=0;
            father=0;sum=val=vsum=0;
        }
    }tree[MAXN+48];
    inline void init()
    {
        for (register int i=1;i<=n;i++) tree[i].clear();
    }
    inline void pushdown(int cur)
    {
        if (tree[cur].flip)
        {
            tree[tree[cur].ch[0]].flip^=1;
            tree[tree[cur].ch[1]].flip^=1;
            swap(tree[cur].ch[0],tree[cur].ch[1]);
            tree[cur].flip=0;
        }
    }
    inline void pushup(int cur)
    {
        tree[cur].sum=tree[tree[cur].ch[0]].sum^tree[tree[cur].ch[1]].sum^tree[cur].vsum^tree[cur].val;
    }
    inline bool isroot(int cur) {return tree[tree[cur].father].ch[0]!=cur && tree[tree[cur].father].ch[1]!=cur;}
    inline void rotate(int x)
    {
        int y=tree[x].father,z=tree[y].father;
        pushdown(y);pushdown(x);
        if (!isroot(y)) tree[z].ch[tree[z].ch[1]==y]=x;
        int k=(tree[y].ch[1]==x);
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
            if (!isroot(y))
                ((tree[y].ch[1]==x)^(tree[z].ch[1]==y))?rotate(x):rotate(y);
            rotate(x);
        }
    }
    inline void access(int cur)
    {
        for (register int pre=0;cur;pre=cur,cur=tree[cur].father)
        {
            splay(cur);
            tree[cur].vsum^=tree[tree[cur].ch[1]].sum;
            tree[cur].vsum^=tree[pre].sum;
            tree[cur].ch[1]=pre;pushup(cur);
        }
    }
    inline void makeroot(int x)
    {
        access(x);splay(x);tree[x].flip^=1;
    }
    inline void link(int x,int y)
    {
        makeroot(x);makeroot(y);
        tree[x].father=y;tree[y].vsum^=tree[x].sum;pushup(y);
    }
    inline void cut(int x,int y)
    {
        makeroot(x);access(y);splay(y);
        tree[x].father=0;tree[y].ch[0]=0;pushup(y);
    }
    inline void modify(int x,int y)
    {
        makeroot(x);tree[x].val^=y;
        pushup(x);
    }
    inline int query(int x)
    {
        access(x);splay(x);
        return tree[x].vsum^tree[x].val^tree[tree[x].ch[1]].sum;
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
    srand(time(NULL));
    scanf("%d",&n);scanf("%d%d",&n,&m);int type,x,y,u,v;
    LCT::init();
    for (register int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&x,&y);
        LCT::link(x,y);
    }
    while (m--)
    {
        scanf("%d",&type);
        if (type==1)
        {
            scanf("%d%d%d%d",&x,&y,&u,&v);
            LCT::cut(x,y);LCT::link(u,v);
        }
        else if (type==2)
        {
            scanf("%d%d",&x,&y);
            int tmp=rand();xorsum^=tmp;S.pb(mp(mp(x,y),tmp));
            LCT::modify(x,tmp);LCT::modify(y,tmp);
        }
        else if (type==3)
        {
            scanf("%d",&u);
            x=S[u-1].x.x;y=S[u-1].x.y;int tmp=S[u-1].y;
            xorsum^=tmp;LCT::modify(x,tmp);LCT::modify(y,tmp);
        }
        else
        {
            scanf("%d%d",&x,&y);
            LCT::makeroot(x);LCT::makeroot(y);
            int tmp=LCT::query(x);
            if (tmp==xorsum) puts("YES"); else puts("NO");
        }
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}