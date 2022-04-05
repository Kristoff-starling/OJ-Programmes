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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=1e5;

int n;

inline double myabs(double x) {if (x>eps) return x;if (x<-eps) return -x;return 0;}
inline bool islarger(double x,double y) {return x-y>eps;}
inline bool issmaller(double x,double y) {return x-y<-eps;}
inline bool isequal(double x,double y) {return myabs(x-y)<eps;}

struct Vector
{
	double x,y;
	Vector () {}
	inline Vector (double xx,double yy) {x=xx;y=yy;}
	inline double calc_k()
	{
		if (isequal(x,0)) return islarger(y,0)?INF:-INF;
		return y/x;
	}
	inline double calc_ang() {return atan2(y,x);}
	inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
	inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
	inline Vector operator * (double t) {return Vector(x*t,y*t);}
	inline double dot(Vector other) {return x*other.x+y*other.y;}
	inline double det(Vector other) {return x*other.y-y*other.x;}
};

struct Line
{
	Vector pt1,pt2;int ind;
	double ang;
	inline void set_ang() {ang=(pt2-pt1).calc_ang();}
	inline bool operator < (const Line &other) const {return ang<other.ang;}
	inline double dot(Vector other) {return (pt2-pt1).dot(other);}
	inline double dot(Line other) {return (pt2-pt1).dot(other.pt2-other.pt1);}
	inline double det(Vector other) {return (pt2-pt1).det(other);}
	inline double det(Line other) {return (pt2-pt1).det(other.pt2-other.pt1);}
}L[MAXN+48];

inline bool OnTheLeft(Line l,Vector pt) {return islarger(l.det(pt-l.pt1),0);}
inline bool OnTheLine(Line l,Vector pt) {return isequal((l.pt1-pt).det(l.pt2-pt),0) && !islarger((l.pt1-pt).dot(l.pt2-pt),0);}
inline bool isparallel(Line l1,Line l2) {return isequal(l1.det(l2),0);}
inline Vector intersection(Line l1,Line l2)
{
	if (isparallel(l1,l2)) return OnTheLine(l2,l1.pt1)?l1.pt1:l1.pt2;
	return l1.pt1+(l1.pt2-l1.pt1)*((l2.pt2-l2.pt1).det(l2.pt1-l1.pt1)/((l2.pt2-l2.pt1).det(l1.pt2-l1.pt1)));
}

Line q[MAXN+48];int head,tail;
Vector a[MAXN+48];
inline void HalfPlaneIntersection()
{
	sort(L+1,L+n+1);
	head=tail=1;q[1]=L[1];
	for (register int i=2;i<=n;i++)
	{
		while (head<tail && !OnTheLeft(L[i],a[tail-1])) tail--;
		while (head<tail && !OnTheLeft(L[i],a[head])) head++;
		q[++tail]=L[i];
		if (head<tail && isparallel(q[tail-1],q[tail]))
		{
			if (OnTheLeft(q[tail-1],q[tail].pt1)) q[tail-1]=q[tail];
			tail--;
		}
		if (head<tail) a[tail-1]=intersection(q[tail-1],q[tail]);
	}
	while (head+1<tail && !OnTheLeft(q[head],a[tail-1])) tail--;
}

vector<int> ans;

int main ()
{
	n=getint();int i;double k,b;
	for (i=1;i<=n;i++)
	{
		scanf("%lf%lf",&k,&b);
		L[i].pt1=Vector(1,k+b);L[i].pt2=Vector(2,k*2+b);L[i].ind=i;L[i].set_ang();
	}
	HalfPlaneIntersection();
	for (i=head;i<=tail;i++) ans.pb(q[i].ind);
	sort(ans.begin(),ans.end());
	for (i=0;i<int(ans.size());i++) printf("%d ",ans[i]);puts("");
	return 0;
}
