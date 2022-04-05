//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

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

int n,m,q;

namespace LCT
{
    struct node
    {
        int ch[2],val,maxn,maxind,flip,father;
    }tree[MAXN+48];
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
            tree[cur].ch[1]=pre;
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
        tree[x].father=0;tree[y].ch[0]=0;
    }
}

int ans[MAXN+48];
int X[MAXN+48],Y[MAXN+48];

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca,L,R,lastans=0,k1,k2;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d%d",&n,&m,&q);
        rep(i,1,n) LCT::Create(i,0);int pt=1;
        rep(i,1,m) scanf("%d%d",&X[i],&Y[i]);
        while (pt<=m)
        {
            int x=X[pt],y=Y[pt];
            if (LCT::issame(x,y)) break;
            LCT::link(x,y);
            pt++;
        }
        ans[1]=pt;
        rep(i,2,m)
        {
            if (ans[i-1]==m+1) {ans[i]=m+1;continue;}
            LCT::cut(X[i-1],Y[i-1]);pt=ans[i-1];
            while (pt<=m)
            {
                int x=X[pt],y=Y[pt];
                if (LCT::issame(x,y)) break;
                LCT::link(x,y);
                pt++;
            }
            ans[i]=pt;
        }
        while (q--)
        {
            scanf("%d%d",&L,&R);
            k1=(L^lastans)%m+1;k2=(R^lastans)%m+1;
            L=min(k1,k2);R=max(k1,k2);
            if (R>=ans[L]) puts("Yes"),lastans=1; else puts("No"),lastans=0;
        }
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}