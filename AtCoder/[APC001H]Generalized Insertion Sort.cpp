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

const int MAXN=2000;

int n;
int fa[MAXN+48],a[MAXN+48];
vector<int> v[MAXN+48],anslist;

int path[MAXN+48],tot;
inline void Rotate(int cur)
{
    tot=0;
    for (register int tmp=cur;tmp;tmp=fa[tmp]) path[++tot]=tmp;
    reverse(path+1,path+tot+1);int val=a[path[1]];
    for (register int i=1;i<=tot-1;i++) a[path[i]]=a[path[i+1]];
    a[path[tot]]=val;
}

bool isleaf[MAXN+48],isblue[MAXN+48],isblack[MAXN+48],taboo[MAXN+48];int depth[MAXN+48];
inline void dfs(int cur)
{
    int cnt=0;isleaf[cur]=true;
    for (auto y : v[cur])
        if (!taboo[y]) cnt++,depth[y]=depth[cur]+1,dfs(y),isleaf[cur]&=isleaf[y];
    isleaf[cur]&=(cnt<=1);
}

inline int get_bottom(int cur)
{
    for (auto y : v[cur]) if (!taboo[y]) return get_bottom(y);
    return cur;
}

int maxdepth,maxind;
inline void Dfs(int cur,bool red_exist)
{
    red_exist|=isleaf[a[cur]];
    if (red_exist && depth[cur]>maxdepth) maxdepth=depth[cur],maxind=cur;
    for (auto y : v[cur]) if (!taboo[y] && !isblue[a[y]] && !isblack[a[y]]) Dfs(y,red_exist);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);
    for (register int i=2;i<=n;i++) io.Get(fa[i]),fa[i]++,v[fa[i]].pb(i);
    for (register int i=1;i<=n;i++) io.Get(a[i]),a[i]++;
    while (!taboo[1])
    {
        memset(isleaf,false,sizeof(isleaf));memset(isblue,false,sizeof(isblue));memset(isblack,false,sizeof(isblack));
        depth[1]=1;dfs(1);
        int cnt=0,tar=0;for (register int i=1;i<=n;i++) if (isleaf[i]) tar++;
        while (cnt<tar)
        {
            if (isleaf[a[1]])
            {
                int tmp=get_bottom(a[1]);
                while (isblue[a[tmp]] && depth[a[tmp]]>depth[a[1]]) tmp=fa[tmp];
                anslist.pb(tmp);Rotate(tmp);isblue[a[tmp]]=true;cnt++;
            }
            else
            {
                maxdepth=-1;
                for (register int i=1;i<=n;i++)
                    if (!taboo[i] && !isblue[a[i]] && !isblack[a[i]] && depth[i]>maxdepth) maxdepth=depth[i],maxind=i;
                anslist.pb(maxind);Rotate(maxind);isblack[a[maxind]]=true;
            }
        }
        for (register int i=1;i<=n;i++) taboo[i]|=isleaf[i];
    }
    assert(int(anslist.size())<=25000);
    printf("%d\n",int(anslist.size()));
    for (auto item : anslist) printf("%d\n",item-1);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}