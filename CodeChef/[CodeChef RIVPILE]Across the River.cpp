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

const int MAXN=250;

int n,m,w;
int X[MAXN+48],Y[MAXN+48];
vector<Pair> v[200048];

struct disk
{
    int r,c;
    inline void input() {io.Get(r);io.Get(c);}
    inline bool operator < (const disk &other) const {return r<other.r;}
}d[MAXN+48];

inline int getind(int x,int y,int z)
{
    return z*(n*m)+(x-1)*m+y;
}

inline bool reachable(int id1,int id2,int d1,int d2)
{
    return 1ll*(X[id1]-X[id2])*(X[id1]-X[id2])+1ll*(Y[id1]-Y[id2])*(Y[id1]-Y[id2])<=1ll*(d[d1].r+d[d2].r)*(d[d1].r+d[d2].r);
}

int S,T;

int dist[200048];
priority_queue<Pair> q;
inline void dijkstra()
{
    for (register int i=1;i<=n*m*2+2;i++) dist[i]=INF;
    dist[S]=0;q.push(mp(0,S));
    while (!q.empty())
    {
        int x=q.top().y,dd=-q.top().x;q.pop();
        if (dd>dist[x]) continue;
        for (register int i=0;i<int(v[x].size());i++)
        {
            int y=v[x][i].x;
            if (dist[y]>dist[x]+v[x][i].y)
            {
                dist[y]=dist[x]+v[x][i].y;
                q.push(mp(-dist[y],y));
            }
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
    int ca;io.Get(ca);
    while (ca--)
    {
        io.Get(n);io.Get(m);io.Get(w);
        for (register int i=1;i<=n;i++) io.Get(X[i]),io.Get(Y[i]);
        for (register int i=1;i<=m;i++) d[i].input();
        sort(d+1,d+m+1);
        for (register int i=1;i<=n*m*2+2;i++) v[i].clear();
        for (register int i=1;i<=n;i++)
            for (register int j=1;j<=m;j++)
            {
                v[getind(i,j,0)].pb(mp(getind(i,j,1),d[j].c));
                if (j<m) v[getind(i,j,0)].pb(mp(getind(i,j+1,0),0));
            }
        for (register int i=1;i<=n;i++)
            for (register int j=1;j<=n;j++)
                if (i!=j)
                {
                    int pt=m+1;
                    for (register int k=1;k<=m;k++)
                    {
                        while (pt>1 && reachable(i,j,k,pt-1)) pt--;
                        if (pt<=m) v[getind(i,k,1)].pb(mp(getind(j,pt,0),0));
                    }
                }
        S=n*m*2+1;T=n*m*2+2;
        for (register int i=1;i<=n;i++)
        {
            int pt=m+1;
            while (pt>1 && d[pt-1].r>=Y[i]) pt--;
            if (pt<=m) v[S].pb(mp(getind(i,pt,0),0));
        }
        for (register int i=1;i<=n;i++)
            for (register int j=1;j<=m;j++)
                if (d[j].r>=w-Y[i]) v[getind(i,j,1)].pb(mp(T,0));
        dijkstra();
        if (dist[T]>=INF) printf("impossible\n"); else printf("%d\n",dist[T]);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}