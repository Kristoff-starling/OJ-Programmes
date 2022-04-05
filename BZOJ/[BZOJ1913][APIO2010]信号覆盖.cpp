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

const LL MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-15;
const long double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
Pair a[2048];
struct node
{
	int x,y;
	long double ang;
}b[4048];int tot;
int cmpx,cmpy;

inline int calc_region(int x,int y,int xx,int yy)
{
	int dx=xx-x,dy=yy-y;
	if (dx>0 && dy>=0) return 1;
	if (dx<=0 && dy>0) return 2;
	if (dx<0 && dy<=0) return 3;
	if (dx>=0 && dy<0) return 4;
}	

inline long double calc_angle(int x,int y,int xx,int yy)
{
	int pt=calc_region(x,y,xx,yy);
	if (x==xx) return (pt==2?90:270);
	if (y==yy) return (pt==1?0:180);
	long double k=(long double)(y-yy)/(x-xx);
	long double res=atan(k)/pi*180;
	if (pt==1) return res;
	if (pt==2) return res+180;
	if (pt==3) return res+180;
	if (pt==4) return res+360;
}

inline bool cmp(node x,node y)
{
	return y.ang-x.ang>eps;
}

inline long double judge(int ind1,int ind2)
{
	return (b[ind1].ang-b[ind2].ang>eps?b[ind1].ang-b[ind2].ang:b[ind1].ang-b[ind2].ang+360);
}

inline LL C(int x,int y)
{
	if (x<y) return 0;
	LL res=1;int i;
	for (i=x;i>=x-y+1;i--) res*=i;
	for (i=y;i;i--) res/=i;
	return res;
}

int main ()
{
	int i,j;n=getint();
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint();
	long double ans=0;
	for (i=1;i<=n;i++)
	{
		cmpx=a[i].x;cmpy=a[i].y;tot=0;
		for (j=1;j<=n;j++)
		{
			if (i==j) continue;
			b[++tot]=node{a[j].x,a[j].y,calc_angle(cmpx,cmpy,a[j].x,a[j].y)};
		}
		sort(b+1,b+tot+1,cmp);
		for (j=tot+1;j<=tot*2;j++) b[j]=b[j-tot];
		int pt=1;LL cnt=0;
		for (j=1;j<=tot;j++)
		{
			pt=max(pt,j+1);
			while (judge(pt,j)<180 && pt<j+tot) pt++;pt--;
			cnt+=C(pt-j,2);
		}
		cnt=C(n-1,3)-cnt;ans+=cnt;
	}
	ans=ans+(C(n,4)-ans)*2;ans/=C(n,3);ans+=3;
	printf("%.6Lf\n",ans);
	return 0;
}
