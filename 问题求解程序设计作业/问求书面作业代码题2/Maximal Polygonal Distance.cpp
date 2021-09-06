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
const double eps=1e-9;
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

int dcmp(double x)
{
    if (fabs(x)<eps) return 0;
    if (x>eps) return 1; else return -1;
}

void check_max(double &x,double y) {if (dcmp(y-x)==1) x=y;}

struct Point
{
    double x,y;
    Point () {}
    Point (double _x,double _y) {x=_x;y=_y;}
    Point operator + (Point other) {return Point(x+other.x,y+other.y);}
    Point operator - (Point other) {return Point(x-other.x,y-other.y);}
    Point operator * (double coef) {return Point(x*coef,y*coef);}
    friend double dot(const Point &x,const Point &y) {return x.x*y.x+x.y*y.y;}
    friend double Cross(const Point &x,const Point &y) {return x.x*y.y-x.y*y.x;}
    friend double Dist2(const Point &x,const Point &y) {return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);}
    friend double Dist(const Point &x,const Point &y) {return sqrt(Dist2(x,y));}
    void Print() {printf("%.10lf %.10lf\n",x,y);}
};

double DistLinePoint(Point A,Point B,Point C) {return fabs(Cross(C-A,B-A))/Dist(A,B);}

int n;Point a[MAXN+48];

inline int nxt(int x) {x++;if (x>n) x=1;return x;}
inline int pre(int x) {x--;if (x<0) x=n;return x;}

int main ()
{
#ifndef ONLINE_JUDGE
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    scanf("%d",&n);int x,y;
    rep(i,1,n) scanf("%d%d",&x,&y),a[i]=Point(x,y);a[n+1]=a[1];
    int pt=2;double ans=0,pdist,cdist;
    rep(i,1,n) check_max(ans,Dist(a[i],a[i+1]));
    rep(i,1,n)
    {
        pdist=-1;cdist=DistLinePoint(a[i],a[i+1],a[pt]);
        while (dcmp(cdist-pdist)>=0)
        {
            check_max(ans,Dist(a[i],a[pt]));check_max(ans,Dist(a[i+1],a[pt]));
            pt=nxt(pt);pdist=cdist;cdist=DistLinePoint(a[i],a[i+1],a[pt]);
        }
        pt=pre(pt);
    }
    printf("%.15lf\n",ans);
#ifndef ONLINE_JUDGE
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}