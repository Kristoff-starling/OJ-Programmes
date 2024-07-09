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

const int MAXN=500;

int n,m;
int g[MAXN+48][MAXN+48];
int delta[MAXN+48];

int ansrow[MAXN+48],anscol[MAXN+48],Ans;

int cntrow[MAXN+48],cntcol[MAXN+48];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=m;j++)
            io.Get(g[i][j]);
    for (register int i=2;i<=n;i++) delta[i]=g[i][1]-g[i-1][1];
    bool f=true;
    for (register int j=2;j<=m;j++)
        for (register int i=2;i<=n;i++)
            if (g[i][j]-g[i-1][j]!=delta[i]) f=false;
    if (!f) {printf("-1\n");return 0;}
    int minrow=1,minn=g[1][1];
    for (register int i=2;i<=n;i++) if (g[i][1]<minn) minn=g[i][1],minrow=i;
    int mincol=1;
    for (register int j=2;j<=m;j++) if (g[minrow][j]<minn) minn=g[minrow][j],mincol=j;
    Ans=INF;
    for (register int base=0;base<=minn;base++)
    {
        memset(cntrow,0,sizeof(cntrow));
        memset(cntcol,0,sizeof(cntcol));
        for (register int i=1;i<=n;i++) cntrow[i]=base+g[i][mincol]-minn;
        for (register int j=1;j<=m;j++) cntcol[j]=g[1][j]-cntrow[1];
        int cnt=0;
        for (register int i=1;i<=n;i++) cnt+=cntrow[i];
        for (register int j=1;j<=m;j++) cnt+=cntcol[j];
        if (cnt<Ans)
        {
            Ans=cnt;
            memcpy(ansrow+1,cntrow+1,n*sizeof(int));
            memcpy(anscol+1,cntcol+1,m*sizeof(int));
        }
    }
    printf("%d\n",Ans);
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=ansrow[i];j++)
            printf("row %d\n",i);
    for (register int i=1;i<=m;i++)
        for (register int j=1;j<=anscol[i];j++)
            printf("col %d\n",i);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}