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

int n,m;
vector<int> v[MAXN+48];
int ans[MAXN+48];

struct Edge
{
    int u,v,l,r;
    inline void input() {io.Get(u);io.Get(v);io.Get(l);io.Get(r);}
}edge[MAXN+48];
int type[MAXN+48];

int s[MAXN+48];
priority_queue<Pair> q;

inline void init_dijkstra()
{
    memset(s,0,sizeof(s));
    for (register int i=1;i<=n;i++) if (type[i]==-1) s[i]=INF,q.push(mp(s[i],i));
    while (!q.empty())
    {
        int x=q.top().y,dd=q.top().x;q.pop();
        if (dd<s[x]) continue;
        for (register int i=0;i<int(v[x].size());i++)
        {
            int y=((edge[v[x][i]].u==x)?edge[v[x][i]].v:edge[v[x][i]].u);
            if (edge[v[x][i]].r>=s[x]) continue;
            if (edge[v[x][i]].l+1>s[y])
            {
                s[y]=edge[v[x][i]].l+1;
                q.push(mp(s[y],y));
            }
        }
    }
}

int dist[MAXN+48];bool visited[MAXN+48];
inline void dijkstra()
{
    for (register int i=1;i<=n;i++) dist[i]=INF;
    dist[1]=0;q.push(mp(0,1));
    while (!q.empty())
    {
        int x=q.top().y,dd=-q.top().x;q.pop();
        if (dd>dist[x]) continue;
        visited[x]=true;
        for (register int i=0;i<int(v[x].size());i++)
        {
            int y=((edge[v[x][i]].u==x)?edge[v[x][i]].v:edge[v[x][i]].u);
            if (visited[y]) continue;
            if (edge[v[x][i]].r<s[y] || edge[v[x][i]].r<dist[x]) {ans[v[x][i]]=edge[v[x][i]].l;continue;}
            int val=max(s[y],max(edge[v[x][i]].l,dist[x]));
            ans[v[x][i]]=val;
            if (val<dist[y])
            {
                dist[y]=val;
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
    io.Get(n);io.Get(m);
    for (register int i=1;i<=m;i++) edge[i].input(),v[edge[i].u].pb(i),v[edge[i].v].pb(i);
    for (register int i=1;i<=n;i++) io.Get(type[i]);
    init_dijkstra();
    if (s[1]) {printf("Impossible\n");return 0;}
    // for (register int i=1;i<=n;i++) cerr<<s[i]<<' ';
    // cerr<<endl;
    dijkstra();
    // for (register int i=1;i<=n;i++) cerr<<dist[i]<<' ';
    // cerr<<endl;
    for (register int i=1;i<=n;i++) if (dist[i]==INF && type[i]==1) {printf("Impossible\n");return 0;}
    for (register int i=1;i<=m;i++)
    {
        if (!ans[i]) ans[i]=edge[i].l;
        printf("%d\n",ans[i]);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}