#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <sstream>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <stack>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,m;
int to[8048],sz[8048];
int dp[8048],DP[8048][8048];

inline int mod(int x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

inline void init()
{
	int i,j;
	dp[0]=1;
	for (i=1;i<=n;i++)
	{
		if (i%2==1) {dp[i]=0;continue;}
		for (j=2;j<=i;j+=2) dp[i]=mod(dp[i]+((long long)dp[j-2]*dp[i-j])%MOD);
	}
}

inline int polymul(int ind1,int ind2,int N,int M)
{
	int res[8048],i,j;
	for (i=0;i<=N+M;i++) res[i]=0;
	for (i=0;i<=N;i++)
		for (j=0;j<=M;j++)
			res[i+j]=mod(res[i+j]+((long long)DP[ind1][i]*DP[ind2][j])%MOD);
	for (i=0;i<=N+M;i++) DP[ind1][i]=res[i];
	return N+M;
}

int main ()
{
	int i,j,x,y;n=getint();m=getint();n*=2;
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();
		if (x>y) swap(x,y);
		to[x]=y;
	}
	to[0]=n+1;
	init();
	for (i=n;i>=0;i--)
	{
		if (!to[i])
		{
			sz[i]=1;
			DP[i][0]=0;DP[i][1]=1;
			continue;
		}
		sz[i]=0;DP[i][0]=1;
		for (j=i+1;j<to[i];j++)
		{
			sz[i]=polymul(i,j,sz[i],sz[j]);
			if (to[j]) j=to[j];
		}
		int fres=0;
		for (j=0;j<=sz[i];j+=2) fres=mod(fres+((long long)DP[i][j]*dp[j])%MOD);
		for (j=sz[i]+2;j>=2;j--) DP[i][j]=DP[i][j-2];sz[i]+=2;
		DP[i][1]=0;DP[i][0]=fres;	
	}
	printf("%d\n",DP[0][0]);
	return 0;
}

