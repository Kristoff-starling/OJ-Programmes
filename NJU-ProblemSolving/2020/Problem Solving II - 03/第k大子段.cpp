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
template<typename T> inline T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
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

int a[MAXN+48];LL s[MAXN+48];

struct segment
{
    int l,r;
    segment () {}
    inline segment(int _l,int _r) {l=_l;r=_r;}
    bool operator < (const segment &other) const
    {
        if (l==-1) return false;
        if (other.l==-1) return true;
        LL s1=s[r]-s[l-1],s2=s[other.r]-s[other.l-1];
        if (s1!=s2) return s1>s2;
        if (l!=other.l) return l<other.l;
        return r<other.r;
    }
};

struct element
{
    segment a[11];
    element () {rep(i,1,10) a[i].l=a[i].r=-1;}
    void Sort() {sort(a+1,a+11);}
};

int b1[MAXN+48],b2[MAXN+48];
segment L[149];int tot;

bool cmp1(int x,int y)
{
    if (s[x-1]!=s[y-1]) return s[x-1]<s[y-1];
    return x<y;
}

bool cmp2(int x,int y)
{
    if (s[x]!=s[y]) return s[x]>s[y];
    return x<y;
}

element doit(int l,int r)
{
    if (l==r)
    {
        element res;
        rep(i,1,10) res.a[i].l=-1;
        res.a[1].l=l;res.a[1].r=r;
        return res;
    }
    int mid=(l+r)>>1;
    element res1=doit(l,mid),res2=doit(mid+1,r);
    tot=0;rep(i,1,k) if (res1.a[i].l!=-1) L[++tot]=res1.a[i];
    rep(i,1,k) if (res2.a[i].l!=-1) L[++tot]=res2.a[i];
    int tot1=0,tot2=0;
    rep(i,l,mid) b1[++tot1]=i;rep(i,mid+1,r) b2[++tot2]=i;
    sort(b1+1,b1+tot1+1,cmp1);sort(b2+1,b2+tot2+1,cmp2);
    rep(i,1,min(k,tot1)) rep(j,1,min(k,tot2)) L[++tot]=segment(b1[i],b2[j]);
    sort(L+1,L+tot+1);
    element res;
    rep(i,1,min(k,tot)) res.a[i]=L[i];
    return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d%d",&n,&k);rep(i,1,n) scanf("%d",a+i);
    s[0]=0;rep(i,1,n) s[i]=s[i-1]+a[i];
    element res=doit(1,n);
    printf("%d %d\n",res.a[k].l,res.a[k].r);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}