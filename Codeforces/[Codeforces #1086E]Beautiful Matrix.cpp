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

const int MAXN=2000;

int n,a[MAXN+48][MAXN+48];

int fac[MAXN+48];
int d[MAXN+48][MAXN+48],pw[MAXN+48];

inline void init()
{
    d[0][0]=1;d[1][0]=1;
    for (register int i=2;i<=n;i++)
        for (register int j=0;j<=i;j++)
            if (i!=j) d[i][j]=add(1ll*(i-j)*d[i-1][j]%MOD+1ll*j*d[i-1][j-1]%MOD);
            else d[i][j]=1ll*(i-1)*d[i-1][j-2]%MOD;
    fac[0]=1;for (register int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    pw[0]=1;for (register int i=1;i<=n;i++) pw[i]=1ll*pw[i-1]*d[n][n]%MOD;
}

int cnt[MAXN+48];

struct BIT
{
    int c[MAXN+48];
    inline void init() {memset(c,0,sizeof(c));}
    inline void modify(int x,int delta) {while (x<=n) c[x]+=delta,x+=LOWBIT(x);}
    inline int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
    inline int calc(int l,int r) {return query(r)-query(l-1);}
}s1,s2;

struct SuperBIT
{
    int c[MAXN+48],cc[MAXN+48];
    inline void init() {memset(c,0,sizeof(c));memset(cc,0,sizeof(cc));}
    inline void modify(int x,int delta)
    {
        cc[x]+=delta;
        if ((delta==1 && cc[x]==1) || (delta==-1 && cc[x]==0))
            while (x<=n) c[x]+=delta,x+=LOWBIT(x);
    }
    inline int query(int x) {int res=0;while (x) res+=c[x],x^=LOWBIT(x);return res;}
    inline int calc(int l,int r) {return query(r)-query(l-1);}
}s3;

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d",&n);
    for (register int i=1;i<=n;i++)
        for (register int j=1;j<=n;j++)
            scanf("%d",&a[i][j]);
    init();s1.init();int ans=0;
    for (register int i=1;i<=n;i++)
    {
        int avai=a[1][i]-1-s1.query(a[1][i]-1);
        Add(ans,1ll*avai*fac[n-i]%MOD*pw[n-1]%MOD);
        s1.modify(a[1][i],1);
    }
    for (register int i=2;i<=n;i++)
    {
        s1.init();s2.init();s3.init();memset(cnt,0,sizeof(cnt));int Cnt=0;
        for (register int j=2;j<=n;j++) s2.modify(a[i-1][j],1),s3.modify(a[i-1][j],1),cnt[a[i-1][j]]++;
        for (register int j=1;j<=n;j++)
        {
            int avai=a[i][j]-1-s1.query(a[i][j]-1)-(a[i-1][j]<a[i][j] && !s1.calc(a[i-1][j],a[i-1][j]));
            int m=(n-j)-Cnt;
            int type1=a[i][j]-1-s3.query(a[i][j]-1)-(a[i-1][j]<a[i][j] && !s3.calc(a[i-1][j],a[i-1][j]));
            int type2=avai-type1;
            Add(ans,1ll*type1*d[n-j][m]%MOD*pw[n-i]%MOD);
            if (m) Add(ans,1ll*type2*d[n-j][m-1]%MOD*pw[n-i]%MOD);
            if (j!=n)
            {
                cnt[a[i][j]]++;if (cnt[a[i][j]]==2) Cnt++;
                cnt[a[i-1][j+1]]--;if (cnt[a[i-1][j+1]]==1) Cnt--;
                s1.modify(a[i][j],1);s3.modify(a[i][j],1);
                s2.modify(a[i-1][j+1],-1);s3.modify(a[i-1][j+1],-1);
            }
        }
    }
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}