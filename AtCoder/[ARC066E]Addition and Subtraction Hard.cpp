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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return res;
}

LL dp[100048][5];

struct node
{
	int sign;
	int num;
}a[100048];

int n;

int main ()
{
	int i,j;n=getint();string s;
	for (i=1;i<=n;i++)
	{
		if (i==1) {a[i].sign=1,a[i].num=getint();continue;}
		cin>>s;a[i].sign=(s[0]=='+'?1:-1);
		a[i].num=getint();
	}
	for (i=1;i<=n;i++)
		for (j=0;j<=4;j++)
			dp[i][j]=-LINF;
	dp[1][0]=a[1].num;
	for (i=2;i<=n;i++)
		for (j=0;j<=4;j++)
		{
			//no sign
			dp[i][j]=max(dp[i][j],dp[i-1][j]+a[i].num*a[i].sign*(j%2?-1:1));
			//)
			if (j!=4) dp[i][j]=max(dp[i][j],dp[i-1][j+1]+a[i].num*a[i].sign*((j+1)%2?-1:1));
			//(
			if (j && a[i].sign==-1) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+a[i].num*(j%2?-1:1));
		}
	printf("%lld\n",dp[n][0]);
	return 0;
}
