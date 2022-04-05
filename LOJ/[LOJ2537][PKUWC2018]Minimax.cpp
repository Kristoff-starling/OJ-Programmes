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
const int MOD=998244353;
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
const int lim=MAXN;

int n;
vector<int> v[MAXN+48];
int Inv,p[MAXN+48],ans;

int vv[MAXN+48],vtot;
int table[MAXN+48];

int root[MAXN+48];
namespace SegmentTree
{
    int lson[MAXN*30+48],rson[MAXN*30+48],sum[MAXN*30+48],lazy[MAXN*30+48],tot;
    inline int Create()
    {
        ++tot;lson[tot]=rson[tot]=0;
        sum[tot]=0;lazy[tot]=1;
        return tot;
    }
    inline void pushdown(int cur)
    {
        if (lazy[cur]!=1)
        {
            lazy[lson[cur]]=1ll*lazy[lson[cur]]*lazy[cur]%MOD;sum[lson[cur]]=1ll*sum[lson[cur]]*lazy[cur]%MOD;
            lazy[rson[cur]]=1ll*lazy[rson[cur]]*lazy[cur]%MOD;sum[rson[cur]]=1ll*sum[rson[cur]]*lazy[cur]%MOD;
            lazy[cur]=1;
        }
    }
    inline void pushup(int cur)
    {
        sum[cur]=0;
        if (lson[cur]) Add(sum[cur],sum[lson[cur]]);
        if (rson[cur]) Add(sum[cur],sum[rson[cur]]);
    }
    inline void insert(int &cur,int pos,int val,int l,int r)
    {
        if (!cur) cur=Create();
        if (l==r) {sum[cur]=val;lazy[cur]=1;return;}
        pushdown(cur);int mid=(l+r)>>1;
        if (pos<=mid) insert(lson[cur],pos,val,l,mid); else insert(rson[cur],pos,val,mid+1,r);
        pushup(cur);
    }
    inline int merge(int root1,int root2,int sum1,int sum2,int p,int l,int r)
    {
        if (!root1 && !root2) return 0;
        if (!root2)
        {
            lazy[root1]=1ll*lazy[root1]*add(sub(sum2-2ll*p*sum2%MOD)+p)%MOD;
            sum[root1]=1ll*sum[root1]*add(sub(sum2-2ll*p*sum2%MOD)+p)%MOD;
            return root1;
        }
        if (!root1)
        {
            lazy[root2]=1ll*lazy[root2]*add(sub(sum1-2ll*p*sum1%MOD)+p)%MOD;
            sum[root2]=1ll*sum[root2]*add(sub(sum1-2ll*p*sum1%MOD)+p)%MOD;
            return root2;
        }
        pushdown(root1);pushdown(root2);
        int mid=(l+r)>>1;
        lson[root1]=merge(lson[root1],lson[root2],add(sum1+(rson[root1]?sum[rson[root1]]:0)),add(sum2+(rson[root2]?sum[rson[root2]]:0)),p,l,mid);
        rson[root1]=merge(rson[root1],rson[root2],sum1,sum2,p,mid+1,r);
        pushup(root1);return root1;
    }
    int cnt=0;
    inline void solve(int cur,int l,int r)
    {
        if (!cur) return;
        if (l==r)
        {
            cnt++;Add(ans,1ll*cnt*table[l]%MOD*sum[cur]%MOD*sum[cur]%MOD);
            return;
        }
        pushdown(cur);int mid=(l+r)>>1;
        solve(lson[cur],l,mid);solve(rson[cur],mid+1,r);
    }
}

inline void dfs(int cur)
{
    if (!int(v[cur].size())) root[cur]=SegmentTree::Create(),SegmentTree::insert(root[cur],p[cur],1,1,lim);
    if (int(v[cur].size())==1) dfs(v[cur][0]),root[cur]=root[v[cur][0]];
    if (int(v[cur].size())==2)
    {
        int y1=v[cur][0],y2=v[cur][1];
        dfs(y1);dfs(y2);
        root[cur]=SegmentTree::merge(root[y1],root[y2],0,0,p[cur],1,lim);
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
    io.Get(n);int x;
    for (register int i=1;i<=n;i++) io.Get(x),v[x].pb(i);
    Inv=quick_pow(10000,MOD-2);
    for (register int i=1;i<=n;i++)
    {
        io.Get(p[i]);
        if (int(v[i].size())) assert(p[i]<=10000),p[i]=1ll*p[i]*Inv%MOD;
        else vv[++vtot]=p[i];
    }
    sort(vv+1,vv+vtot+1);
    for (register int i=1;i<=n;i++)
        if (!int(v[i].size()))
        {
            int tmp=lower_bound(vv+1,vv+vtot+1,p[i])-vv;
            table[tmp]=p[i];p[i]=tmp;
        }
    dfs(1);SegmentTree::solve(root[1],1,lim);
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}