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

const int MAXN=2e5;

int n,X,Y;
vector<Pair> v[MAXN+48];
int col[MAXN+48];

int id[MAXN+48],tot;

inline bool cmp(int x,int y)
{
    return v[x][0].x<v[y][0].x;
}

int fac[MAXN+48],ifac[MAXN+48];
inline void init_inv()
{
    fac[0]=1;for (register int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[n]=quick_pow(fac[n],MOD-2);
    for (register int i=n-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

inline int C(int x,int y)
{
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

vector<int> vv[MAXN+48];
inline void addedge(int x,int y) {cerr<<x<<' '<<y<<endl;vv[x].pb(y);vv[y].pb(x);}

map<int,int> Mp;bool visited[MAXN+48];int cc=0;
inline void dfs(int cur)
{
    visited[cur]=true;cc++;Mp[col[cur]]++;
    for (register int i=0;i<int(vv[cur].size());i++)
    {
        int y=vv[cur][i];
        if (!visited[y]) dfs(y);
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
    io.Get(n);io.Get(X);io.Get(Y);int c,w;
    init_inv();
    for (register int i=1;i<=n;i++)
    {
        io.Get(c);io.Get(w);
        v[c].pb(mp(w,i));col[i]=c;
    }
    for (register int i=1;i<=n;i++) sort(v[i].begin(),v[i].end());
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<int(v[i].size()) && v[i][0].x+v[i][j].x<=X;j++) addedge(v[i][0].y,v[i][j].y);
    for (register int i=1;i<=n;i++) if (int(v[i].size())) id[++tot]=i;
    if (tot==1) {printf("1\n");return 0;}
    sort(id+1,id+tot+1,cmp);
    for (register int i=1;i<=n;i++)
        for (register int j=0;j<int(v[i].size());j++)
        {
            if (id[1]!=i && v[id[1]][0].x+v[i][j].x<=Y) addedge(v[id[1]][0].y,v[i][j].y);
            if (id[2]!=i && v[id[2]][0].x+v[i][j].x<=Y) addedge(v[id[2]][0].y,v[i][j].y);
        }
    int ans=1;memset(visited,false,sizeof(visited));
    for (register int i=1;i<=n;i++)
        if (!visited[i])
        {
            cc=0;Mp.clear();dfs(i);
            for (map<int,int>::iterator iter=Mp.begin();iter!=Mp.end();iter++)
                ans=1ll*ans*C(cc,iter->y)%MOD,cc-=iter->y;
        }
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}