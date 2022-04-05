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

const int MAXN=1200000;

int q;char s[4000048];

namespace LCT
{
    struct node
    {
        int ch[2],vsum,sum,val,father;
    }tree[MAXN+48];
    inline void Create(int cur,int val) {tree[cur].val=tree[cur].sum=val;tree[cur].vsum=tree[cur].ch[0]=tree[cur].ch[1]=tree[cur].father=0;}
    inline void pushup(int cur) {tree[cur].sum=tree[cur].vsum+tree[tree[cur].ch[0]].sum+tree[tree[cur].ch[1]].sum+tree[cur].val;}
    inline bool isroot(int cur) {return tree[tree[cur].father].ch[0]!=cur && tree[tree[cur].father].ch[1]!=cur;}
    inline void rotate(int x)
    {
        int y=tree[x].father,z=tree[y].father;
        int k=(tree[y].ch[1]==x);
        if (!isroot(y)) tree[z].ch[tree[z].ch[1]==y]=x;
        tree[y].ch[k]=tree[x].ch[k^1];tree[x].ch[k^1]=y;
        tree[tree[y].ch[k]].father=y;tree[y].father=x;tree[x].father=z;
        pushup(y);pushup(x);
    }
    inline void splay(int x)
    {
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
            tree[cur].vsum+=tree[tree[cur].ch[1]].sum;
            tree[cur].vsum-=tree[pre].sum;
            tree[cur].ch[1]=pre;pushup(cur);
        }
    }
    inline void link(int x,int y)
    {
        access(x);splay(x);access(y);splay(y);
        tree[x].father=y;tree[y].vsum+=tree[x].sum;pushup(y);
    }
    inline void cut(int x)
    {
        access(x);splay(x);
        tree[tree[x].ch[0]].father=0;tree[x].ch[0]=0;pushup(x);
    }
    inline int query(int x)
    {
        access(x);splay(x);
        return tree[x].vsum+tree[tree[x].ch[1]].sum+tree[x].val;
    }
}

namespace SAM
{
    int nxt[MAXN*2][27],par[MAXN*2],maxn[MAXN*2],root,last,tot;
    inline void init() {tot=1;root=last=1;LCT::Create(root,0);}
    inline void extend(char ch)
    {
        int p=last,np=++tot,w=ch-'A'+1;maxn[np]=maxn[p]+1;LCT::Create(np,1);
        while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
        if (!p) {par[np]=root;LCT::link(np,root);last=np;return;}
        int q=nxt[p][w];
        if (maxn[q]==maxn[p]+1) {par[np]=q;LCT::link(np,q);last=np;return;}
        int nq=++tot;LCT::Create(nq,0);
        maxn[nq]=maxn[p]+1;memcpy(nxt[nq]+1,nxt[q]+1,26*sizeof(int));
        par[nq]=par[q];LCT::link(nq,par[nq]);
        LCT::cut(q);par[q]=nq;LCT::link(q,nq);
        par[np]=nq;LCT::link(np,nq);
        while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
        last=np;
    }
    inline int go(int cur,char ch) {return nxt[cur][ch-'A'+1]?nxt[cur][ch-'A'+1]:-1;}
}

int mask;
inline void decodeWithMask(int mask)
{
    int len=strlen(s);
    for (register int j=0;j<len;j++)
    {
        mask=(mask*131+j)%len;
        char t=s[j];
        s[j]=s[mask];
        s[mask]=t;
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
    io.Get(q);io.getstring(s);int len=strlen(s);char op[10];
    SAM::init();for (register int i=0;i<len;i++) SAM::extend(s[i]);
    while (q--)
    {
        io.getstring(op+1);io.getstring(s);
        decodeWithMask(mask);len=strlen(s);
        if (op[1]=='A')
        {
            for (register int i=0;i<len;i++) SAM::extend(s[i]);
        }
        else
        {
            int ans=0,cur=SAM::root;
            for (register int i=0;i<len;i++)
            {
                cur=SAM::go(cur,s[i]);
                if (cur==-1) break;
            }
            if (cur!=-1) ans=LCT::query(cur);
            printf("%d\n",ans);
            mask^=ans;
        }
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
