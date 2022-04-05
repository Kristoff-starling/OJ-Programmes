// I'll always miss you like a darling.
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
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-9;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

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
    template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}
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

inline bool islarger(LD x,LD y) {return x-y>eps;}
inline bool issmaller(LD x,LD y) {return x-y<-eps;}
inline bool isequal(LD x,LD y) {return !islarger(x,y) && !issmaller(x,y);}

struct Point
{
	LD x,y;
	Point () {}
	inline Point (LD _x,LD _y) {x=_x;y=_y;}
	inline Point operator + (Point other) {return Point(x+other.x,y+other.y);}
	inline Point operator - (Point other) {return Point(x-other.x,y-other.y);}
	inline Point operator * (LD t) {return Point(x*t,y*t);}
	inline LD dot(Point other) {return x*other.x+y*other.y;}
	inline LD det(Point other) {return x*other.y-y*other.x;}
	inline LD dist() {return sqrt(x*x+y*y);}
	inline LD dist(Point other) {return (other-(*this)).dist();}
	inline Point rotate(LD ang) {Point vec=Point(cos(ang),sin(ang));return Point(x*vec.x-y*vec.y,x*vec.y+y*vec.x);}
	inline bool operator == (Point &other) const {return isequal(x,other.x) && isequal(y,other.y);}
};

struct Circle
{
	Point center;LD r;
	Circle () {}
	inline Circle(Point _c,LD _r) {center=_c;r=_r;}
	inline LD area() {return r*r*pi;}
	inline LD perimeter() {return r*2*pi;}
	inline LD diameter() {return r*2;}
	inline Point getPoint(LD ang) {return center+Point(r,0).rotate(ang);}
	inline bool operator == (Circle &other) const {return center==other.center && isequal(r,other.r);}
};

inline LD getcos(LD a,LD b,LD c) {return (a*a+b*b-c*c)/(2*a*b);}

inline LD CircleIntersection(Circle c1,Circle c2)
{
	if (islarger(c1.r,c2.r)) swap(c1,c2);
	LD d=c1.center.dist(c2.center);
	if (!issmaller(d,c1.r+c2.r)) return 0;
	if (!islarger(d+c1.r,c2.r)) return c1.area();
	LD ang1=acos(getcos(c1.r,d,c2.r)),ang2=acos(getcos(c2.r,d,c1.r));
	return c1.r*c1.r*ang1+c2.r*c2.r*ang2-sin(2*ang1)*c1.r*c1.r/2-sin(2*ang2)*c2.r*c2.r/2;
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int x1,y1,r1,x2,y2,r2;
	Get(x1,y1,r1,x2,y2,r2);
	double res=CircleIntersection(Circle(Point(x1,y1),r1),Circle(Point(x2,y2),r2));
	printf("%.20lf\n",res);
	io.flush();
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}

