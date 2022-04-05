#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-12;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline double myabs(double x) {if (x>eps) return x;if (x<-eps) return -x;return 0;}
inline bool islarger(double x,double y) {return x-y>eps;}
inline bool issmaller(double x,double y) {return x-y<-eps;}
inline bool isequal(double x,double y) {return myabs(x-y)<eps;}
struct Vector
{
	double x,y;
	Vector () {}
	inline Vector(double xx,double yy) {x=xx;y=yy;}
	inline double calc_k() {if (!isequal(x,0)) return y/x;if (islarger(y,0)) return INF; else return -INF;}
	inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
	inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
	inline Vector operator * (double t) {return Vector(x*t,y*t);}
	inline double dot(Vector other) {return x*other.x+y*other.y;}
	inline double det(Vector other) {return x*other.y-y*other.x;}
	inline bool operator < (const Vector &other) const {return issmaller(x,other.x);}
}a[148],lft[148],rght[148],middle[148],tmp[148];int ltot,rtot,mtot,tot;

class BatmanAndRobin
{
	int n;
	struct Line
	{
		Vector pt,dir;
		Line () {}
		inline Line(Vector x,Vector y) {pt=x;dir=y;}
	}border;
	inline int judgepos(Line l,Vector pt)
	{
		double res=l.dir.det(pt-l.pt);
		if (islarger(res,0)) return -1;
		if (issmaller(res,0)) return 1;
		return 0;
	}
	Vector s[148],conv[148];int stot,ctot;
	inline double calc_convex()
	{
		sort(tmp+1,tmp+tot+1);
		ctot=0;stot=1;s[1]=tmp[1];int i;
		for (i=2;i<=tot;i++)
		{
			while (stot>1 && !issmaller((s[stot]-s[stot-1]).calc_k(),(tmp[i]-s[stot]).calc_k())) stot--;
			s[++stot]=tmp[i];
		}
		for (i=1;i<=stot;i++) conv[++ctot]=s[i];
		//reverse(tmp+1,tmp+tot+1);
		stot=1;s[1]=tmp[1];
		for (i=2;i<=tot;i++)
		{
			while (stot>1 && !islarger((s[stot]-s[stot-1]).calc_k(),(tmp[i]-s[stot]).calc_k())) stot--;
			s[++stot]=tmp[i];
		}
		for (i=stot-1;i>=2;i--) conv[++ctot]=s[i];
		double res=0;Vector curVec=conv[2]-conv[1];
		for (i=3;i<=ctot;i++)
		{
			res+=0.5*curVec.det(conv[i]-conv[1]);
			curVec=conv[i]-conv[1];
		}
		return res;
	}
	inline double calc()
	{
		int i,res;
		double ans=INF,larea,rarea;
		ltot=rtot=mtot=0;
		for (i=1;i<=n;i++)
		{
			res=judgepos(border,a[i]);
			if (res==-1) lft[++ltot]=a[i];
			if (!res) middle[++mtot]=a[i];
			if (res==1) rght[++rtot]=a[i];
		}
		tot=0;
		for (i=1;i<=ltot;i++) tmp[++tot]=lft[i];
		for (i=1;i<=mtot;i++) tmp[++tot]=middle[i];
		larea=calc_convex();
		tot=0;
		for (i=1;i<=rtot;i++) tmp[++tot]=rght[i];
		rarea=calc_convex();
		ans=min(ans,max(larea,rarea));
		tot=0;
		for (i=1;i<=ltot;i++) tmp[++tot]=lft[i];
		larea=calc_convex();
		tot=0;
		for (i=1;i<=mtot;i++) tmp[++tot]=middle[i];
		for (i=1;i<=rtot;i++) tmp[++tot]=rght[i];
		rarea=calc_convex();
		ans=min(ans,max(larea,rarea));
		return ans;
	}
	public:
		inline double minArea(vector<int> x,vector<int> y)
		{
			n=int(x.size());int i,j;
			if (n<=4) return 0;
			double ans=INF;
			for (i=1;i<=n;i++) a[i]=Vector(x[i-1],y[i-1]);
			for (i=1;i<=n-1;i++)
				for (j=i+1;j<=n;j++)
				{
					border=Line(a[i],a[j]-a[i]);
					ans=min(ans,calc());
				}
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	int nn,x;vector<int> xx,yy;
	BatmanAndRobin A;
	while (scanf("%d",&nn)!=EOF)
	{
		xx.clear();yy.clear();
		int i;
		for (i=1;i<=nn;i++) x=getint(),xx.pb(x);
		for (i=1;i<=nn;i++) x=getint(),yy.pb(x);
		printf("%.10lf\n",A.minArea(xx,yy));
	}
	return 0;
}
*/
