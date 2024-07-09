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
const double eps=1e-12;
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

inline bool islarger(double x,double y) {return x-y>eps;}
inline bool issmaller(double x,double y) {return x-y<-eps;}
inline bool isequal(double x,double y) {return (!islarger(x,y)) && (!issmaller(x,y));}

int n,k;
int t[MAXN+48];

double dp[51][MAXN+48];
double p[MAXN+48],q[MAXN+48],r[MAXN+48];

inline void init()
{
    for (register int i=1;i<=n;i++) p[i]=p[i-1]+t[i];
    for (register int i=1;i<=n;i++) q[i]=q[i-1]+double(1.0)/t[i];
    for (register int i=1;i<=n;i++) r[i]=r[i-1]+double(1.0)*double(t[i])*q[i-1];
}

inline double calc_k(double x1,double y1,double x2,double y2)
{
    if (isequal(x1,x2)) return 1e16;
    return (y1-y2)/(x1-x2);
}

inline double calc(int left,int right)
{
    return p[right]*q[right]-p[left-1]*q[right]-r[right]+r[left-1];
}

struct node
{
    double x,y;int ind;
    node () {}
    inline node(double _x,double _y,int _i) {x=_x;y=_y;ind=_i;}
}Q[MAXN+48];int head,tail;

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&k);
    for (register int i=1;i<=n;i++) scanf("%d",t+i);
    init();
    for (register int i=1;i<=n;i++) dp[1][i]=calc(1,i);
    for (register int layer=2;layer<=k;layer++)
    {
        head=tail=1;Q[1]=node(p[layer-1],dp[layer-1][layer-1]+r[layer-1],layer-1);
        for (register int i=layer;i<=n;i++)
        {
            while (head<tail && issmaller(calc_k(Q[head].x,Q[head].y,Q[head+1].x,Q[head+1].y),q[i])) head++;
            int chosen=Q[head].ind;
            dp[layer][i]=dp[layer-1][chosen]+calc(chosen+1,i);
            Q[++tail]=node(p[i],dp[layer-1][i]+r[i],i);
            while (head+1<tail && issmaller(calc_k(Q[tail-1].x,Q[tail-1].y,Q[tail].x,Q[tail].y),calc_k(Q[tail-2].x,Q[tail-2].y,Q[tail-1].x,Q[tail-1].y))) Q[tail-1]=Q[tail],tail--;
        }
    }
    printf("%.10lf\n",dp[k][n]);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}