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
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
int A[30],B[30],C[30];
double dp[48][48];
double p[48];
double DP[1048],sum[1048];

inline double myabs(double x)
{
	if (x>eps) return x;
	if (x<-eps) return -x;
	return 0;
}
inline bool isequal(double x,double y) {return myabs(x-y)<eps;}

inline double solve(int Mask)
{
	if (DP[Mask]!=-1) return DP[Mask];
	DP[Mask]=0;int i;
	for (i=0;i<=9;i++)
		if (!(Mask&(1<<i))) DP[Mask]=DP[Mask]+p[i]*solve(Mask|(1<<i));
	DP[Mask]++;
	DP[Mask]/=(1-sum[Mask]);
	return DP[Mask];
}

int main ()
{
	n=getint();int i,j,k,Mask;
	for (i=1;i<=n;i++) A[i]=getint();
	for (i=1;i<=n;i++) B[i]=getint();
	for (i=1;i<=n;i++) C[i]=getint();
	memset(dp,0,sizeof(dp));
	for (k=0;k<=9;k++)
	{
		int val=(A[1]*k*k+B[1]*k+C[1])%11;
		dp[1][val]+=0.1;
	}
	for (i=1;i<=n-1;i++)
		for (j=0;j<=10;j++)
			if (dp[i][j])
				for (k=0;k<=9;k++)
				{
					int val=((A[i+1]*k*k+B[i+1]*k+C[i+1])*j)%11;
					dp[i+1][val]+=dp[i][j]/10;
				}
	for (i=0;i<=9;i++) p[i]=dp[n][i];p[0]+=dp[n][10];
	for (i=0;i<=9;i++)
		if (isequal(p[i],0)) {puts("-1");return 0;}
	for (Mask=0;Mask<=(1<<10)-1;Mask++)
	{
		sum[Mask]=0;
		for (i=0;i<=9;i++)
			if (Mask&(1<<i)) sum[Mask]+=p[i];
	}
	for (Mask=0;Mask<=(1<<10)-1;Mask++) DP[Mask]=-1;
	DP[(1<<10)-1]=0;
	printf("%.10lf\n",solve(0));
	return 0;
}
