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
#define LOCAL true

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
char s[MAXN+48];
vector<int> v[MAXN+48];

bool visited[MAXN+48];

int sz[MAXN+48];
inline void dfs(int cur,int father)
{
    sz[cur]=1;
    for (auto y : v[cur])
        if (y!=father && !visited[y]) dfs(y,cur),sz[cur]+=sz[y];
}

inline int find_root(int cur,int father,int Sz)
{
    for (auto y : v[cur])
        if (y!=father && !visited[y] && sz[y]>=Sz/2) return find_root(y,cur,Sz);
    return cur;
}

int cnt[MAXN+48];LL ans;
stack<int> sta;

inline void dfs1(int cur,int father)
{
    bool ispop=false;
    if (s[cur]==1)
    {
        if (!sta.empty() && sta.top()==0) ispop=true,sta.pop(); else sta.push(1);
    }
    else sta.push(0);
    for (auto y : v[cur])
        if (y!=father && !visited[y]) dfs1(y,cur);
    if (sta.empty() || sta.top()) ans+=cnt[int(sta.size())];
    if (s[cur]==1 && ispop) sta.push(0); else sta.pop();
}

inline void dfs2(int cur,int father)
{
    bool ispop=false;
    if (s[cur]==0)
    {
        if (!sta.empty() && sta.top()==1) ispop=true,sta.pop(); else sta.push(0);
    }
    else sta.push(1);
    for (auto y : v[cur])
        if (y!=father && !visited[y]) dfs2(y,cur);
    if (sta.empty() || !sta.top()) cnt[int(sta.size())]++;
    if (s[cur]==0 && ispop) sta.push(1); else sta.pop();
}

inline void dfs3(int cur,int father)
{
    bool ispop=false;
    if (s[cur]==0)
    {
        if (!sta.empty() && sta.top()==1) ispop=true,sta.pop(); else sta.push(0);
    }
    else sta.push(1);
    for (auto y : v[cur])
        if (y!=father && !visited[y]) dfs3(y,cur);
    if (sta.empty()) ans++;
    if (s[cur]==0 && ispop) sta.push(1); else sta.pop();
}

inline void dfs4(int cur,int father)
{
    bool ispop=false;
    if (s[cur]==1)
    {
        if (!sta.empty() && sta.top()==0) ispop=true,sta.pop(); else sta.push(1);
    }
    else sta.push(0);
    for (auto y : v[cur])
        if (y!=father && !visited[y]) dfs4(y,cur);
    if (sta.empty()) ans++;
    if (s[cur]==1 && ispop) sta.push(0); else sta.pop();
}

inline void solve(int cur)
{
    dfs(cur,-1);int rt=find_root(cur,-1,sz[cur]);
    for (register int iter=0;iter<int(v[rt].size());iter++)
    {
        int y=v[rt][iter];
        if (visited[y]) continue;
        sta.push(s[rt]);dfs3(y,rt);sta.pop();
        sta.push(s[rt]);dfs4(y,rt);sta.pop();
    }
    for (register int i=0;i<=sz[cur]+10;i++) cnt[i]=0;
    for (register int iter=0;iter<int(v[rt].size());iter++)
    {
        int y=v[rt][iter];
        if (visited[y]) continue;
        dfs1(y,rt);
        sta.push(s[rt]);dfs2(y,rt);sta.pop();
    }
    for (register int i=0;i<=sz[cur]+10;i++) cnt[i]=0;
    for (register int iter=int(v[rt].size())-1;iter>=0;iter--)
    {
        int y=v[rt][iter];
        if (visited[y]) continue;
        dfs1(y,rt);
        sta.push(s[rt]);dfs2(y,rt);sta.pop();
    }
    visited[rt]=true;
    for (auto y : v[rt]) if (!visited[y]) solve(y);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.getstring(s+1);
    for (register int i=1;i<=n;i++) s[i]=((s[i]=='(')?0:1);
    int x,y;for (register int i=1;i<=n-1;i++) io.Get(x),io.Get(y),v[x].pb(y),v[y].pb(x);
    solve(1);printf("%lld\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}