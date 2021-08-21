#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

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

struct frac
{
    #define LL __int128
    template<typename T> T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
    template<typename T> T myabs(T x) {if (x>=0) return x; else return -x;}

    LL num,den;
    frac (LL num=0,LL den=1)
    {
        if (den==1) {this->num=num;this->den=den;return;}
        if (den<0) num=-num,den=-den;
        assert(den!=0);
        LL g=mygcd(myabs(num),den);
        this->num=num/g;this->den=den/g;
    }
    // void print() {cerr<<num<<'/'<<den<<endl;}
    frac operator + (const frac &other) const
    {
        if (den==1 && other.den==1) return frac(num+other.num,1);
        return frac(num*other.den+den*other.num,den*other.den);
    }
    frac operator - (const frac &other) const
    {
        if (den==1 && other.den==1) return frac(num-other.num,1);
        return frac(num*other.den-den*other.num,den*other.den);
    }
    frac operator * (const frac &other) const {return frac(num*other.num,den*other.den);}
    frac operator / (const frac &other) const {return frac(num*other.den,den*other.num);}
    bool operator <  (const frac &other) const {return num*other.den<den*other.num;}
    bool operator == (const frac &other) const {return num*other.den==den*other.num;}
    bool operator <= (const frac &other) const {return num*other.den<=den*other.num;}
};

#define double frac
struct Point
{
    double x,y;
    Point () {}
    Point (double a,double b): x(a),y(b) {}
    friend Point operator + (const Point &a,const Point &b) {return Point(a.x+b.x,a.y+b.y);}
    friend Point operator - (const Point &a,const Point &b) {return Point(a.x-b.x,a.y-b.y);}
    // friend bool operator == (const Point &a,const Point &b) {return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;}
    friend bool operator == (const Point &a,const Point &b) {return a.x-b.x==frac(0,1) && a.y-b.y==frac(0,1);}
    friend Point operator * (const Point &a,const double &b) {return Point(a.x*b,a.y*b);}
    friend Point operator * (const double &a,const Point &b) {return Point(a*b.x,a*b.y);}
    friend Point operator / (const Point &a,const double &b) {return Point(a.x/b,a.y/b);}
    // double norm () {return sqrt(x*x+y*y);}
    double norm () {return x*x+y*y;}
};
double det(const Point &a,const Point &b) {return a.x*b.y-a.y*b.x;}
double dot(const Point &a,const Point &b) {return a.x*b.x+a.y*b.y;}
double dist(const Point &a,const Point &b) {return (a-b).norm();}

struct Line
{
    Point a,b;
    Line () {}
    Line (Point x,Point y): a(x),b(y) {}
};

double dis_point_segment(const Point p,const Point s,const Point t)
{
    if (dot(p-s,t-s)<frac(0,1)) return (p-s).norm();
    if (dot(p-t,s-t)<frac(0,1)) return (p-t).norm();
    // return fabs(det(s-p,t-p)/dist(s,t));
    return det(s-p,t-p)*det(s-p,t-p)/dist(s,t);
}

double dis_point_segment(const Point p,const Line l) {return dis_point_segment(p,l.a,l.b);}

void PointProjLine(const Point p,const Point s,const Point t,Point &cp)
{
    double r=dot((t-s),(p-s))/dot(t-s,t-s);
    cp=s+r*(t-s);
}

#undef double

const int MAXN=3e5;
const int MOD=1e9+7;

template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}
template<typename T> void check_max(T &x,T y) {if (x<y) x=y;}

int m,n;
Point a[MAXN+48],b[MAXN+48];

int quick_pow(int x,int y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%MOD;
        x=1ll*x*x%MOD;y>>=1;
    }
    return res;
}

int main ()
{
    int ca;io.Get(ca);
    while (ca--)
    {
        io.Get(m);int x,y;
        rep(i,1,m)
        {
            io.Get(x);io.Get(y);
            a[i].x=frac(x,1);a[i].y=frac(y,1);
            a[i+m]=a[i+2*m]=a[i];
        }
        io.Get(n);
        rep(i,1,n)
        {
            io.Get(x);io.Get(y);
            b[i].x=frac(x,1);b[i].y=frac(y,1);
        }
        frac minn=frac(1e16,1);int pos;
        rep(i,1,m)
        {
            frac dis=dis_point_segment(b[1],a[i],a[i+1]);
            if (dis<minn) pos=i,minn=dis;
        }
        frac ans=minn;
        rep(i,2,n)
        {
            while (pos<m*3-1 && dis_point_segment(b[i],a[pos+1],a[pos+2])<=dis_point_segment(b[i],a[pos],a[pos+1])) pos++;
            frac dis=dis_point_segment(b[i],a[pos],a[pos+1]);
            check_max(ans,dis);
        }
        int xx=ans.num%MOD,yy=ans.den%MOD;
        yy=quick_pow(yy,MOD-2);xx=1ll*xx*yy%MOD;
        io.Print(xx,'\n');
    }
    io.flush();
    return 0;
}
