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

const int MAXN=5e5;

int n,q;
int Root[MAXN*2];
char s[MAXN+48],t[MAXN+48];

namespace SegmentTree
{
    int lson[MAXN*20],rson[MAXN*20],maxn[MAXN*20],maxind[MAXN*20],tot;
    inline void init() {tot=0;}
    inline int Create() {++tot;maxn[tot]=0;return tot;}
    inline void pushup(int cur)
    {
        if (!lson[cur]) {maxn[cur]=maxn[rson[cur]];maxind[cur]=maxind[rson[cur]];return;}
        if (!rson[cur]) {maxn[cur]=maxn[lson[cur]];maxind[cur]=maxind[lson[cur]];return;}
        if (maxn[rson[cur]]>maxn[lson[cur]]) maxn[cur]=maxn[rson[cur]],maxind[cur]=maxind[rson[cur]];
        else maxn[cur]=maxn[lson[cur]],maxind[cur]=maxind[lson[cur]];
    }
    inline void insert(int &cur,int pos,int l,int r)
    {
        if (!cur) cur=Create();
        if (l==r) {maxn[cur]=1;maxind[cur]=l;return;}
        int mid=(l+r)>>1;
        if (pos<=mid) insert(lson[cur],pos,l,mid); else insert(rson[cur],pos,mid+1,r);
        pushup(cur);
    }
    inline int merge(int root1,int root2,int l,int r)
    {
        if (!root1 || !root2) return root1^root2;
        if (l==r) {maxn[root1]+=maxn[root2];return root1;}
        int mid=(l+r)>>1;
        lson[root1]=merge(lson[root1],lson[root2],l,mid);
        rson[root1]=merge(rson[root1],rson[root2],mid+1,r);
        pushup(root1);return root1;
    }
    inline Pair query(int cur,int left,int right,int l,int r)
    {
        if (!cur) return mp(-1,-1);
        if (left<=l && r<=right) return mp(maxn[cur],maxind[cur]);
        int mid=(l+r)>>1;Pair res=mp(-1,-1);
        if (left<=mid)
        {
            Pair tmp=query(lson[cur],left,right,l,mid);
            if (tmp.x>res.x || (tmp.x==res.x && tmp.y<res.y)) res=tmp;
        }
        if (mid+1<=right)
        {
            Pair tmp=query(rson[cur],left,right,mid+1,r);
            if (tmp.x>res.x || (tmp.x==res.x && tmp.y<res.y)) res=tmp;
        }
        return res;
    }
}

struct Query
{
    int l,r,pl,pr,ind;
    inline void input() {scanf("%d%d%d%d",&l,&r,&pl,&pr);}
}a[MAXN+48];
vector<Query> seq[MAXN+48];
Pair ans[MAXN+48];

namespace SAM
{
    int par[MAXN*2],nxt[MAXN*2][27],maxn[MAXN*2],root,last,tot;
    vector<int> v[MAXN*2];int anc[MAXN*2][21];
    vector<Query> Q[MAXN*2];
    inline void init() {root=tot=last=1;}
    inline void extend(char ch,int ind)
    {
        int p=last,np=++tot,w=ch-'a'+1;maxn[np]=maxn[p]+1;
        SegmentTree::insert(Root[np],ind,1,n);
        while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
        if (!p) {par[np]=root;last=np;return;}
        int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
        int nq=++tot;maxn[nq]=maxn[p]+1;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));
        par[nq]=par[q];par[q]=nq;par[np]=nq;
        while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
        last=np;
    }
    inline void insert(char s[],int ind)
    {
        last=root;int len=strlen(s+1);
        for (register int i=1;i<=len;i++) extend(s[i],ind);
    }
    inline void build() {for (register int i=2;i<=tot;i++) v[par[i]].pb(i);}
    inline void dfs(int cur,int father)
    {
        for (auto y : v[cur])
        {
            anc[y][0]=cur;
            for (register int i=1;i<=20;i++) anc[y][i]=anc[anc[y][i-1]][i-1];
            dfs(y,cur);
        }
    }
    inline int jump(int u,int len)
    {
        for (register int i=20;i>=0;i--)
        {
            int tmp=anc[u][i];
            if (maxn[tmp]>=len) u=tmp;
        }
        return u;
    }
    inline void go()
    {
        int len=strlen(s+1),cur=root,cnt=0;
        for (register int i=1;i<=len;i++)
        {
            int w=s[i]-'a'+1;
            while (cur && !nxt[cur][w]) cur=par[cur],cnt=maxn[cur];
            if (!cur) cur=root,cnt=0; else cur=nxt[cur][w],cnt++;
            for (auto item : seq[i])
            {
                int L=item.pr-item.pl+1;
                if (L>cnt) {ans[item.ind]=mp(0,item.l);continue;}
                int pt=jump(cur,L);Q[pt].pb(item);
            }
        }
    }
    inline void solve(int cur,int father)
    {
        for (auto y : v[cur])
        {
            solve(y,cur);
            Root[cur]=SegmentTree::merge(Root[cur],Root[y],1,n);
        }
        for (auto item : Q[cur])
        {
            Pair res=SegmentTree::query(Root[cur],item.l,item.r,1,n);
            if (res.x==-1) ans[item.ind]=mp(0,item.l); else ans[item.ind]=res;
        }
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
    scanf("%s",s+1);SAM::init();SegmentTree::init();
    scanf("%d",&n);for (register int i=1;i<=n;i++) scanf("%s",t+1),SAM::insert(t,i);
    scanf("%d",&q);for (register int i=1;i<=q;i++) a[i].input(),a[i].ind=i,seq[a[i].pr].pb(a[i]);
    SAM::build();SAM::dfs(SAM::root,-1);SAM::go();SAM::solve(SAM::root,-1);
    for (register int i=1;i<=q;i++) printf("%d %d\n",ans[i].y,ans[i].x);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}