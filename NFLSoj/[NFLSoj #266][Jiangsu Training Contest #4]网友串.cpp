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

typedef bitset<256> bs;

int n,a[58];
int A[58],B[58],atot,btot;
unordered_map<bs,int> dp[58][58];

bs can[256];
inline bool check(int len1,int x,int len2,int y)
{
    if ((len1+len2)&1) return false;
    int bit[48];
    for (register int i=1,pt=len1;i<=len1;i++) bit[pt--]=(x&1),x>>=1;
    for (register int i=1,pt=len1+len2;i<=len2;i++) bit[pt--]=(y&1),y>>=1;
    for (register int i=1,j=((len1+len2)>>1)+1;j<=len1+len2;i++,j++) if (bit[i]!=bit[j]) return true;
    return false;
}
inline void init_can()
{
    for (register int i=2;i<=255;i++)
        for (register int j=2;j<=255;j++)
        {
            int len1=1,len2=1;
            while ((1<<(len1+1))<=i) len1++;
            while ((1<<(len2+1))<=j) len2++;
            int x=i-(1<<len1),y=j-(1<<len2);
            if (check(len1,x,len2,y)) can[i][j]=1;
        }
}

int ansa[148],ansb[148],ans[148];

inline void gen(int A[],int res[],int N)
{
    for (register int i=0;i<=N;i++)
        for (register int j=0;j<=N;j++)
            dp[i][j].clear();
    dp[0][0][0]=1;
    for (register int i=0;i<=N-1;i++)
        for (register int j=0;j<=i;j++)
            for (unordered_map<bs,int>::iterator iter=dp[i][j].begin();iter!=dp[i][j].end();iter++)
                for (register int nxt=0;nxt<=(1<<A[i+1])-1;nxt++)
                    Add(dp[i+1][j+iter->x[(1<<A[i+1])+nxt]][iter->x|can[(1<<A[i+1])+nxt]],iter->y);
    for (register int j=0;j<=N;j++)
        for (unordered_map<bs,int>::iterator iter=dp[N][j].begin();iter!=dp[N][j].end();iter++)
                Add(res[j],iter->y);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);for (register int i=1;i<=n;i++) io.Get(a[i]);
    for (register int i=1;i<=n;i++) if (a[i]&1) A[++atot]=a[i]; else B[++btot]=a[i];
    init_can();gen(A,ansa,atot);gen(B,ansb,btot);
    for (register int i=0;i<=atot;i++)
        for (register int j=0;j<=btot;j++)
            Add(ans[i+j],1ll*ansa[i]*ansb[j]%MOD);
    for (register int i=0;i<=n;i++) printf("%d ",ans[i]);
    printf("\n");
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}