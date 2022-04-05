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

int dp[1048][1048];
int n,m;

int main ()
{
	int i,j,k,l,r,mid1,mid2;
	for (i=0;i<=1000;i++)
		for (j=0;j<=1000;j++)
			dp[i][j]=INF;
	for (i=0;i<=1000;i++) dp[0][i]=0;
	for (i=1;i<=1000;i++)
		for (j=1;j<=20;j++)
			for (k=1;k<=i;k++)
				dp[i][j]=min(dp[i][j],max(dp[k-1][j-1],dp[i-k][j])+1);
	while (scanf("%d%d",&m,&n) && n && m) printf("%d\n",dp[n][min(m,20)]);
	return 0;
}
