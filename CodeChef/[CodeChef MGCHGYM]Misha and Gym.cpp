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
int a[MAXN+48],toind[MAXN+48],toval[48],ind;
int cnt[48];

int w[1048],wtot;

bitset<MAXN+48> dp[448];

namespace Treap
{
    struct node
    {
        int left,right,val,priority;
        int cnt[11],sz,flip;
    }tree[MAXN*4];int tot,Root;
    inline void pushdown(int cur)
    {
        if (tree[cur].flip)
        {
            tree[tree[cur].left].flip^=1;
            tree[tree[cur].right].flip^=1;
            swap(tree[cur].left,tree[cur].right);
            tree[cur].flip=0;
        }
    }
    inline void pushup(int cur)
    {
        memset(tree[cur].cnt,0,sizeof(tree[cur].cnt));
        if (tree[cur].left) for (register int i=1;i<=ind;i++) tree[cur].cnt[i]+=tree[tree[cur].left].cnt[i];
        if (tree[cur].right) for (register int i=1;i<=ind;i++) tree[cur].cnt[i]+=tree[tree[cur].right].cnt[i];
        tree[cur].cnt[tree[cur].val]++;
        tree[cur].sz=1;
        if (tree[cur].left) tree[cur].sz+=tree[tree[cur].left].sz;
        if (tree[cur].right) tree[cur].sz+=tree[tree[cur].right].sz;
    }
    inline int Create (int left,int right,int val,int priority)
    {
        ++tot;
        tree[tot].left=left;tree[tot].right=right;tree[tot].val=val;tree[tot].priority=priority;
        pushup(tot);return tot;
    }
    inline Pair split(int cur,int k)
    {
        if (!cur) return mp(0,0);
        pushdown(cur);
        int leftsz=tree[tree[cur].left].sz+1;
        if (k>=leftsz)
        {
            Pair splitted=split(tree[cur].right,k-leftsz);
            tree[cur].right=splitted.x;pushup(cur);
            return mp(cur,splitted.y);
        }
        else
        {
            Pair splitted=split(tree[cur].left,k);
            tree[cur].left=splitted.y;pushup(cur);
            return mp(splitted.x,cur);
        }
    }
    inline int merge(int root1,int root2)
    {
        if (!root1 || !root2) return root1^root2;
        pushdown(root1);pushdown(root2);
        if (tree[root1].priority<tree[root2].priority)
        {
            tree[root1].right=merge(tree[root1].right,root2);
            pushup(root1);return root1;
        }
        else
        {
            tree[root2].left=merge(root1,tree[root2].left);
            pushup(root2);return root2;
        }
    }
    inline void modify(int pos,int nv)
    {
        nv=toind[nv];
        Pair splitted=split(Root,pos-1),splitted2=split(splitted.y,1);
        Root=merge(splitted.x,merge(Create(0,0,nv,rand()),splitted2.y));
    }
    inline void reverse(int l,int r)
    {
        Pair splitted=split(Root,l-1),splitted2=split(splitted.y,r-l+1);
        tree[splitted2.x].flip^=1;
        Root=merge(splitted.x,merge(splitted2.x,splitted2.y));
    }
    inline void getcnt(int l,int r)
    {
        Pair splitted=split(Root,l-1),splitted2=split(splitted.y,r-l+1);
        for (register int i=1;i<=ind;i++) cnt[i]=tree[splitted2.x].cnt[i];
        Root=merge(splitted.x,merge(splitted2.x,splitted2.y));
    }
    inline void construct()
    {
        Root=0;tot=0;
        for (register int i=1;i<=n;i++) Root=merge(Root,Create(0,0,toind[a[i]],rand()));
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
    scanf("%d%d",&n,&q);
    for (register int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        if (!toind[a[i]]) toind[a[i]]=++ind,toval[ind]=a[i];
    }
    Treap::construct();int op,l,r,x;
    while (q--)
    {
        scanf("%d",&op);
        if (op==1)
        {
            scanf("%d%d",&l,&x);
            if (!toind[x]) toind[x]=++ind,toval[ind]=x;
            Treap::modify(l,x);
        }
        if (op==2)
        {
            scanf("%d%d",&l,&r);
            Treap::reverse(l,r);
        }
        if (op==3)
        {
            scanf("%d%d%d",&l,&r,&x);
            Treap::getcnt(l,r);wtot=0;
            for (register int i=1;i<=ind;i++)
            {
                int tmp=cnt[i],pw=1;
                while (tmp>pw)
                {
                    if (1ll*pw*toval[i]<=x) w[++wtot]=1ll*pw*toval[i];
                    tmp-=pw;pw<<=1;
                }
                if (tmp && 1ll*tmp*toval[i]<=x) w[++wtot]=1ll*tmp*toval[i];
            }
            dp[0][0]=1;
            for (register int i=1;i<=wtot;i++) dp[i]=dp[i-1]|(dp[i-1]<<w[i]);
            if (dp[wtot][x]==1) puts("Yes"); else puts("No");
        }
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}