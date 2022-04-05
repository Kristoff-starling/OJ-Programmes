#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <functional>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp maek_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int MOD=998244353;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,k;
char a[200048];
int b[148];
int dp[200048][105];
int f[200048][105],g[200048][105];
int sum_[200048],sumx[200048];
int okx[200048],ok_[200048];

inline bool solve()
{
	int i,j;
	memset(dp,0,sizeof(dp));
	for (i=1;i<=n;i++)
		if (sumx[i]==0) dp[i][0]=1; else dp[i][0]=0;
	dp[0][0]=1;
	for (i=1;i<=n;i++)
		for (j=1;j<=k;j++)
		{
			if (a[i]!='X' && dp[i-1][j]) {dp[i][j]=1;continue;}
			if (i-b[j]>=1 && sum_[i]-sum_[i-b[j]]==0 && dp[i-b[j]-1][j-1] && a[i-b[j]]!='X') dp[i][j]=1;
		}
}

int main ()
{
	int i,j;
	a[1]='_';
	scanf("%s",a+2);n=strlen(a+1);
	a[++n]='_';
	sum_[1]=1;sumx[1]=0;for (i=2;i<=n;i++) sum_[i]=sum_[i-1]+(a[i]=='_'),sumx[i]=sumx[i-1]+(a[i]=='X');
	k=getint();for (i=1;i<=k;i++) b[i]=getint();
	solve();
	for (i=0;i<=n;i++)
		for (j=0;j<=k;j++)
			f[i][j]=dp[i][j];
	reverse(a+1,a+n+1);reverse(b+1,b+k+1);
	sum_[1]=1;sumx[1]=0;for (i=2;i<=n;i++) sum_[i]=sum_[i-1]+(a[i]=='_'),sumx[i]=sumx[i-1]+(a[i]=='X');
	solve();
	for (i=0;i<=n;i++)
		for (j=0;j<=k;j++)
			g[n-i+1][k-j+1]=dp[i][j];
	reverse(a+1,a+n+1);reverse(b+1,b+k+1);
	sum_[1]=1;sumx[1]=0;for (i=2;i<=n;i++) sum_[i]=sum_[i-1]+(a[i]=='_'),sumx[i]=sumx[i-1]+(a[i]=='X');
	for (i=2;i<=n-1;i++)
	{
		if (a[i]!='.') continue;
		for (j=1;j<=k-1;j++)
			if (f[i-1][j] && g[i+1][j+1]) ok_[i]++;
		if (g[i+1][1] && sumx[i]==0) ok_[i]++;
		if (f[i-1][k] && sumx[n]-sumx[i]==0) ok_[i]++;
	}
	for (j=2;j<=k-1;j++)
		for (i=2;i<=n-b[j];i++)
			if (f[i-2][j-1] && g[i+b[j]+1][j+1] && sum_[i+b[j]-1]-sum_[i-1]==0 && a[i-1]!='X' && a[i+b[j]]!='X') okx[i]++,okx[i+b[j]]--;
	for (i=2;i<=n-b[1]+1;i++)
		if (sumx[i-1]==0 && g[i+b[1]+1][2] && sum_[i+b[1]-1]-sum_[i-1]==0 && a[i+b[1]]!='X') okx[i]++,okx[i+b[1]]--;
	for (i=2;i<=n-b[k]+1;i++)
		if (sumx[n]-sumx[i+b[k]-1]==0 && f[i-2][k-1] && sum_[i+b[k]-1]-sum_[i-1]==0 && a[i-1]!='X') okx[i]++,okx[i+b[k]]--;
	for (i=2;i<=n;i++) okx[i]+=okx[i-1];
	for (i=2;i<=n-1;i++)
	{
		if (a[i]=='X' || a[i]=='_') {printf("%c",a[i]);continue;}
		if (ok_[i] && okx[i]) printf("?");
		if (!ok_[i] && okx[i]) printf("X");
		if (ok_[i] && !okx[i]) printf("_");
	}
	return 0;
}
