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

const int MAXN=2e5;

int n;
struct Vector
{
	int x,y,ind;
	Vector () {}
	inline bool operator < (const Vector &other) const {if (x!=other.x) return x<other.x; else return ind<other.ind;}
	inline Vector (int xx,int yy) {x=xx;y=yy;}
	inline void input() {x=getint();y=getint();}
	inline double calc_k() {if (x==0) return y>0?INF:-INF;return double(y)*1.0/x;}
	inline Vector operator + (Vector other) {return Vector(x+other.x,y+other.y);}
	inline Vector operator - (Vector other) {return Vector(x-other.x,y-other.y);}
}a[MAXN+48];

Vector sta[MAXN+48];int stot;

inline double myabs(double x) {if (x>eps) return x;if (x<-eps) return -x;return 0;}
inline bool islarger(double x,double y) {return x-y>eps;}
inline bool isequal(double x,double y) {return myabs(x-y)<eps;}

inline void construct_convex()
{
	int i;
	sort(a+1,a+n+1);
	stot=1;sta[1]=a[1];
	for (i=2;i<=n;i++)
	{
		while (stot>1)
		{
			double k1=(a[i]-sta[stot]).calc_k(),k2=(sta[stot]-sta[stot-1]).calc_k();
			if (islarger(k1,k2) || (isequal(k1,k2) && a[i].ind<sta[stot].ind)) stot--; else break;
		}
		sta[++stot]=a[i];
	}
}

int main ()
{
	int i,ca;ca=getint();
	while (ca--)
	{
		n=getint();
		for (i=1;i<=n;i++) a[i].input(),a[i].ind=i;
		construct_convex();
		for (i=1;i<=stot;i++) {printf("%d",sta[i].ind);if (i!=stot) printf(" ");}
		puts("");
	}
	return 0;
}
