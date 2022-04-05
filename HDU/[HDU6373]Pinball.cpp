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

double A,B,X,Y;
double T,vx,vy,dist;
double sd;
const double g=9.8;

inline double myabs(double x) {if (x>eps) return x;if (x<eps) return -x;return 0;}

int main ()
{
	int ca;ca=getint();
	while (ca--)
	{
		A=getint();B=getint();swap(A,B);X=getint();Y=getint();X=-X;
		dist=0;
		T=A/B;int cnt=0;
		vx=0;
		sd=Y-T*X;vy=sqrt(g*2*sd);
		do
		{
			cnt++;
			double v=sqrt(vx*vx+vy*vy);
			double thi=(vx==0?pi/2:atan(vy/vx))-atan(T);
			thi=thi-atan(T);
			vx=v*cos(thi);vy=v*sin(thi);
			double ti=(vx*T+vy)*2/g;
			if (dist+ti*vx>X) break;
			dist+=ti*vx; 
			ti-=vy*2/g;
			vy+=g*ti;
		}
		while (true);
		printf("%d\n",cnt);
	}
	return 0;
}
