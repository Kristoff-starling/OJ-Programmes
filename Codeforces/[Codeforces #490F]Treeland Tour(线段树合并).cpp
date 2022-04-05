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

int n;
vector<int> v[MAXN+48];
int r[MAXN+48],val[MAXN+48],cnt;
int ans=0;

int root[MAXN+48];
namespace SegmentTree
{
    int lson[MAXN*4],rson[MAXN*4],lis[MAXN*4],lds[MAXN*4],tot;
    inline void init()
    {
        memset(root,0,sizeof(root));
        memset(lson,0,sizeof(lson));
        memset(rson,0,sizeof(rson));
        memset(lis,0,sizeof(lis));
        memset(lds,0,sizeof(lds));
        tot=0;
    }
    inline void pushup(int cur)
    {
        lis[cur]=lds[cur]=0;
        if (lson[cur]) check_max(lis[cur],lis[lson[cur]]),check_max(lds[cur],lds[lson[cur]]);
        if (rson[cur]) check_max(lis[cur],lis[rson[cur]]),check_max(lds[cur],lds[rson[cur]]);
    }
    inline int merge(int root1,int root2)
    {
        if (!root1 || !root2) return root1^root2;
        check_max(ans,lis[lson[root1]]+lds[rson[root2]]);
        check_max(ans,lis[lson[root2]]+lds[rson[root1]]);
        lson[root1]=merge(lson[root1],lson[root2]);rson[root1]=merge(rson[root1],rson[root2]);
        pushup(root1);return root1;
    }
    inline void modify(int &cur,int pos,int nv,int l,int r,int type)
    {
        if (!cur) cur=++tot;
        if (l==r)
        {
            if (type==1) check_max(lis[cur],nv); else check_max(lds[cur],nv);
            return;
        }
        int mid=(l+r)>>1;
        if (pos<=mid) modify(lson[cur],pos,nv,l,mid,type); else modify(rson[cur],pos,nv,mid+1,r,type);
        pushup(cur);
    }
    inline int query(int &cur,int left,int right,int l,int r,int type)
    {
        if (!cur) return 0;
        if (left<=l && r<=right) {if (type==1) return lis[cur]; else return lds[cur];}
        int mid=(l+r)>>1,res=0;
        if (left<=mid) check_max(res,query(lson[cur],left,right,l,mid,type));
        if (mid+1<=right) check_max(res,query(rson[cur],left,right,mid+1,r,type));
        return res;
    }
}

inline void dfs(int cur,int father)
{
    int maxn1=0,maxn2=0,cmaxn1,cmaxn2;
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i];
        if (y!=father)
        {
            dfs(y,cur);
            cmaxn1=SegmentTree::query(root[y],1,r[cur]-1,1,cnt,1);
            cmaxn2=SegmentTree::query(root[y],r[cur]+1,cnt,1,cnt,2);
            check_max(ans,maxn1+cmaxn2+1);check_max(ans,cmaxn1+maxn2+1);
            check_max(maxn1,cmaxn1);check_max(maxn2,cmaxn2);
            root[cur]=SegmentTree::merge(root[cur],root[y]);
        }
    }
    SegmentTree::modify(root[cur],r[cur],maxn1+1,1,cnt,1);
    SegmentTree::modify(root[cur],r[cur],maxn2+1,1,cnt,2);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);for (register int i=1;i<=n;i++) io.Get(r[i]),val[i]=r[i];
    int x,y;for (register int i=1;i<=n-1;i++) io.Get(x),io.Get(y),v[x].pb(y),v[y].pb(x);
    sort(val+1,val+n+1);cnt=unique(val+1,val+n+1)-(val+1);
    for (register int i=1;i<=n;i++) r[i]=lower_bound(val+1,val+cnt+1,r[i])-val;
    SegmentTree::init();
    dfs(1,-1);printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}