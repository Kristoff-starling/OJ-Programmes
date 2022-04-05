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
template<typename T> inline T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
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

int n;
vector<int> v[MAXN+48];
int depth[MAXN+48],anc[MAXN+48][21];
Pair a[MAXN+48];int m;int LCA[MAXN+48],s1[MAXN+48],s2[MAXN+48];
int ind,in[MAXN+48],out[MAXN+48],sum[MAXN+48],sum2[MAXN+48];

void dfs(int cur,int father)
{
    depth[cur]=depth[father]+1;anc[cur][0]=father;in[cur]=++ind;
    rep(i,1,20) anc[cur][i]=anc[anc[cur][i-1]][i-1];
    for (auto y : v[cur]) if (y!=father) dfs(y,cur);
    out[cur]=ind;
}

int jump(int x,int y)
{
    REP(i,20,0) if (depth[anc[x][i]]>depth[y]) x=anc[x][i];
    return x;
}

int getlca(int x,int y)
{
    if (depth[x]<depth[y]) swap(x,y);
    REP(i,20,0) if (depth[anc[x][i]]>=depth[y]) x=anc[x][i];
    if (x==y) return x;
    REP(i,20,0) if (anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
    return anc[x][0];
}

int cnt[MAXN+48];
map<Pair,int> m1;
map<pair<int,Pair>,int> m2;

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d",&n);int x,y;
    rep(i,1,n-1) scanf("%d%d",&x,&y),v[x].pb(y),v[y].pb(x);
    scanf("%d",&m);rep(i,1,m) scanf("%d%d",&a[i].x,&a[i].y);
    dfs(1,-1);
    rep(i,1,m)
    {
        LCA[i]=getlca(a[i].x,a[i].y);
        if (a[i].x==LCA[i]) s1[i]=-1; else s1[i]=jump(a[i].x,LCA[i]);
        if (a[i].y==LCA[i]) s2[i]=-1; else s2[i]=jump(a[i].y,LCA[i]);
        if (s1[i]<s2[i]) swap(s1[i],s2[i]);
        cnt[LCA[i]]++;
        if (s1[i]!=-1) m1[mp(LCA[i],s1[i])]++;
        if (s2[i]!=-1) m1[mp(LCA[i],s2[i])]++;
        if (s1[i]!=-1 && s2[i]!=-1) m2[mp(LCA[i],mp(s1[i],s2[i]))]++;
    }
    LL ans=0;
    rep(i,1,m)
    {
        ans+=(cnt[LCA[i]]-1);
        if (s1[i]!=-1) ans-=(m1[mp(LCA[i],s1[i])]-1);
        if (s2[i]!=-1) ans-=(m1[mp(LCA[i],s2[i])]-1);
        if (s1[i]!=-1 && s2[i]!=-1) ans+=(m2[mp(LCA[i],mp(s1[i],s2[i]))]-1);
    }
    ans>>=1;
    rep(i,1,m)
    {
        if (a[i].x!=LCA[i])
        {
            x=a[i].x;y=jump(a[i].x,LCA[i]);
            sum[in[x]]++;sum[in[anc[y][0]]]--;
        }
        if (a[i].y!=LCA[i])
        {
            x=a[i].y;y=jump(a[i].y,LCA[i]);
            sum[in[x]]++;sum[in[anc[y][0]]]--;
        }
    }
    rep(i,2,n) sum[i]+=sum[i-1];
    rep(i,1,m)
    {
        if (depth[a[i].x]-depth[LCA[i]]>=2)
        {
            x=a[i].x;y=jump(x,LCA[i]);y=jump(x,y);
            sum2[in[x]]++;sum2[in[anc[y][0]]]--;
        }
        if (depth[a[i].y]-depth[LCA[i]]>=2)
        {
            x=a[i].y;y=jump(x,LCA[i]);y=jump(x,y);
            sum2[in[x]]++;sum2[in[anc[y][0]]]--;
        }
    }
    rep(i,2,n) sum2[i]+=sum2[i-1];
    rep(i,1,m)
    {
        ans+=(sum[out[LCA[i]]]-sum[in[LCA[i]]-1]);
        if (s1[i]!=-1) ans-=(sum2[out[s1[i]]]-sum2[in[s1[i]]-1]);
        if (s2[i]!=-1) ans-=(sum2[out[s2[i]]]-sum2[in[s2[i]]-1]);
    }
    printf("%lld\n",ans);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}