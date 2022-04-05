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
const int magic=48;
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

const int MAXN=2e5;

int n;

vector<int> v[MAXN+48];
int son[MAXN+48],depth[MAXN+48],cntdepth[MAXN+48],level[MAXN+48];LL curson[MAXN+48];
int pos[MAXN+48],ind;LL val[MAXN+48];
LL f[magic+48][magic+48];
LL ans[MAXN+48],fans[MAXN+48];

inline void dfs1(int cur)
{
    level[cur]=depth[cur];son[cur]=0;cntdepth[depth[cur]]++;
    for (auto y : v[cur])
    {
        depth[y]=depth[cur]+1;dfs1(y);
        if (level[y]>level[cur]) level[cur]=level[y],son[cur]=y;
    }
}

inline void dfs2(int cur)
{
    pos[cur]=++ind;
    if (son[cur]) dfs2(son[cur]);
    for (auto y : v[cur]) if (y!=son[cur]) dfs2(y);
}

inline void solve(int cur,bool isheavy)
{
    for (auto y : v[cur]) if (y!=son[cur]) solve(y,false);
    if (son[cur]) solve(son[cur],true);
    for (auto y : v[cur])
    {
        if (y==son[cur]) continue;
        int maxdepth=level[y]-depth[y];
        for (register int d=0;d<=maxdepth;d++)
        {
            curson[d]=val[pos[y]+d];
            for (register int dd=d*2+1;dd<=maxdepth;dd+=d+1) val[pos[y]+d]+=val[pos[y]+dd];
            if (d+1<=magic)
                ans[d+1]+=1ll*val[pos[y]+d]*f[d+1][(depth[y]+d)%(d+1)];
            else
                for (register int dd=d+1;dd<=level[cur]-depth[cur];dd+=d+1)
                    ans[d+1]+=1ll*val[pos[y]+d]*val[pos[cur]+dd];
        }
        for (register int d=0;d<=maxdepth;d++) val[pos[cur]+d+1]+=curson[d];
        for (register int d=0;d<=maxdepth;d++)
            for (register int i=1;i<=magic;i++)
                f[i][(depth[y]+d)%i]+=curson[d];
    }
    val[pos[cur]]++;
    if (isheavy)
    {
        for (register int i=1;i<=magic;i++)
            f[i][depth[cur]%i]++;
    }
    else
    {
        for (register int d=1;d<=level[cur]-depth[cur];d++)
            for (register int i=1;i<=magic;i++)
                f[i][(depth[cur]+d)%i]=0;
    }
}

int mu[MAXN+48];bool isprime[MAXN+48];int prime[MAXN+48],tot;
inline void init_mu()
{
    mu[1]=1;memset(isprime,true,sizeof(isprime));
    for (register int i=2;i<=n;i++)
    {
        if (isprime[i]) prime[++tot]=i,mu[i]=-1;
        for (register int j=1;j<=tot && 1ll*i*prime[j]<=n;j++)
        {
            isprime[i*prime[j]]=false;
            if (i%prime[j]==0) {mu[i*prime[j]]=0;break;} else mu[i*prime[j]]=-mu[i];
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
    int x;scanf("%d",&n);
    for (register int i=2;i<=n;i++) scanf("%d",&x),v[x].pb(i);
    depth[1]=0;dfs1(1);dfs2(1);
    for (register int i=n;i>=0;i--) cntdepth[i]+=cntdepth[i+1];
    solve(1,false);
    init_mu();
    for (register int i=1;i<=n-1;i++)
        for (register int d=i;d<=n-1;d+=i)
            fans[i]+=ans[d]*mu[d/i];
    for (register int i=1;i<=n-1;i++) printf("%lld\n",fans[i]+cntdepth[i]);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}