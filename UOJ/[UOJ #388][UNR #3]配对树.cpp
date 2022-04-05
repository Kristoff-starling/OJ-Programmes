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

const int MAXN=1e5;

int n,m;

vector<Pair> v[MAXN+48];
int a[MAXN+48];vector<int> pos[MAXN+48];

inline int Count(int l,int r,int type) //0: even; 1: odd;
{
    int res=(r-l+1)/2;
    if ((l&1)==(r&1) && (l&1)==type) res++;
    return res;
}

int root[MAXN+48];
namespace SegmentTree
{
    int xsum[MAXN*40+48],cnt[MAXN*40+48][2][2],lson[MAXN*40+48],rson[MAXN*40+48],tot;
    inline int Create(int l,int r)
    {
        ++tot;lson[tot]=rson[tot]=0;
        xsum[tot]=0;
        cnt[tot][0][1]=cnt[tot][1][1]=0;
        cnt[tot][0][0]=Count(l,r,0);cnt[tot][1][0]=Count(l,r,1);
        return tot;
    }
    inline void pushup(int cur)
    {
        if (!lson[cur] && !rson[cur]) return;
        int Cnt[2][2];memcpy(Cnt,cnt[rson[cur]],sizeof(cnt[rson[cur]]));
        if (xsum[lson[cur]]) swap(Cnt[0][0],Cnt[0][1]),swap(Cnt[1][0],Cnt[1][1]);
        for (register int i=0;i<=1;i++)
            for (register int j=0;j<=1;j++)
                cnt[cur][i][j]=cnt[lson[cur]][i][j]+Cnt[i][j];
        xsum[cur]=xsum[lson[cur]]^xsum[rson[cur]];
    }
    inline void insert(int &cur,int pos,int l,int r)
    {
        if (!cur) cur=Create(l,r);
        if (l==r)
        {
            xsum[cur]=1;
            memset(cnt[cur],0,sizeof(cnt[cur]));
            cnt[cur][l&1][1]=1;
            return;
        }
        int mid=(l+r)>>1;
        if (!lson[cur]) lson[cur]=Create(l,mid);
        if (!rson[cur]) rson[cur]=Create(mid+1,r);
        if (pos<=mid) insert(lson[cur],pos,l,mid); else insert(rson[cur],pos,mid+1,r);
        pushup(cur);
    }
    inline int merge(int root1,int root2,int l,int r)
    {
        if (!root1 || !root2) return root1^root2;
        if (l==r)
        {
            if (!xsum[root1] && !xsum[root2]) return root1;
            xsum[root1]=1;
            memset(cnt[root1],0,sizeof(cnt[root1]));
            cnt[root1][l&1][1]=1;
            return root1;
        }
        int mid=(l+r)>>1;
        lson[root1]=merge(lson[root1],lson[root2],l,mid);
        rson[root1]=merge(rson[root1],rson[root2],mid+1,r);
        pushup(root1);return root1;
    }
    inline int query(int cur) {if (!cur) return 0;return add(1ll*cnt[cur][0][0]*cnt[cur][0][1]%MOD+1ll*cnt[cur][1][0]*cnt[cur][1][1]%MOD);}
}

int ans=0;

inline void dfs(int cur,int father,int faedge)
{
    for (register int i=0;i<int(v[cur].size());i++)
    {
        int y=v[cur][i].x;
        if (y!=father) dfs(y,cur,v[cur][i].y),root[cur]=SegmentTree::merge(root[cur],root[y],0,m);
    }
    if (father!=-1) Add(ans,1ll*faedge*SegmentTree::query(root[cur])%MOD);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&m);int x,y,c;
    for (register int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&x,&y,&c);
        v[x].pb(mp(y,c));v[y].pb(mp(x,c));
    }
    for (register int i=1;i<=m;i++) scanf("%d",a+i),pos[a[i]].pb(i);
    for (register int i=1;i<=n;i++)
        for (auto p : pos[i])
            SegmentTree::insert(root[i],p,0,m);
    dfs(1,-1,-1);printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}