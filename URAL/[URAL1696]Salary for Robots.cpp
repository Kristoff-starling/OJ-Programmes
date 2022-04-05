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

const int MOD=123456789;
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

int dp[2][248][248];
int sum1[248][248],sum2[248][248];
int n,k,p;

inline int mod(int x) {while (x>=p) x-=p;while (x<0) x+=p;return x;}
inline int doit(int x) {if (x==0) x+=p;return x;}

int main ()
{
	int i,j,m;n=getint();k=getint();p=getint();
	int cur=0,nxt=1;
	for (i=1;i<=k;i++) dp[0][k+1][i]=1;
	for (i=1;i<=n-1;i++)
	{
		memset(sum1,0,sizeof(sum1));memset(sum2,0,sizeof(sum2));
		for (j=2;j<=k+1;j++)
			for (m=1;m<j;m++)
			{
				sum1[m+1][m]=mod(sum1[m+1][m]+dp[cur][j][m]);
				sum1[min(j+1,k+1)][m]=mod(sum1[min(j+1,k+1)][m]-dp[cur][j][m]);
				sum2[j][1]=mod(sum2[j][1]+dp[cur][j][m]);
				sum2[j][m+1]=mod(sum2[j][m+1]-dp[cur][j][m]);
			}
		for (j=3;j<=k+1;j++)
			for (m=1;m<j;m++)
				sum1[j][m]=mod(sum1[j][m]+sum1[j-1][m]);
		for (j=2;j<=k+1;j++)
			for (m=2;m<j;m++)
				sum2[j][m]=mod(sum2[j][m]+sum2[j][m-1]);
		for (j=2;j<=k+1;j++)
			for (m=1;m<j;m++)
				dp[nxt][j][m]=mod(sum1[j][m]+sum2[j][m]);
		swap(cur,nxt);
	}
	int ans=1;
	for (j=2;j<=k+1;j++)
		for (m=1;m<j;m++)
			ans=mod(ans+dp[cur][j][m]);
	printf("%d\n",doit(ans));
	return 0;
}
