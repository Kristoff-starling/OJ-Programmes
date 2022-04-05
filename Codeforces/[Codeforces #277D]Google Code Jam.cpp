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
const long double eps=1e-14;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LB myabs(LB x)
{
	if (x>eps) return x;
	if (x<-eps) return -x;
	return 0;
}
inline bool issmall(LB x,LB y) {return x-y<-eps;}
inline bool islarge(LB x,LB y) {return x-y>eps;}
inline bool isequal(LB x,LB y) {return myabs(x-y)<eps;}

struct Problem
{
	int ssmall,slarge;
	int tsmall,tlarge;
	LB p;
	inline bool operator < (const Problem &x) const
	{
		LB t1=(1-p)*x.p*tlarge+p*(1-x.p)*(tlarge+x.tlarge);
		LB t2=(1-x.p)*p*x.tlarge+x.p*(1-p)*(tlarge+x.tlarge);
		return issmall(t1,t2);
	}
}a[1048];

int n,t;
long double dp[1048][2048],dp2[1048][2048];

int main ()
{
	n=getint();t=getint();int i,j;
	for (i=1;i<=n;i++)
	{
		a[i].ssmall=getint();a[i].slarge=getint();a[i].tsmall=getint();a[i].tlarge=getint();
		double pp;scanf("%lf",&pp);
		a[i].p=pp;
	}
	sort(a+1,a+n+1);
	for (i=0;i<=n;i++)
		for (j=0;j<=t;j++)
			dp[i][j]=-1,dp2[i][j]=INF;
	dp[0][0]=0;dp2[0][0]=0;
	for (i=0;i<=n-1;i++)
		for (j=0;j<=t;j++)
		{
			if (isequal(dp[i][j],-1)) continue;
			if (islarge(dp[i][j],dp[i+1][j]))
			{
				dp[i+1][j]=dp[i][j];
				dp2[i+1][j]=dp2[i][j];
			}
			else if (isequal(dp[i][j],dp[i+1][j]) && issmall(dp2[i][j],dp2[i+1][j]))
				dp2[i+1][j]=dp2[i][j];
			if (t-j>=a[i+1].tsmall)
			{
				if (islarge(dp[i][j]+a[i+1].ssmall,dp[i+1][j+a[i+1].tsmall]))
				{
					dp[i+1][j+a[i+1].tsmall]=dp[i][j]+a[i+1].ssmall;
					dp2[i+1][j+a[i+1].tsmall]=dp2[i][j]+a[i+1].tsmall;
				}
				else if (isequal(dp[i][j]+a[i+1].ssmall,dp[i+1][j+a[i+1].tsmall]))
				{
					LB cmp=dp2[i][j]+a[i+1].tsmall;
					if (issmall(cmp,dp2[i+1][j+a[i+1].tsmall])) dp2[i+1][j+a[i+1].tsmall]=cmp;
				}
			}
			if (t-j>=a[i+1].tsmall+a[i+1].tlarge)
			{
				if (islarge(dp[i][j]+a[i+1].ssmall+a[i+1].slarge*(1-a[i+1].p),dp[i+1][j+a[i+1].tsmall+a[i+1].tlarge]))
				{
					dp[i+1][j+a[i+1].tsmall+a[i+1].tlarge]=dp[i][j]+a[i+1].ssmall+a[i+1].slarge*(1-a[i+1].p);
					dp2[i+1][j+a[i+1].tsmall+a[i+1].tlarge]=(dp2[i][j]+a[i+1].tsmall)*a[i+1].p+(j+a[i+1].tsmall+a[i+1].tlarge)*(1-a[i+1].p);
				}
				else if (isequal(dp[i][j]+a[i+1].ssmall+a[i+1].slarge*(1-a[i+1].p),dp[i+1][j+a[i+1].tsmall+a[i+1].tlarge]))
				{
					LB cmp=(dp2[i][j]+a[i+1].tsmall)*a[i+1].p+(j+a[i+1].tsmall+a[i+1].tlarge)*(1-a[i+1].p);
					if (issmall(cmp,dp2[i+1][j+a[i+1].tsmall+a[i+1].tlarge])) dp2[i+1][j+a[i+1].tsmall+a[i+1].tlarge]=cmp;
				}
			}
		}
	LB maxscore=-1,mintime=INF;
	for (i=0;i<=n;i++)
		for (j=0;j<=t;j++)
			if (islarge(dp[i][j],maxscore))
			{
				maxscore=dp[i][j];
				mintime=dp2[i][j];
			}
			else if (isequal(dp[i][j],maxscore) && issmall(dp2[i][j],mintime))
				mintime=dp2[i][j];
	double x=maxscore,y=mintime;
	printf("%.10lf %.10lf\n",x,y);
	return 0;
}
/*
3 40
10 20 15 4 0.5
5 100 21 1 0.99
1 4 1 1 0.25
*/
