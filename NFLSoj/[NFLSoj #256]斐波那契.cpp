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
int a[MAXN+48],pre[MAXN+48];

int fib[48],ftot;

struct node
{
    int val,ind;
    node () {}
    inline node (int vv,int ii) {val=vv;ind=ii;}
    inline bool operator < (const node &other) const
    {
        if (val!=other.val) return val<other.val;
        return ind<other.ind;
    }
}b[MAXN+48];

map<int,Pair> pos;
int p[MAXN+48],ptot;

inline int bsearch(int L,int R,int cmp)
{
    int l=L,r=R,mid,res=0;
    while (l<=r)
    {
        mid=(l+r)>>1;
        if (p[mid]<cmp) res=p[mid],l=mid+1; else r=mid-1;
    }
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
    io.Get(n);
    for (register int i=1;i<=n;i++) io.Get(a[i]),b[i]=node(a[i],i);
    fib[1]=1;fib[2]=2;
    for (ftot=3;;ftot++)
    {
        LL tmp=fib[ftot-1];tmp+=fib[ftot-2];
        if (tmp>INF) {ftot--;break;}
        fib[ftot]=tmp;
    }
    sort(b+1,b+n+1);
    int pt1=1,pt2;
    while (pt1<=n)
    {
        pt2=pt1;
        while (pt2<n && b[pt2+1].val==b[pt1].val) pt2++;
        pos[b[pt1].val]=mp(pt1,pt2);
        for (register int i=ptot+1;i<=ptot+(pt2-pt1+1);i++) p[i]=b[i].ind;
        ptot+=(pt2-pt1+1);
        pt1=pt2+1;
    }
    for (register int i=1;i<=n;i++)
    {
        pre[i]=1;
        for (register int j=1;j<=ftot;j++)
        {
            int need=fib[j]-a[i];
            if (need<0 || pos.find(need)==pos.end()) continue;
            Pair interval=pos[need];
            check_max(pre[i],bsearch(interval.x,interval.y,i)+1);
        }
    }
    int ans=1,maxn=0;
    for (register int i=n;i>=1;i--)
    {
        maxn=max(maxn,pre[i]);
        if (i==maxn && i!=1) ans++,maxn=0;
    }
    io.Print(ans,'\n');
    io.flush();
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}