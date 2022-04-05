//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
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

#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

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

int fac[15000048],ifac[15000048];

inline void init_fac()
{
    int mx=5001*5000/2;
    fac[0]=1;rep(i,1,mx) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[mx]=quick_pow(fac[mx],MOD-2);
    REP(i,mx-1,1) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

int c[5048][5048];

inline void init_c()
{
    c[0][0]=1;
    rep(i,1,5000)
    {
        c[i][0]=c[i][i]=1;
        rep(j,1,i-1) c[i][j]=add(c[i-1][j-1]+c[i-1][j]);
    }
}

int n,b[5048];

int a[5048],tot;
int mulfac[5048],imulfac[5048],sum[5048];

int dp[5048][2];

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    init_fac();init_c();int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n-1) scanf("%d",b+i);
        tot=0;int cnt=1;
        rep(i,1,n-1) if (b[i]==0) cnt++; else a[++tot]=cnt,cnt=1;
        a[++tot]=cnt;
        sum[0]=0;rep(i,1,tot) sum[i]=sum[i-1]+a[i];
        mulfac[0]=1;rep(i,1,tot) mulfac[i]=1ll*mulfac[i-1]*fac[a[i]]%MOD;
        imulfac[0]=1;rep(i,1,tot) imulfac[i]=1ll*imulfac[i-1]*ifac[a[i]]%MOD;
        memset(dp,0,sizeof(dp));dp[0][0]=1;
        rep(i,1,tot) rep(j,0,1) rep(pre,0,i-1)
        {
            int connected=(i-pre-1)&1;
            Add(dp[i][j],1ll*dp[pre][j^connected]*ifac[sum[i]-sum[pre]]%MOD*mulfac[i]%MOD*imulfac[pre]%MOD);
        }
        int ss=n,ans=1;
        rep(i,1,tot) ans=1ll*ans*c[ss][a[i]]%MOD,ss-=a[i];
        printf("%d\n",1ll*ans*sub(dp[tot][0]-dp[tot][1])%MOD);
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}