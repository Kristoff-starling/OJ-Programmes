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

int n;
int a[48];LL sum[2000048];
int table[2000048];

int dp1[2000048],dp2[2000048];
int q[2000048],head,tail;bool inq[2000048];

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);for (register int i=1;i<=n;i++) io.Get(a[i]);
    for (register int i=1;i<=n;i++) table[1<<(i-1)]=i;
    for (register int Mask=1;Mask<=(1<<n)-1;Mask++) sum[Mask]=sum[Mask^LOWBIT(Mask)]+a[table[LOWBIT(Mask)]];
    dp2[0]=1;head=tail=1;q[1]=0;inq[0]=true;int full=(1<<n)-1;
    while (head<=tail)
    {
        int Mask=q[head++];inq[Mask]=false;
        for (register int valid=full^Mask;valid;valid^=LOWBIT(valid))
        {
            int nxt=table[LOWBIT(valid)];
            if (sum[Mask]+a[nxt]<=0)
            {
                int toMask=Mask|(1<<(nxt-1));
                Add(dp2[toMask],dp2[Mask]);
                if (!inq[toMask]) inq[toMask]=true,q[++tail]=toMask;
            }
        }
    }
    dp1[0]=1;head=tail=1;q[1]=0;inq[0]=true;
    while (head<=tail)
    {
        int Mask=q[head++];inq[Mask]=false;
        for (register int valid=full^Mask;valid;valid^=LOWBIT(valid))
        {
            int nxt=table[LOWBIT(valid)];
            if (sum[Mask]+a[nxt]>0)
            {
                int toMask=Mask|(1<<(nxt-1));
                Add(dp1[toMask],dp1[Mask]);
                if (!inq[toMask]) inq[toMask]=true,q[++tail]=toMask;
            }
        }
    }
    int ans=0;
    for (register int Mask=1;Mask<=(1<<n)-1;Mask++)
        Add(ans,sum[Mask]%MOD*dp1[Mask]%MOD*dp2[full^Mask]%MOD);
    for (register int i=1;i<=n;i++)
        if (a[i]<=0)
            for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
                if (!(Mask&(1<<(i-1))) && sum[Mask]+a[i]<=0)
                {
                    int another=full^Mask^(1<<(i-1));
                    Add(ans,1ll*add(sub(a[i])+sub(sum[Mask]%MOD))*dp1[Mask]%MOD*dp2[another]%MOD);
                }
    printf("%d\n",ans);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}