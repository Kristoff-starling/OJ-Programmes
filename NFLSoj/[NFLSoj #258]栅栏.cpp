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

const int MAXN=2000;
const int MAXM=100000;

int n,m,q;

namespace BIT
{
    int c[MAXN+48][MAXN+48];
    inline void update(int x,int y,int delta)
    {
        int tmp=y;
        while (x<=n)
        {
            y=tmp;
            while (y<=m) c[x][y]^=delta,y+=LOWBIT(y);
            x+=LOWBIT(x);
        }
    }
    inline int query(int x,int y)
    {
        int tmp=y,res=0;
        while (x)
        {
            y=tmp;
            while (y) res^=c[x][y],y^=LOWBIT(y);
            x^=LOWBIT(x);
        }
        return res;
    }
}

map<pair<Pair,Pair>,int> Mp;

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);io.Get(q);
    int op,x1,y1,x2,y2;
    for (register int i=1;i<=q;i++)
    {
        io.Get(op);io.Get(x1);io.Get(y1);io.Get(x2);io.Get(y2);
        if (op==1)
        {
            int val=rand();
            Mp[mp(mp(x1,y1),mp(x2,y2))]=val;
            BIT::update(x1,y1,val);
            if (y2<m) BIT::update(x1,y2+1,val);
            if (x2<n) BIT::update(x2+1,y1,val);
            if (x2<n && y2<m) BIT::update(x2+1,y2+1,val);
        }
        if (op==2)
        {
            int val=Mp[mp(mp(x1,y1),mp(x2,y2))];
            BIT::update(x1,y1,val);
            if (y2<m) BIT::update(x1,y2+1,val);
            if (x2<n) BIT::update(x2+1,y1,val);
            if (x2<n && y2<m) BIT::update(x2+1,y2+1,val);
        }
        if (op==3)
        {
            int col1=BIT::query(x1,y1),col2=BIT::query(x2,y2);
            if (col1==col2) printf("Yes\n"); else printf("No\n");
        }
    }
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}