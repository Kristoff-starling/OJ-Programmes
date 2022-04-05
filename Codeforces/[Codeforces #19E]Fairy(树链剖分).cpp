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

const int MAXN=1e4;

int n,m;
vector<Pair> v[MAXN+48];

bool intree[MAXN+48],vv[MAXN+48];
int fa[MAXN+48],faind[MAXN+48],son[MAXN+48],sz[MAXN+48],depth[MAXN+48],top[MAXN+48];
int tpos[MAXN+48],seq[MAXN+48],ind;
inline void dfs1(int cur,int father)
{
    fa[cur]=father;sz[cur]=1;son[cur]=0;
    vv[cur]=true;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        if (!intree[v[cur][i].y]) continue;
        if (y!=father)
        {
            depth[y]=depth[cur]+1;faind[y]=v[cur][i].y;
            dfs1(y,cur);sz[cur]+=sz[y];
            if (!son[cur] || sz[son[cur]]<sz[y]) son[cur]=y;
        }
    }
}

inline void dfs2(int cur,int tp)
{
    seq[++ind]=cur;tpos[cur]=ind;top[cur]=tp;
    if (son[cur]) dfs2(son[cur],tp);
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        if (!intree[v[cur][i].y]) continue;
        if (y!=fa[cur] && y!=son[cur]) dfs2(y,y);
    }
}

namespace SegmentTree
{
    int lazy[MAXN*4];
    inline void init() {for (register int i=1;i<=ind*4;i++) lazy[i]=0;}
    inline void pushdown(int cur)
    {
        lazy[cur<<1]+=lazy[cur];
        lazy[cur<<1|1]+=lazy[cur];
        lazy[cur]=0;
    }
    inline void modify(int cur,int left,int right,int delta,int l,int r)
    {
        if (left>right) return;
        if (left<=l && r<=right) {lazy[cur]+=delta;return;}
        pushdown(cur);int mid=(l+r)>>1;
        if (left<=mid) modify(cur<<1,left,right,delta,l,mid);
        if (mid+1<=right) modify(cur<<1|1,left,right,delta,mid+1,r);
    }
    inline int query(int cur,int pos,int l,int r)
    {
        if (l==r) return lazy[cur];
        pushdown(cur);int mid=(l+r)>>1;
        if (pos<=mid) return query(cur<<1,pos,l,mid); else return query(cur<<1|1,pos,mid+1,r);
    }
}

inline void update(int u,int v,int delta)
{
    int tp1=top[u],tp2=top[v];
    while (tp1!=tp2)
    {
        if (depth[tp1]<depth[tp2])
        {
            swap(u,v);
            swap(tp1,tp2);
        }
        SegmentTree::modify(1,tpos[tp1],tpos[u],delta,1,ind);
        u=fa[tp1];tp1=top[u];
    }
    if (depth[u]<depth[v]) swap(u,v);
    SegmentTree::modify(1,tpos[v]+1,tpos[u],delta,1,ind);
}

int cntodd,fnum,visited[MAXN+48],d[MAXN+48];
vector<Pair> Odd,Even;
inline void Dfs(int cur,int father)
{
    visited[cur]=1;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        if (!visited[y])
        {
            d[y]=d[cur]+1;
            intree[v[cur][i].y]=true;
            Dfs(y,cur);
        }
        else if (y!=father && visited[y]==1)
        {
            if ((d[cur]&1)==(d[y]&1))
            {
                cntodd++;
                Odd.pb(mp(cur,y));
                if (cntodd==1) fnum=v[cur][i].y;
            }
            else
                Even.pb(mp(cur,y));
        }
    }
    visited[cur]=2;
}

vector<int> edge;

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);int x,y;
    for (register int i=1;i<=m;i++)
    {
        io.Get(x);io.Get(y);
        v[x].pb(mp(y,i));v[y].pb(mp(x,i));
    }
    int ocnt=0;
    for (register int i=1;i<=n;i++)
        if (!vv[i])
        {
            int tmp=cntodd;
            d[i]=1;Dfs(i,-1);
            if (cntodd!=tmp) ocnt++; else continue;
            depth[i]=1;dfs1(i,-1);ind=0;dfs2(i,i);
            for (auto item : Odd) update(item.x,item.y,1);
            for (auto item : Even) update(item.x,item.y,-1);
        }
    if (ocnt>1) {printf("0\n");return 0;}
    if (!cntodd)
    {
        printf("%d\n",m);
        for (register int i=1;i<=m;i++) printf("%d ",i);
        printf("\n");return 0;
    }
    int Ans=0;
    for (register int i=2;i<=n;i++)
        if (tpos[i] && SegmentTree::query(1,tpos[i],1,ind)==cntodd) Ans++,edge.pb(faind[i]);
    if (cntodd==1) Ans++,edge.pb(fnum);
    printf("%d\n",Ans);
    sort(edge.begin(),edge.end());
    for (register int i=0;i<int(edge.size());i++) printf("%d ",edge[i]);
    printf("\n");
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}