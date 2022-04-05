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
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int MAXN=3000;

int n,m,k;
int p[MAXN+48],q[MAXN+48];

int dp1[MAXN+48][MAXN+48],dp2[MAXN+48][MAXN+48];

inline bool cmp(int x,int y) {return x>y;}

int c[MAXN+48][MAXN+48];
inline void init_c()
{
    c[0][0]=1;
    for (register int i=1;i<=MAXN;i++)
    {
        c[i][0]=c[i][i]=1;
        for (register int j=1;j<=i-1;j++) c[i][j]=add(c[i-1][j-1]+c[i-1][j]);
    }
}
inline int C(int x,int y)
{
    if (y<0 || x<y) return 0;
    return c[x][y];
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca;io.Get(ca);init_c();
    while (ca--)
    {
        io.Get(n);io.Get(m);io.Get(k);
        for (register int i=1;i<=n;i++) io.Get(q[i]);
        for (register int i=1;i<=n;i++) io.Get(p[i]);
        sort(p+1,p+n+1,cmp);sort(q+1,q+n+1,cmp);
        memset(dp1,0,sizeof(dp1));dp1[0][0]=1;
        for (register int i=1;i<=n;i++)
        {
            int sum=dp1[i-1][i-1];
            for (register int j=i;j<=n;j++)
            {
                dp1[i][j]=1ll*sum*q[j]%MOD;
                Add(sum,dp1[i-1][j]);
            }
        }
        memset(dp2,0,sizeof(dp2));
        for (register int i=1;i<=n;i++)
        {
            int sum=dp2[i-1][i-1],num=1;
            for (register int j=i;j<=n;j++)
            {
                dp2[i][j]=add(sum+1ll*num*p[j]%MOD);
                Add(sum,dp2[i-1][j]);Add(num,C(j-1,i-2));
            }
        }
        int ans=0;
        //more than one attack card
        for (register int i=0;i<=min(k-2,n);i++)
        {
            int sum=0;for (register int j=i;j<=n;j++) Add(sum,dp1[i][j]);
            for (register int j=k-i;j<=n;j++)
                Add(ans,1ll*sum*dp2[k-i][j]%MOD*C(n-j,m-k)%MOD);
        }
        //only one attack card and k-1 upgrade cards
        for (register int i=k-1;i<=n;i++)
        {
            for (register int j=1;j<=n;j++)
                Add(ans,1ll*dp1[k-1][i]*p[j]%MOD*C(n-i+n-j,m-k)%MOD);
        }
        printf("%d\n",ans);
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}