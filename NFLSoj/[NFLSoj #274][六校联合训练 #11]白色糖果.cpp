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

const int MAXN=1e6;

int len;
char s[MAXN+48];

struct Matrix
{
    int b[4][4];
    inline void clear() {memset(b,0,sizeof(b));}
    inline void init_I() {clear();for (register int i=1;i<=3;i++) b[i][i]=1;}
    inline Matrix operator * (Matrix ma)
    {
        Matrix res;res.clear();
        for (register int i=1;i<=3;i++)
            for (register int j=1;j<=3;j++)
                for (register int k=1;k<=3;k++)
                    Add(res.b[i][j],1ll*b[i][k]*ma.b[k][j]%MOD);
        return res;
    }
}up,down,trans;

inline Matrix quick_pow(Matrix x,int y)
{
    Matrix res;res.init_I();
    while (y)
    {
        if (y&1) res=res*x;
        x=x*x;y>>=1;
    }
    return res;
}

inline void trans_left()
{
    for (register int i=1;i<=3;i++) trans.b[i][3]=trans.b[i][2];
    for (register int i=1;i<=3;i++) trans.b[i][2]=add(trans.b[i][1]+trans.b[i][3]);
}

inline void trans_right()
{
    for (register int i=1;i<=3;i++) trans.b[i][1]=trans.b[i][2];
    for (register int i=1;i<=3;i++) trans.b[i][2]=add(trans.b[i][1]+trans.b[i][3]);
}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(len);io.getstring(s+1);
    up.b[1][2]=up.b[1][3]=1;down.b[1][1]=down.b[1][2]=1;
    int pt1=1,pt2;
    while (pt1<=len)
    {
        pt2=pt1;trans.init_I();
        while (!isdigit(s[pt2])) {if (s[pt2]=='L') trans_left(); else trans_right();pt2++;}
        int pw=0;
        while (pt2<=len && isdigit(s[pt2])) pw=pw*10+s[pt2]-'0',pt2++;
        up=up*quick_pow(trans,pw);down=down*quick_pow(trans,pw);
        pt1=pt2;
    }
    printf("%lld\n",1ll*up.b[1][2]*quick_pow(down.b[1][2],MOD-2)%MOD);
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}