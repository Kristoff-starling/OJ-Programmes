#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <cctype>
#include <bitset>
#include <functional>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-12;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
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
inline bool islarger(double x,double y) {return x-y>eps;}
inline bool issmaller(double x,double y) {return x-y<-eps;}
inline bool isequal(double x,double y) {return myabs(x-y)<eps;}

double st,w;int n;
struct node
{
	double pos,dist,speed;int ind;
	inline bool operator < (const node &x) const {return issmaller(pos,x.pos);}
}a[2048];

double dp[2048][2048][2];bool inq[2048][2048][2];
int pre[2048][2048][2];
double pos[2048];
queue<int> q;

inline double calc_time(double p1,double p2) {return myabs(p1-p2)/w;}

inline void update(int left,int right,int dir,int predir,double val)
{
	if (!dir && islarger(val,(a[left].dist-1)/a[left].speed)) return;
	if (dir && islarger(val,(a[right].dist-1)/a[right].speed)) return;
	if (val<dp[left][right][dir])
	{
		dp[left][right][dir]=val;
		pre[left][right][dir]=predir;
		if (!inq[left][right][dir])
		{
			inq[left][right][dir]=true;
			q.push(left);q.push(right);q.push(dir);
		}
	}
}

inline void getans(int left,int right,int dir)
{
	if (!dir)
	{
		if (left!=right) getans(left+1,right,pre[left][right][dir]);
		printf("%d\n",a[left].ind);
	}
	else
	{
		if (left!=right) getans(left,right-1,pre[left][right][dir]);
		printf("%d\n",a[right].ind);
	}
}

int main ()
{
	int i,left,right,dir;double cp;
	scanf("%lf%lf%d",&st,&w,&n);w*=360;
	for (i=n+1;i<=n*2;i++) scanf("%lf%lf%lf",&a[i].pos,&a[i].dist,&a[i].speed),a[i].ind=i-n,a[i].speed/=60;
	sort(a+n+1,a+n*2+1);
	for (i=1;i<=n;i++) a[i]=a[i+n],a[i].pos-=360;
	for (i=n*2+1;i<=n*3;i++) a[i]=a[i-n],a[i].pos+=360;
	for (i=1;i<=n*3;i++) pos[i]=a[i].pos;
	int sp=lower_bound(pos+1,pos+n*3+1,st)-pos;
	for (left=1;left<=n*3;left++)
		for (right=left;right<=n*3;right++)
			for (dir=0;dir<=1;dir++)
				dp[left][right][dir]=INF;
	if (!islarger(calc_time(st,pos[sp]),(a[sp].dist-1)/a[sp].speed))
	{
		dp[sp][sp][0]=dp[sp][sp][1]=calc_time(st,pos[sp]);
		q.push(sp);q.push(sp);q.push(0);inq[sp][sp][0]=true;
		q.push(sp);q.push(sp);q.push(1);inq[sp][sp][1]=true;
	}
	if (st!=pos[sp] && !islarger(calc_time(pos[sp-1],st),(a[sp-1].dist-1)/a[sp-1].speed))
	{
		dp[sp-1][sp-1][0]=dp[sp-1][sp-1][1]=calc_time(pos[sp-1],st);
		q.push(sp-1);q.push(sp-1);q.push(0);inq[sp-1][sp-1][0]=true;
		q.push(sp-1);q.push(sp-1);q.push(1);inq[sp-1][sp-1][1]=true;
	}
	while (!q.empty())
	{
		left=q.front();q.pop();right=q.front();q.pop();dir=q.front();q.pop();
		inq[left][right][dir]=false;
		if (!dir) cp=pos[left]; else cp=pos[right];
		if (left!=1 && !islarger(myabs(pos[left-1]-cp),180))
			update(left-1,right,0,dir,dp[left][right][dir]+calc_time(pos[left-1],cp));
		if (right!=n*3 && !islarger(myabs(pos[right+1]-cp),180))
			update(left,right+1,1,dir,dp[left][right][dir]+calc_time(pos[right+1],cp));
	}
	double mintime=INF;int ansl,ansr,ansdir;
	for (i=1;i<=n*2+1;i++)
	{
		if (issmaller(dp[i][i+n-1][0],mintime))
		{
			mintime=dp[i][i+n-1][0];
			ansl=i;ansr=i+n-1;ansdir=0;
		}
		if (issmaller(dp[i][i+n-1][1],mintime))
		{
			mintime=dp[i][i+n-1][1];
			ansl=i;ansr=i+n-1;ansdir=1;
		}
	}
	if (mintime>=INF) {puts("Impossible");return 0;}
	printf("%.3lf\n",mintime);
	getans(ansl,ansr,ansdir);
	return 0;
}
