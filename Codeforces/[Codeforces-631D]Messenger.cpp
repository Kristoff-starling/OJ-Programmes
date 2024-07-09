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

int N,M,n,m;
pLL a[MAXN+48],b[MAXN+48];

inline void input(pLL A[],int N,int &re)
{
    re=0;int x;char ch;
    for (register int i=1;i<=N;i++)
    {
        scanf("%d-%c",&x,&ch);
        if (re && A[re].y==ch) {A[re].x+=x;continue;}
        A[++re]=mp(x,ch);
    }
}

pLL A[MAXN+48];int len;
int kmp[MAXN+48];
inline void construct_kmp()
{
    kmp[0]=-1;kmp[1]=0;int k=0;
    for (register int i=2;i<=len;i++)
    {
        while (k!=-1 && A[i]!=A[k+1]) k=kmp[k];
        kmp[i]=++k;
    }
}

inline bool check(int id,Pair cur) {return 1<=id && id<=n && cur.y==a[id].y && cur.x<=a[id].x;}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&N,&M);
    input(a,N,n);input(b,M,m);
    if (m==1)
    {
        LL ans=0;
        for (register int i=1;i<=n;i++)
            if (a[i].y==b[1].y && a[i].x>=b[1].x) ans+=a[i].x-b[1].x+1;
        printf("%lld\n",ans);
        return 0;
    }
    if (m==2)
    {
        int ans=0;
        for (register int i=1;i<=n-1;i++)
            if (a[i].y==b[1].y && a[i].x>=b[1].x && a[i+1].y==b[2].y && a[i+1].x>=b[2].x) ans++;
        printf("%d\n",ans);
        return 0;
    }
    len=0;for (register int i=2;i<=m-1;i++) A[++len]=b[i];
    construct_kmp();int pos=0;int ans=0;
    for (register int i=1;i<=n;i++)
    {
        while (pos!=-1 && a[i]!=A[pos+1]) pos=kmp[pos];
        ++pos;
        if (pos==len && check(i+1,b[m]) && check(i-len,b[1])) ans++;
    }
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}