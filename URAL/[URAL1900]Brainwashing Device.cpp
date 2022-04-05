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
#include <cassert>
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
int ga[548][548];
int dp[548][548],pre[548][548];
int sum[548][548];

inline void print(int curpos,int cnt)
{
	if (cnt!=1) print(pre[curpos][cnt],cnt-1);
	printf("%d ",curpos);
}

int main ()
{
	int i,j,m;
	n=getint();k=getint();
	for (i=1;i<=n;i++)
		for (j=i+1;j<=n;j++)
			ga[i][j]=getint();
	for (i=1;i<=n;i++)
	{
		sum[i][n]=ga[i][n];
		for (j=n-1;j>=1;j--)
			sum[i][j]=sum[i][j+1]+ga[i][j];
	}
	for (i=2;i<=n;i++)
		for (j=1;j<=n;j++)
			sum[i][j]+=sum[i-1][j];
	for (i=0;i<=n;i++)
		for (j=0;j<=k;j++)
			dp[i][j]=-INF;
	dp[0][0]=0;
	for (i=1;i<=n-1;i++)
		for (j=1;j<=k;j++)
			for (m=0;m<=i-1;m++)
				if (dp[m][j-1]+sum[i][i+1]-sum[m][i+1]>dp[i][j])
				{
					dp[i][j]=dp[m][j-1]+sum[i][i+1]-sum[m][i+1];
					pre[i][j]=m;
				}
	int ans=-1,last;
	for (i=1;i<=n-1;i++)
		if (dp[i][k]>ans) ans=dp[i][k],last=i;
	printf("%d\n",ans);
	print(last,k);
	puts("");return 0;
}
