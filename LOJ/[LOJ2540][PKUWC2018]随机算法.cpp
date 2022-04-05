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

int n,m,full;
int edge[48],taboo[2000048];
int table[2000048],popcount[2000048];
int dp[1100048][21];bool inq[1100048][21];

int head,tail,q[40000048];

inline int getstd()
{
    int res=0;
    for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
        if (!(taboo[Mask]&Mask)) check_max(res,popcount[Mask]);
    return res;
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);int x,y;
    for (register int i=1;i<=m;i++)
    {
        io.Get(x);io.Get(y);
        edge[x]|=(1<<(y-1));edge[y]|=(1<<(x-1));
    }
    full=(1<<n)-1;
    for (register int i=1;i<=n;i++) table[1<<(i-1)]=i;
    for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
    {
        taboo[Mask]=0;if (Mask) popcount[Mask]=popcount[Mask^LOWBIT(Mask)]+1;
        for (register int cur=Mask;cur;cur^=LOWBIT(cur))
            taboo[Mask]|=edge[table[LOWBIT(cur)]];
    }
    int ans=getstd(),cnt=0;
    dp[0][0]=1;head=1;tail=2;q[1]=0;q[2]=0;inq[0][0]=true;
    while (head<=tail)
    {
        int Mask=q[head++],x=q[head++];inq[Mask][x]=false;
        if (!x && (Mask|taboo[Mask])==full && popcount[Mask]==ans) Add(cnt,dp[Mask][x]);
        //put a useless node
        if (x)
        {
            Add(dp[Mask][x-1],1ll*dp[Mask][x]*x%MOD);
            if (!inq[Mask][x-1]) inq[Mask][x-1]=true,q[++tail]=Mask,q[++tail]=x-1;
        }
        //put a useful node
        for (register int toMask=(full^(Mask|taboo[Mask]));toMask;toMask^=LOWBIT(toMask))
        {
            int to=table[LOWBIT(toMask)];
            int tt=(Mask|(1<<(to-1))),ct=popcount[taboo[tt]]-(popcount[taboo[Mask]]-x);
            Add(dp[tt][ct],dp[Mask][x]);if (!inq[tt][ct]) inq[tt][ct]=true,q[++tail]=tt,q[++tail]=ct;
        }
    }
    for (register int i=2;i<=n;i++) cnt=1ll*cnt*quick_pow(i,MOD-2)%MOD;
    printf("%d\n",cnt);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}