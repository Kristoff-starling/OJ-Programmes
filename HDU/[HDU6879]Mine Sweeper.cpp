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

inline void solve1()
{
    puts("1 2");
    puts("X.");
}

inline void solve2()
{
    puts("1 3");
    puts("X.X");
}

inline void solve4()
{
    puts("2 2");
    puts("X.");
    puts("X.");
}

inline void solve5()
{
    puts("2 3");
    puts("XX.");
    puts("X..");
}

inline void solve7()
{
    puts("1 11");
    puts("X..X..X..X.");
}

inline void solve10()
{
    puts("1 11");
    puts("X.X.X.X.X.X");
}

inline void solve13()
{
    puts("2 5");
    puts("XX.X.");
    puts("X..X.");
}

char s[48][48];

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        int n;scanf("%d",&n);
        if (n==1) {solve1();continue;}
        if (n==2) {solve2();continue;}
        if (n==7) {solve7();continue;}
        if (n==4) {solve4();continue;}
        if (n==5) {solve5();continue;}
        if (n==10) {solve10();continue;}
        if (n==13) {solve13();continue;}
        puts("25 25");
        rep(i,1,25) rep(j,1,25) s[i][j]='.';
        int T=n/8,res=n%8;
        if (res==1 || res==4 || res==7) T--;
        if (res==2 || res==5) T-=2;
        int x=2,y=2;
        while (T--)
        {
            s[x][y]='X';
            if (y==24) x+=2,y=2; else y+=2;
        }
        if (res==1) rep(i,1,3) s[25][i]='X';
        if (res==2) rep(i,1,6) s[25][i]='X';
        if (res==3) s[25][1]='X';
        if (res==4) rep(i,1,4) s[25][i]='X';
        if (res==5) rep(i,1,7) s[25][i]='X';
        if (res==6) rep(i,1,2) s[25][i]='X';
        if (res==7) rep(i,1,5) s[25][i]='X';
        rep(i,1,25)
        {
            rep(j,1,25) printf("%c",s[i][j]);
            puts("");
        }
    }
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}