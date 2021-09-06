//I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
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
template<typename T> inline T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline LL quick_pow(LL x,T y) {LL res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n;
LL pw[48];

struct node
{
    int a,b,c,d;
    node (int _a,int _b,int _c,int _d) {a=_a;b=_b;c=_c;d=_d;}
    bool operator < (const node &other) const
    {
        if (a!=other.a) return a<other.a;
        if (b!=other.b) return b<other.b;
        if (c!=other.c) return c<other.c;
        return d<other.d;
    }
    node operator & (node other) {return node(a&other.a,b&other.b,c&other.c,d&other.d);}
    LL Count()
    {
        int cnt=__builtin_popcount(a)+__builtin_popcount(b)+__builtin_popcount(c)+__builtin_popcount(d);
        cnt=32-cnt;return pw[cnt]-2;
    }
    void print() {printf("%d.%d.%d.%d",a,b,c,d);}
};

set<pair<node,node> > s;
vector<pair<node,node> > ans;

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    pw[0]=1;rep(i,1,32) pw[i]=pw[i-1]+pw[i-1];
    scanf("%d",&n);int a1,a2,a3,a4,b1,b2,b3,b4;
    while (n--)
    {
        scanf("%d.%d.%d.%d %d.%d.%d.%d",&a1,&a2,&a3,&a4,&b1,&b2,&b3,&b4);
        node A=node(a1,a2,a3,a4),B=node(b1,b2,b3,b4),C=A&B;
        if (s.find(mp(C,B))==s.end()) ans.pb(mp(C,B)),s.insert(mp(C,B));
    }
    sort(ans.begin(),ans.end());
    for (auto item : ans) item.x.print(),printf(" %lld\n",item.y.Count());
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}