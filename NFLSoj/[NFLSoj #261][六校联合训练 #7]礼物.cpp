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

const int MAXN=1e5;

int n;
Pair a[MAXN+48];
Pair small[MAXN+48],big[MAXN+48];int stot,btot;

const int lim=2e7;
int fac[lim+48],finv[lim+48];
inline void init_inv()
{
    fac[0]=fac[1]=1;
    for (register int i=2;i<=lim;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    finv[lim]=quick_pow(fac[lim],MOD-2);
    for (register int i=lim-1;i>=0;i--) finv[i]=1ll*finv[i+1]*(i+1)%MOD;
}

inline int C(int x,int y)
{
    if (x<y || y<0) return 0;
    return 1ll*fac[x]*finv[y]%MOD*finv[x-y]%MOD;
}

int dp[5600][5600];

inline int calc_small()
{
    int base=2748;
    for (register int i=1;i<=stot;i++) Add(dp[base-small[i].x][base-small[i].y],1);
    for (register int i=base-2748;i<=base+2748;i++)
        for (register int j=base-2748;j<=base+2748;j++)
            Add(dp[i+1][j],dp[i][j]),Add(dp[i][j+1],dp[i][j]);
    int ans=0;
    for (register int i=1;i<=stot;i++) Add(ans,dp[base+small[i].x][base+small[i].y]);
    for (register int i=1;i<=stot;i++) Sub(ans,C(small[i].x*2+small[i].y*2,small[i].x*2));
    return ans;
}

inline int calc_big()
{
    int ans=0;
    for (register int i=1;i<=btot-1;i++)
        for (register int j=i+1;j<=btot;j++)
            Add(ans,C(big[i].x+big[i].y+big[j].x+big[j].y,big[i].x+big[j].x));
    return add(ans+ans);
}

inline int calc_smallbig()
{
    int ans=0,base=2748;
    for (register int i=1;i<=btot;i++)
    {
        for (register int j=base-2748;j<=base;j++)
            Add(ans,1ll*dp[base][j]*C(big[i].x-1+big[i].y-(j-base),big[i].x-1)%MOD);
        for (register int j=base;j>=base-2748;j--)
            Add(ans,1ll*dp[j][base]*C(big[i].x-(j-base)+big[i].y-1,big[i].x-(j-base))%MOD);
    }
    return add(ans+ans);
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
    for (register int i=1;i<=n;i++)
    {
        io.Get(a[i].x),io.Get(a[i].y);
        if (a[i].x<=2700 && a[i].y<=2700) small[++stot]=a[i]; else big[++btot]=a[i];
    }
    init_inv();
    io.Print(add(add(calc_small()+calc_big())+calc_smallbig()),'\n');
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}