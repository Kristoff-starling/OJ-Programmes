#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LD long double
#define LL long long
using namespace std;

const int MAXN=1e5;
const LD eps=1e-12;
const LD pi=acos(-1);

int sgn(LL x) {if (x>0) return 1; else return -1;}

struct Point
{
    LL x,y;
    Point () {}
    Point (LL a,LL b): x(a),y(b) {}
    void input() {scanf("%lld%lld",&x,&y);}
    void print() {cerr<<x<<' '<<y<<endl;}
    friend Point operator + (const Point &a,const Point &b) {return Point(a.x+b.x,a.y+b.y);}
    friend Point operator - (const Point &a,const Point &b) {return Point(a.x-b.x,a.y-b.y);}
    friend bool operator == (const Point &a,const Point &b) {return a.x==b.x && a.y==b.y;}
    friend Point operator * (const Point &a,const LD &b) {return Point(a.x*b,a.y*b);}
    friend Point operator * (const LD &a,const Point &b) {return Point(a*b.x,a*b.y);}
    LL norm() {return x*x+y*y;}
};
LL det(const Point &a,const Point &b) {return a.x*b.y-a.y*b.x;}
LL dot(const Point &a,const Point &b) {return a.x*b.x+a.y*b.y;}

struct Line
{
    Point a,b;
    Line () {}
    Line (Point x,Point y): a(x),b(y) {}
    void input() {a.input();b.input();}
};

bool parallel(Line a,Line b) {return det(a.a-a.b,b.a-b.b)==0;}

bool PointOnSegment(Point p, Line b)
{
    return det(p-b.a,p-b.b)==0 && (p-b.a).norm()<=(b.b-b.a).norm() && (p-b.b).norm()<=(b.b-b.a).norm();
}

int n;
Line a[MAXN+48];

int main ()
{
    scanf("%d",&n);
    rep(i,1,n) a[i].input();
    Point tmp;
    int cnt=0;
    rep(i,1,n)
    {
        bool f=true;Point tmp;
        rep(j,i+1,n)
        {
            if (PointOnSegment(a[i].a,a[j]) || \
                PointOnSegment(a[i].b,a[j]) || \
                PointOnSegment(a[j].a,a[i]) || \
                PointOnSegment(a[j].b,a[i]))
                {f=false;break;}
            if (sgn(det(a[j].a-a[i].a,a[j].b-a[i].a)) != sgn(det(a[j].a-a[i].b,a[j].b-a[i].b)) \
             && sgn(det(a[i].a-a[j].a,a[i].b-a[j].a)) != sgn(det(a[i].a-a[j].b,a[i].b-a[j].b)))
                {f=false;break;}
        }
        if (f) ++cnt;
    }
    printf("%d\n",cnt);
    return 0;
}