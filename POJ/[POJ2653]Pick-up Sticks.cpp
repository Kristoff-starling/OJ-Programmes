#include <cstdio>
#include <iostream>
#include <cmath>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e5;
const double eps=1e-8;
const double pi=acos(-1);

int dcmp(double x)
{
    if (fabs(x)<eps) return 0;
    if (x>0) return 1; else return -1;
}

struct Point
{
    double x,y;
    Point () {}
    Point (double a,double b): x(a),y(b) {}
    void input() {scanf("%lf%lf",&x,&y);}
    void print() {cerr<<x<<' '<<y<<endl;}
    friend Point operator + (const Point &a,const Point &b) {return Point(a.x+b.x,a.y+b.y);}
    friend Point operator - (const Point &a,const Point &b) {return Point(a.x-b.x,a.y-b.y);}
    friend bool operator == (const Point &a,const Point &b) {return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;}
    friend Point operator * (const Point &a,const double &b) {return Point(a.x*b,a.y*b);}
    friend Point operator * (const double &a,const Point &b) {return Point(a*b.x,a*b.y);}
    friend Point operator / (const Point &a,const double &b) {return Point(a.x/b,a.y/b);}
    double norm () {return sqrt(x*x+y*y);}
};
double det(const Point &a,const Point &b) {return a.x*b.y-a.y*b.x;}
double dot(const Point &a,const Point &b) {return a.x*b.x+a.y*b.y;}
double dist(const Point &a,const Point &b) {return (a-b).norm();}
Point rotate_point(const Point &p,double A)
{
    double tx=p.x,ty=p.y;
    return Point(tx*cos(A)-ty*sin(A),tx*sin(A)+ty*cos(A));
}

struct Line
{
    Point a,b;
    Line () {}
    Line (Point x,Point y): a(x),b(y) {}
    void input() {a.input();b.input();}
};

double dis_point_segment(const Point p,const Point s,const Point t)
{
    if (dcmp(dot(p-s,t-s))<0) return (p-s).norm();
    if (dcmp(dot(p-t,s-t))<0) return (p-t).norm();
    return fabs(det(s-p,t-p)/dist(s,t));
}

void PointProjLine(const Point p,const Point s,const Point t,Point &cp)
{
    double r=dot((t-s),(p-s))/dot(t-s,t-s);
    cp=s+r*(t-s);
}

bool PointOnSegment(Point p,Point s,Point t)
{
    return dcmp(det(p-s,t-s))==0 && dcmp(dot(p-s,p-t))<=0;
}

bool PointOnSegment(Point p,Line l) {return PointOnSegment(p,l.a,l.b);}

bool parallel(Line a,Line b) {return !dcmp(det(a.a-a.b,b.a-b.b));}

bool line_make_point(Line a,Line b,Point &res)
{
    if (parallel(a,b)) return false;
    double s1=det(a.a-b.a,b.b-b.a),s2=det(a.b-b.a,b.b-b.a);
    res=(s1*a.b-s2*a.a)/(s1-s2);
    return true;
}

Line move_d(Line a,const double &len)
{
    Point d=a.b-a.a;
    d=d/d.norm();
    d=rotate_point(d,pi/2);
    return Line(a.a+d*len,a.b+d*len);
}

int n;
Line a[MAXN+48];

int main ()
{
    while (scanf("%d",&n) && n)
    {
        rep(i,1,n) a[i].input();
        Point tmp;
        printf("Top sticks: ");int cnt=0;
        rep(i,1,n)
        {
            bool f=true;Point tmp;
            rep(j,i+1,n)
            {
                bool res=line_make_point(a[i],a[j],tmp);
                if (res && PointOnSegment(tmp,a[i]) && PointOnSegment(tmp,a[j])) {f=false;break;}
            }
            if (f)
            {
                ++cnt;
                if (cnt==1) printf("%d",i); else printf(", %d",i);
            }
        }
        puts(".");
    }
    return 0;
}