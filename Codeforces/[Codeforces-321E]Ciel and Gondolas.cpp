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
const int INF=1e9;
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

int n,k;
int a[5048][5048],sum[5048][5048];
int w[5048][5048];
int dp[5048],tmp[5048];

inline void solve(int hl,int hr,int cl,int cr)
{
	if (hl>hr) return;
	if (cl>cr) return;
	if (hl==0 && hr==0) {tmp[0]=1e9;return;}
	int mid=(hl+hr)>>1;
	tmp[mid]=INF;int minpos;
	for (register int i=cl;i<=min(cr,mid-1);i++)
		if (dp[i]+w[i+1][mid]<tmp[mid])
		{
			tmp[mid]=dp[i]+w[i+1][mid];
			minpos=i;
		}
	solve(hl,mid-1,cl,minpos);
	solve(mid+1,hr,minpos,cr);
}			

int main ()
{
	int i,j;
	n=getint();k=getint();
	for (i=1;i<=n;i++)
	{
		sum[i][0]=0;
		for (j=1;j<=n;j++)
		{
			a[i][j]=getint();
			sum[i][j]=sum[i][j-1]+a[i][j];
		}
		for (j=1;j<=n;j++) sum[i][j]+=sum[i-1][j];
	}
	for (i=1;i<=n;i++)
		for (j=i;j<=n;j++)
			w[i][j]=(sum[j][j]-sum[i-1][j]-sum[j][i-1]+sum[i-1][i-1])/2;
	for (i=1;i<=n;i++) dp[i]=1e9;dp[0]=0;
	for (i=1;i<=k;i++)
	{
		solve(1,n,0,n);
		for (j=0;j<=n;j++) dp[j]=tmp[j];
	}
	printf("%d\n",dp[n]);
	return 0;
}
