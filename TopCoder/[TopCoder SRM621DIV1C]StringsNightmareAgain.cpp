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

string S;char s[MAXN+48];
LL ans=0;

namespace SAM
{
    int root,last,nxt[MAXN*2][4],par[MAXN*2],minocc[MAXN*2],maxocc[MAXN*2],maxn[MAXN*2],tot;
    vector<int> v[MAXN*2];
    inline void init() {root=last=tot=1;memset(nxt,0,sizeof(nxt));}
    inline void extend(char ch,int ind)
    {
        int p=last,np=++tot,w=ch-'a'+1;maxn[np]=maxn[p]+1;minocc[np]=maxocc[np]=ind;
        while (p && !nxt[p][w]) nxt[p][w]=np,p=par[p];
        if (!p) {par[np]=root;last=np;return;}
        int q=nxt[p][w];if (maxn[q]==maxn[p]+1) {par[np]=q;last=np;return;}
        int nq=++tot;minocc[nq]=MAXN+1;maxocc[nq]=0;memcpy(nxt[nq],nxt[q],sizeof(nxt[q]));maxn[nq]=maxn[p]+1;
        par[nq]=par[q];par[q]=par[np]=nq;
        while (p && nxt[p][w]==q) nxt[p][w]=nq,p=par[p];
        last=np;
    }
    inline void build()
    {
        for (register int i=1;i<=tot;i++) v[i].clear();
        for (register int i=2;i<=tot;i++) v[par[i]].pb(i);
    }
    inline void dfs(int cur)
    {
        for (register int i=0;i<int(v[cur].size());i++)
        {
            int y=v[cur][i];
            dfs(y);check_min(minocc[cur],minocc[y]);check_max(maxocc[cur],maxocc[y]);
        }
        if (cur!=root && minocc[cur]<maxocc[cur])
        {
            int r=min(maxn[cur],maxocc[cur]-minocc[cur]),l=maxn[par[cur]]+1;
            if (r>=l) ans+=r-l+1;
        }
    }
}

class StringsNightmareAgain
{
    public:
        inline LL UniqueSubstrings(LL a,LL b,LL c,LL d,LL n)
        {
            S="";
            for (register int i=0;i<n;++i) S+="a";
            for (register int i=0;i<a;++i) b=(b*c+d)%n,S[b]='b';
            for (register int i=1;i<=n;i++) s[i]=S[i-1];
            SAM::init();for (register int i=1;i<=n;i++) SAM::extend(s[i],i);
            SAM::build();ans=0;SAM::dfs(SAM::root);
            return ans;
        }
};

#ifdef LOCAL
int main ()
{
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
    int nn,aa,bb,cc,dd;
    StringsNightmareAgain A;
    while (cin>>aa>>bb>>cc>>dd>>nn) cout<<A.UniqueSubstrings(aa,bb,cc,dd,nn)<<endl;
    io.flush();
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
    return 0;
}
#endif