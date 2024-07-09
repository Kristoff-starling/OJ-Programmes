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
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;

struct POINT
{
	double x,y;
	inline void input()
	{
		x=getint();y=getint();
	}
}a[40048];

struct LINE
{
	double A,B,C;
};

inline double myabs(double x)
{
	return x>=double(0)?x:-x;
}

inline LINE construct_line(POINT x,POINT y)
{
	LINE res;
	res.A=y.y-x.y;res.B=x.x-y.x;res.C=x.y*y.x-x.x*y.y;
	return res;
}

inline double calc_dist(POINT x,POINT y)
{
	return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}

inline POINT find_intersect(LINE l1,LINE l2)
{
	POINT res;
	res.x=(l2.C*l1.B-l1.C*l2.B)/(l1.A*l2.B-l2.A*l1.B);
	res.y=(l1.C*l2.A-l2.C*l1.A)/(l1.A*l2.B-l2.A*l1.B);
	return res;
}

inline POINT OnTheLine(LINE l,POINT pt)
{
	if (l.B==0) return POINT{-l.C/l.A,pt.y};
	if (l.A==0) return POINT{pt.x,-l.C/l.B};
	double k=double(-1)/(-l.A/l.B);double b=pt.y-k*pt.x;
	LINE tmp;tmp.A=-k;tmp.B=1;tmp.C=-b;
	return find_intersect(l,tmp);
}

inline int inc(int x)
{
	return x%n+1;
}

inline int dec(int x)
{
	x--;
	return !x?n:x;
}

void change_direction()
{
	reverse(a+1,a+n+1);
}

inline bool sameside(POINT pt1,POINT pt2,POINT pt3)
{
	if (pt1.x==pt2.x && pt1.x==pt3.x)
	{
		if ((pt1.y>=pt3.y && pt2.y>=pt3.y) || (pt1.y<=pt3.y && pt2.y<=pt3.y))
			return true;
		else
			return false;
	}
	else
	{
		if ((pt1.x>=pt3.x && pt2.x>=pt3.x) || (pt1.x<=pt3.x && pt2.x<=pt3.x))
			return true;
		else
			return false;
	}
}

inline bool islowpt(LINE l,POINT starter,int cur)
{
	int cmp=inc(cur);
	POINT tmp1=OnTheLine(l,a[cur]),tmp2=OnTheLine(l,a[cmp]);
	if (!sameside(tmp1,tmp2,starter)) return true;
	double d1=calc_dist(starter,tmp1),d2=calc_dist(starter,tmp2);
	return d1>d2;
}

inline double calc_area(int ind1,int ind2,int ind3)
{
	double x1=a[ind2].x-a[ind1].x,y1=a[ind2].y-a[ind1].y;
	double x2=a[ind3].x-a[ind1].x,y2=a[ind3].y-a[ind1].y;
	double res=myabs(x1*y2-x2*y1);
	return res/2; 
}

double ans=LINF;

void solve()
{
	double lastarea,curarea;
	int lowpt,lastlowpt,tmppt,i;
	lastlowpt=-1;
	for (i=1;i<=n;i++)
	{
		LINE cur=construct_line(a[i],a[inc(i)]);
		if (lastlowpt==-1) lowpt=inc(i); else lowpt=lastlowpt;
		while (!islowpt(cur,a[i],lowpt)) lowpt=inc(lowpt);
		double len1=calc_dist(OnTheLine(cur,a[lowpt]),a[lowpt]),len2=calc_dist(OnTheLine(cur,a[lowpt]),a[i]);
		if (lastlowpt==-1)
		{
			curarea=0;
			for (tmppt=inc(i);tmppt!=lowpt;tmppt=inc(tmppt))
				curarea+=calc_area(i,tmppt,inc(tmppt));
			ans=min(ans,len1*len2/2-curarea);
		}
		else
		{
			curarea=lastarea;
			curarea-=calc_area(i-1,i,lastlowpt);
			for (tmppt=lastlowpt;tmppt!=lowpt;tmppt=inc(tmppt))
				curarea+=calc_area(i,tmppt,inc(tmppt));
			ans=min(ans,len1*len2/2-curarea);
		}
		lastlowpt=lowpt;lastarea=curarea;
	}
}

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++) a[i].input();
	solve();
	change_direction();
	solve();
	printf("%.6lf\n",ans);
	return 0;
}