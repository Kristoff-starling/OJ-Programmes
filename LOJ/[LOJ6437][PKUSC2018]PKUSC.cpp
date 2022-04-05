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
const double eps=7e-6;
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

const int MAXN=500;

inline bool islarger(LB x,LB y) {return x-y>eps;}
inline bool issmaller(LB x,LB y) {return x-y<-eps;}
inline bool isequal(LB x,LB y) {return (!islarger(x,y)) && (!issmaller(x,y));}

int n,m;

struct Vector
{
    LB x,y;
    Vector () {}
    inline Vector(LB xx,LB yy) {x=xx;y=yy;}
    inline void input() {io.Get(x);io.Get(y);}
    inline LB calc_dist() {return sqrt(x*x+y*y);}
    inline LB calc_Dist() {return x*x+y*y;}
    inline LB calc_ang()
    {
        if (isequal(x,0)) return islarger(y,0)?pi/2:pi/2*3;
        LB res=atan2(y,x);
        if (!issmaller(res,0)) return res; else return pi*2+res;
    }
    inline bool operator == (const Vector &other) const {return isequal(x,other.x) && isequal(y,other.y);}
    inline bool operator != (const Vector &other) const {return (!isequal(x,other.x)) || (!isequal(y,other.y));}
    inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
    inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
    inline Vector operator * (LB t) {return Vector(x*t,y*t);}
    inline Vector operator / (LB t) {return Vector(x/t,y/t);}
    inline LB dot(Vector other) {return x*other.x+y*other.y;}
    inline LB det(Vector other) {return x*other.y-y*other.x;}
}a[MAXN+48],b[MAXN+48];
vector<Vector> ipt;

struct Line
{
    Vector pt1,pt2;
    Line () {}
    inline Line (Vector tmp1,Vector tmp2) {pt1=tmp1;pt2=tmp2;}
}edge[MAXN+48];

inline bool on_seg(Vector pt,Line l)
{
    return isequal((l.pt1-pt).det(l.pt2-pt),0) && (!islarger((l.pt1-pt).dot(l.pt2-pt),0));
}

inline Vector query_projection(Vector pt1,Vector pt2,Vector pt3)
{
    if (on_seg(pt3,Line(pt1,pt2))) return pt3;
    LB k=(pt3-pt1).dot(pt2-pt1)/(pt2-pt1).dot(pt2-pt1);
    return pt1+(pt2-pt1)*k;
}

inline void doit_intersection(LB r,Line l)
{
    Vector pt1=l.pt1,pt2=l.pt2;
    Vector pt0=query_projection(pt1,pt2,Vector(0,0));
    if (islarger(pt0.calc_Dist(),r)) return;
    Vector e=(pt2-pt1)/(pt2-pt1).calc_dist();
    LB delta=sqrt(r-pt0.calc_Dist());
    Vector ins=pt0+e*delta;if (on_seg(ins,l)) ipt.pb(ins);
    ins=pt0-e*delta;if (on_seg(ins,l)) ipt.pb(ins);
}

inline bool in_polygon(Vector pt)
{
    for (register int i=1;i<=m;i++) if (on_seg(pt,edge[i])) return false;
    bool in=false;
    for (register int i=1;i<=m;i++)
        if ((issmaller(edge[i].pt1.y,pt.y) && (!issmaller(edge[i].pt2.y,pt.y))) || ((!issmaller(edge[i].pt1.y,pt.y)) && issmaller(edge[i].pt2.y,pt.y)))
        {
            LB coef=(pt.y-edge[i].pt1.y)/(edge[i].pt2.y-edge[i].pt1.y);
            Vector inter=edge[i].pt1+(edge[i].pt2-edge[i].pt1)*coef;
            if (islarger(inter.x,pt.x)) in^=1;
        }
    return in;
}

inline Vector getmid(Vector pt1,Vector pt2,bool type)
{
    LB r=pt1.calc_dist();
    LB seta1=pt1.calc_ang(),seta2=pt2.calc_ang()+(type?pi*2:0);
    LB seta=(seta1+seta2)/2;
    return Vector(r*cos(seta),r*sin(seta));
}

inline LB calc_ang(Vector pt1,Vector pt2,bool type)
{
    LB seta1=pt1.calc_ang(),seta2=pt2.calc_ang()+(type?pi*2:0);
    return seta2-seta1;
}

inline bool cmp(Vector x,Vector y) {return issmaller(x.calc_ang(),y.calc_ang());}

int main ()
{
#ifdef LOCAL
    double TIME=clock();
    freopen ("a.in","r",stdin);
    freopen ("a.out","w",stdout);
    cerr<<"Running..."<<endl;
#endif
    io.Get(n);io.Get(m);LB ans=0;
    for (register int i=1;i<=n;i++) a[i].input();
    for (register int i=1;i<=m;i++) b[i].input();
    for (register int i=1;i<=m;i++) edge[i]=Line(b[i],b[i%m+1]);
    for (register int i=1;i<=n;i++)
    {
        if (a[i]==Vector(0,0))
        {
            if (in_polygon(a[i])) ans++;
            continue;
        }
        ipt.clear();
        for (register int j=1;j<=m;j++) doit_intersection(a[i].calc_Dist(),edge[j]);
        sort(ipt.begin(),ipt.end(),cmp);
        ipt.resize(unique(ipt.begin(),ipt.end())-ipt.begin());
        if (int(ipt.size())<2)
        {
            bool polygon_in_circle=true;
            for (register int j=1;j<=m;j++)
                if (islarger(b[j].calc_Dist(),a[i].calc_Dist())) {polygon_in_circle=false;break;}
            if (!polygon_in_circle) ans++;
            continue;
        }
        LB sang=0;
        for (register int j=0;j<int(ipt.size());j++)
        {
            Vector pt1=ipt[j],pt2=ipt[(j+1)%int(ipt.size())];
            Vector M=getmid(pt1,pt2,j==(int(ipt.size())-1));
            if (in_polygon(M)) sang+=calc_ang(pt1,pt2,j==(int(ipt.size())-1));
        }
        ans+=sang/(pi*2);
    }
    double Ans=ans;
    printf("%.5lf\n",Ans);
#ifdef LOCAL
    cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}