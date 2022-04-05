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
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline double myabs(double x)
{
	if (x>eps) return x;
	if (x<-eps) return -x;
	return 0;
}

inline double add(double x,double y)
{
	if (myabs(x+y)<eps*(myabs(x)+myabs(y))) return 0;
	return x+y;
}

struct Vector
{
	double x,y;
	Vector () {}
	inline Vector (double a,double b) {x=a;y=b;}
	inline Vector operator + (Vector other) {return Vector(add(x,other.x),add(y,other.y));}
	inline Vector operator - (Vector other) {return Vector(add(x,-other.x),add(y,-other.y));}
	inline Vector operator * (double t) {return Vector(x*t,y*t);}
	inline double dot(Vector other) {return add(x*other.x,y*other.y);}
	inline double det(Vector other) {return add(x*other.y,-y*other.x);}
}st[48],ed[48];

int n;
bool ga[48][48];

inline bool on_seg(Vector st,Vector ed,Vector pt) {if (myabs((st-pt).det(ed-pt))<eps && (st-pt).dot(ed-pt)<eps) return true; else return false;}
inline Vector intersection(Vector st1,Vector ed1,Vector st2,Vector ed2) {return st1+(ed1-st1)*((ed2-st2).det(st2-st1)/(ed2-st2).det(ed1-st1));}
inline bool isintersect(Vector st1,Vector ed1,Vector st2,Vector ed2)
{
	if (myabs((ed1-st1).det(ed2-st2))<eps)
	{
		if (on_seg(st1,ed1,st2) || on_seg(st1,ed1,ed2) || on_seg(st2,ed2,st1) || on_seg(st2,ed2,ed1))
			return true;
		else return false;
	}
	Vector pt=intersection(st1,ed1,st2,ed2);
	if (on_seg(st1,ed1,pt) && on_seg(st2,ed2,pt)) return true; else return false;
}

int main ()
{
	int i,j,k,i1,i2;
	while (scanf("%d",&n) && n)
	{
		for (i=1;i<=n;i++) st[i].x=getint(),st[i].y=getint(),ed[i].x=getint(),ed[i].y=getint();
		memset(ga,false,sizeof(ga));
		for (i=1;i<=n-1;i++)
			for (j=i+1;j<=n;j++)
				if (isintersect(st[i],ed[i],st[j],ed[j])) ga[i][j]=true,ga[j][i]=true;
		for (k=1;k<=n;k++)
			for (i=1;i<=n;i++)
				for (j=1;j<=n;j++)
					if (k!=i && k!=j && i!=j && ga[i][k] && ga[k][j]) ga[i][j]=true;
		while (scanf("%d%d",&i1,&i2) && i1 && i2) printf((ga[i1][i2] || i1==i2)?"CONNECTED\n":"NOT CONNECTED\n");
	}
	return 0;
}
