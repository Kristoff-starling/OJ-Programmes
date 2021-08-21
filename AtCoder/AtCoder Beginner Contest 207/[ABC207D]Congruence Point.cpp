#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
using namespace std;

const double pi=acos(-1);
const double eps=1e-5;

int n;

bool smaller(double x,double y) {return x-y<-eps;}
bool larger(double x,double y) {return x-y>eps;}

struct Point
{
    int x,y;
    double ang;
    bool operator < (const Point &other) const
    {
        if (smaller(ang,other.ang) || larger(ang,other.ang)) return smaller(ang,other.ang);
        return x*x+y*y<other.x*other.x+other.y*other.y;
    }
    void input()
    {
        scanf("%d%d",&x,&y);
        x*=n;y*=n;
    }
    int len() {return x*x+y*y;}
}a[101],b[101];


int main ()
{
    scanf("%d",&n);rep(i,1,n) a[i].input();rep(i,1,n) b[i].input();
    int X=0,Y=0;rep(i,1,n) X+=a[i].x,Y+=a[i].y;
    X/=n;Y/=n;rep(i,1,n) a[i].x-=X,a[i].y-=Y;
    X=0;Y=0;rep(i,1,n) X+=b[i].x,Y+=b[i].y;
    X/=n;Y/=n;rep(i,1,n) b[i].x-=X,b[i].y-=Y;
    rep(i,1,n) a[i].ang=atan2(a[i].y,a[i].x),b[i].ang=atan2(b[i].y,b[i].x);
    sort(a+1,a+n+1);sort(b+1,b+n+1);bool ans=false;
    rep(i,1,n) if (a[1].len()==b[i].len())
    {
        double delta=b[i].ang-a[1].ang;bool f=true;
        if (smaller(delta,0)) delta+=pi*2;
        rep(j,2,n)
        {
            int to=i+j-1;if (to>n) to-=n;
            double d=b[to].ang-a[j].ang;
            if (smaller(d,0)) d+=pi*2;
            if (fabs(d-delta)>eps || b[to].len()!=a[j].len()) {f=false;break;}
        }
        ans|=f;
    }
    puts(ans?"Yes":"No");return 0;
}