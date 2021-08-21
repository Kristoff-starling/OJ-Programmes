#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LD long double
using namespace std;

const LD pi=acos(-1);
const LD eps=1e-12;

int dcmp(LD x)
{
    if (fabs(x)<eps) return 0;
    if (x>0) return 1; else return -1;
}

struct Point
{
    LD x,y;
    Point () {}
    Point (LD a,LD b): x(a),y(b) {}
    void print() {cerr<<x<<' '<<y<<endl;}
    friend Point operator + (const Point &a,const Point &b) {return Point(a.x+b.x,a.y+b.y);}
    friend Point operator - (const Point &a,const Point &b) {return Point(a.x-b.x,a.y-b.y);}
    friend bool operator == (const Point &a,const Point &b) {return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;}
    friend Point operator * (const Point &a,const LD &b) {return Point(a.x*b,a.y*b);}
    friend Point operator * (const LD &a,const Point &b) {return Point(a*b.x,a*b.y);}
    friend Point operator / (const Point &a,const LD &b) {return Point(a.x/b,a.y/b);}
    LD norm () {return sqrt(x*x+y*y);}
};

double det(const Point &a,const Point &b) {return a.x*b.y-a.y*b.x;}
double dot(const Point &a,const Point &b) {return a.x*b.x+a.y*b.y;}
double dist(const Point &a,const Point &b) {return (a-b).norm();}
Point rotate_point(const Point &p,double A)
{
    LD tx=p.x,ty=p.y;
    return Point(tx*cos(A)-ty*sin(A),tx*sin(A)+ty*cos(A));
}

double x1,y1,R1,x2,y2,R2,a;

LD solve(LD r1,Point o1,LD r2,Point o2)
{
    LD d = (o1-o2).norm();
    LD ang1 = acos((r1*r1+d*d-r2*r2)/2./r1/d);
    LD ang2 = acos((r2*r2+d*d-r1*r1)/2./r2/d);
    LD ret = ang1*r1*r1+ang2*r2*r2-d*r1*sin(ang1);
    return ret;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf",&R1,&x1,&y1,&R2,&x2,&y2,&a);
        if (R2*R2+R2*R2<=a*a) {puts("0.000000");continue;}
        LD r1,r2;
        r1=sqrt(R1*R1-a*a/4)-a/2;r2=sqrt(R2*R2-a*a/4)-a/2;
        Point o1=Point(x1,y1),o2=Point(x2,y2);LD d=(o1-o2).norm();
        if (dcmp(r1+r2-d)!=1) {puts("0.000000");continue;}
        if (dcmp(r2-r1-d)!=-1) {puts("1.000000");continue;}
        if (dcmp(r1-r2-d)!=-1) {LD ans=r2*r2/r1/r1;double aans=ans;printf("%.6lf\n",aans);continue;}
        LD res=solve(r1,o1,r2,o2);res=res/pi/r1/r1;
        double rres=res;
        printf("%.6lf\n",rres);
    }
    return 0;
}