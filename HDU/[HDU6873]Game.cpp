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

const int MAXN=1e6;

int n,q;
int a[MAXN+48];

namespace Treap
{
    int Root,lson[MAXN+48],rson[MAXN+48],priority[MAXN+48],val[MAXN+48],minn[MAXN+48],sz[MAXN+48],tot;LL sum[MAXN+48];
    inline void init() {tot=0;minn[0]=1e9;sz[0]=0;sum[0]=0;Root=0;}
    inline int Create(int vv) {++tot;lson[tot]=rson[tot]=0;priority[tot]=rand();val[tot]=minn[tot]=sum[tot]=vv;sz[tot]=1;return tot;}
    inline void pushup(int cur) {minn[cur]=val[cur];check_min(minn[cur],min(minn[lson[cur]],minn[rson[cur]]));sz[cur]=sz[lson[cur]]+sz[rson[cur]]+1;sum[cur]=val[cur];sum[cur]+=sum[lson[cur]]+sum[rson[cur]];}
    inline Pair split_size(int root,int key)
    {
        if (!root) return mp(0,0);
        if (key>=sz[lson[root]]+1)
        {
            Pair splitted=split_size(rson[root],key-sz[lson[root]]-1);
            rson[root]=splitted.x;pushup(root);return mp(root,splitted.y);
        }
        else
        {
            Pair splitted=split_size(lson[root],key);
            lson[root]=splitted.y;pushup(root);return mp(splitted.x,root);
        }
    }
    inline Pair split_val(int root,int key)
    {
        if (!root) return mp(0,0);
        if (minn[rson[root]]<key)
        {
            Pair splitted=split_val(rson[root],key);
            rson[root]=splitted.x;pushup(root);return mp(root,splitted.y);
        }
        if (val[root]<key) {int tmp=rson[root];rson[root]=0;pushup(root);return mp(root,tmp);}
        Pair splitted=split_val(lson[root],key);
        lson[root]=splitted.y;pushup(root);return mp(splitted.x,root);
    }
    inline int merge(int root1,int root2)
    {
        if (!root1 || !root2) return root1^root2;
        if (priority[root1]<=priority[root2]) {rson[root1]=merge(rson[root1],root2);pushup(root1);return root1;}
        else {lson[root2]=merge(root1,lson[root2]);pushup(root2);return root2;}
    }
    inline void build() {rep(i,1,n) Root=merge(Root,Create(a[i]));}
    inline LL Push(int pos,int height)
    {
        Pair splitted=split_size(Root,pos);
        Pair splitted2=split_val(splitted.x,height);
        if (!splitted2.x)
        {
            Root=merge(merge(splitted2.x,splitted2.y),splitted.y);
            return 0;
        }
        LL res=sum[splitted2.y]-1ll*sz[splitted2.y]*(height-1);
        int sz1=sz[splitted2.x];
        Pair splitted3=split_size(splitted2.x,sz1-1);
        Pair splitted4=split_size(splitted2.y,1);
        int tmp=merge(splitted3.x,Create(val[splitted3.y]+val[splitted4.x]-height+1));
        tmp=merge(tmp,splitted4.y);tmp=merge(tmp,Create(height-1));
        Root=merge(tmp,splitted.y);return res;
    }
    inline int query(int pos)
    {
        Pair splitted=split_size(Root,pos);
        int Sz=sz[splitted.x];Pair splitted2=split_size(splitted.x,Sz-1);
        int res=val[splitted2.y];
        Root=merge(merge(splitted2.x,splitted2.y),splitted.y);
        return res;
    }
    inline void dfs(int cur)
    {
        if (!cur) return;
        dfs(lson[cur]);printf("%d ",val[cur]);dfs(rson[cur]);
    }
    inline void print() {dfs(Root);}
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca,op,x,y;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&q);rep(i,1,n) scanf("%d",a+i);
        Treap::init();Treap::build();
        while (q--)
        {
            scanf("%d",&op);
            if (op==1)
            {
                scanf("%d%d",&x,&y);
                printf("%lld\n",Treap::Push(x,y));
            }
            else
            {
                scanf("%d",&x);
                printf("%d\n",Treap::query(x));
            }
        }
        Treap::print();puts("");
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}