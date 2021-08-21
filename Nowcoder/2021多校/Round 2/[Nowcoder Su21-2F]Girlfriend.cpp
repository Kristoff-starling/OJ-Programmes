#include <bits/stdc++.h>
using namespace std;

const double eps=1e-5;
const double pi=acos(-1);

bool islarger(double x,double y) {return x-y>eps;}
bool issmaller(double x,double y) {return x-y<-eps;}
bool isequal(double x,double y) {return abs(x-y)<eps;}

double k1,k2,ans;

struct Point
{
    double x,y,z;
    void input() {scanf("%lf%lf%lf",&x,&y,&z);}
    Point() {}
    Point(double _x,double _y,double _z) {x=_x;y=_y;z=_z;}
    double len() {return sqrt(x*x+y*y+z*z);}
    Point operator + (Point other) {return Point(x+other.x,y+other.y,z+other.z);}
    Point operator - (Point other) {return Point(x-other.x,y-other.y,z-other.z);}
    Point operator * (double p) {return Point(x*p,y*p,z*p);}
    void print() {cerr<<x<<' '<<y<<' '<<z<<endl;}
}A,B,C,D;

Point midpoint(Point x,Point y) {return Point((x.x+y.x)/2,(x.y+y.y)/2,(x.z+y.z)/2);}

double R1,R2;Point o1,o2;

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        A.input();B.input();C.input();D.input();scanf("%lf%lf",&k1,&k2);
        Point t1=A+(B-A)*(k1/(k1+1)),t2=A+(B-A)*(k1/(k1-1));
        o1=midpoint(t1,t2);R1=(o1-t1).len();
        t1=C+(D-C)*(k2/(k2+1));t2=C+(D-C)*(k2/(k2-1));
        o2=midpoint(t1,t2);R2=(o2-t1).len();
        o1.print();o2.print();
        double L=(o1-o2).len();
        if (!issmaller(L,R1+R2)) {puts("0.000");continue;}
        if (islarger(R2,R1)) swap(R1,R2),swap(o1,o2); if (!islarger(L,R1-R2)) {printf("%.3lf\n",pi*4/3*R2*R2*R2);continue;}
        ans=0;
        double cosa=(L*L+R1*R1-R2*R2)/2/R1/L;
        double tmp=pi*R1*R1*R1;
        ans+=tmp*2/3-tmp*cosa+tmp*cosa*cosa*cosa/3;
        cosa=(L*L+R2*R2-R1*R1)/2/R2/L;tmp=pi*R2*R2*R2;
        ans+=tmp*2/3-tmp*cosa+tmp*cosa*cosa*cosa/3;
        printf("%.3lf\n",ans);
    }
    return 0;
}