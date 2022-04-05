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

const int MAXN=1e5;

int n,k;
int ans[MAXN+48];

struct node
{
    int val,ind;
    inline void input() {io.Get(val);}
    inline bool operator < (const node &other) const {return val<other.val;}
}a[MAXN+48];

int fac[MAXN+48],ifac[MAXN+48];
inline void init_inv()
{
    fac[0]=1;for (register int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD;
    ifac[n]=quick_pow(fac[n],MOD-2);
    for (register int i=n-1;i>=0;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%MOD;
}

inline int C(int x,int y)
{
    if (x<y || y<0) return 0;
    return 1ll*fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}

inline int count1(int val)
{
    if (a[1].val>val) return 0;
    int l=1,r=n,mid,ans;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (a[mid].val<=val) ans=mid,l=mid+1; else r=mid-1;
    }
    return ans;
}

inline int count2(int val)
{
    if (a[n].val<val) return n+1;
    int l=1,r=n,mid,ans;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (a[mid].val>=val) ans=mid,r=mid-1; else l=mid+1;
    }
    return ans;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(k);
    for (register int i=1;i<=n;i++) a[i].input(),a[i].ind=i;
    sort(a+1,a+n+1);init_inv();
    for (register int i=1;i<=n;i++)
    {
        if (a[i].val==0) {ans[a[i].ind]=C(n,k);continue;}
        //he himself is not chosen
        {
            int valid=(n-count2(a[i].val)+1)+count1((a[i].val&1)?(a[i].val>>1):((a[i].val>>1)-1))-1;
            Add(ans[a[i].ind],C(valid,k));
        }
        //he himself is chosen
        {
            int left=count2(a[i].val),right=count1((a[i].val<<1)-1);
            int must=right-left+1;
            Add(ans[a[i].ind],C(n-must,k-must));
        }
    }
    for (register int i=1;i<=n;i++) printf("%d\n",ans[i]);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}