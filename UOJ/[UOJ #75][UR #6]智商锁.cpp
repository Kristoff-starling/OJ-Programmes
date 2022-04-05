#include <bits/stdc++.h>
#include <unordered_map>
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
template<typename T> inline int quick_pow(int x,T y) {if (!x) return 0;int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int N=12;

int a[48][48];

struct Graph
{
    vector<Pair> edge;
    int n,det;
    inline void clear() {edge.clear();n=det=0;}
    inline void print()
    {
        printf("%d %d\n",n,int(edge.size()));
        for (auto item : edge) printf("%d %d\n",item.x,item.y);
    }
    inline Graph operator * (Graph other)
    {
        Graph res;res.clear();
        res.n=n+other.n-1;res.det=1ll*det*other.det%MOD;
        for (auto item : edge) res.edge.pb(item);
        for (register int i=0;i<int(other.edge.size());i++)
        {
            Pair ins=other.edge[i];ins.x+=n-1;ins.y+=n-1;
            res.edge.pb(ins);
        }
        return res;
    }
};

inline int Gauss()
{
    int fl=1,ans=1;
    for (register int i=1;i<=N-1;i++)
    {
        int pt=i;
        while (pt<=N-1 && !a[pt][i]) pt++;
        if (pt>N-1) return 0;
        if (pt!=i)
        {
            for (register int j=i;j<=N-1;j++) swap(a[i][j],a[pt][j]);
            fl=-fl;
        }
        ans=1ll*ans*a[i][i]%MOD;int inv=quick_pow(a[i][i],MOD-2);
        for (register int j=i+1;j<=N-1;j++)
            if (a[j][i])
            {
                int tmp=a[j][i];
                for (register int k=i;k<=N-1;k++)
                    a[j][k]=sub(a[j][k]-1ll*a[i][k]*inv%MOD*tmp%MOD);
            }
    }
    if (fl==-1) ans=sub(-ans);
    return ans;
}

inline Graph gen_graph()
{
    Graph res;
    memset(a,0,sizeof(a));
    for (register int i=1;i<=N-1;i++)
        for (register int j=i+1;j<=N;j++)
            if (rand()&1) Add(a[i][i],1),Add(a[j][j],1),Sub(a[i][j],1),Sub(a[j][i],1),res.edge.pb(mp(i,j));
    res.n=N;res.det=Gauss();return res;
}

vector<Graph> s[5];
vector<Pair> S[3];vector<int> inv;
unordered_map<int,int> Mp;

inline void gen_set()
{
    for (register int i=1;i<=4;i++)
    {
        s[i].clear();
        for (register int j=1;j<=600;j++)
        {
            Graph ins=gen_graph();
            if (ins.det) s[i].pb(ins);
        }
    }
    S[1].clear();S[2].clear();inv.clear();
    for (register int i=0;i<int(s[1].size());i++)
        for (register int j=0;j<int(s[2].size());j++)
        {
            int ndet=1ll*s[1][i].det*s[2][j].det%MOD;
            S[1].pb(mp(i,j));inv.pb(quick_pow(ndet,MOD-2));
        }
    for (register int i=0;i<int(s[3].size());i++)
        for (register int j=0;j<int(s[4].size());j++)
        {
            int ndet=1ll*s[3][i].det*s[4][j].det%MOD;
            S[2].pb(mp(i,j));
            Mp[ndet]=int(S[2].size())-1;
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
    srand(time(NULL));
    gen_set();int ca,k;
    scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&k);bool f=false;
        if (k==0) {puts("2 0");continue;}
        for (register int i=0;i<int(S[1].size());i++)
        {
            int need=1ll*k*inv[i]%MOD;
            if (Mp.find(need)!=Mp.end())
            {
                int ind=Mp[need];
                int id1=S[1][i].x,id2=S[1][i].y,id3=S[2][ind].x,id4=S[2][ind].y;
                Graph g=s[1][id1];g=g*s[2][id2];g=g*s[3][id3];g=g*s[4][id4];
                g.print();f=true;break;
            }
        }
        if (!f) puts("QwQ");
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}