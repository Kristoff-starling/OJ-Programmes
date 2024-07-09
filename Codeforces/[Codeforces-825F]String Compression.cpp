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
#include <ctime>
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

const int MOD=10007;
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

char s[8048];
int fail[8048][8048];
int dp[8048];
int len;

inline int getlen(int x)
{
	int res=0;
	while (x) res++,x/=10;
	return res;
}

inline int calc(int left,int right)
{
	int l=right-left+1;
	if (fail[left][right]*2<l || l%(l-fail[left][right])!=0) return l+1;
	return (l-fail[left][right])+getlen(l/(l-fail[left][right]));
}

int main ()
{
	scanf("%s",s+1);len=strlen(s+1);int i,j,k;
	for (i=1;i<=len;i++)
	{
		fail[i][i]=0;k=0;
		for (j=i+1;j<=len;j++)
			do
			{
				if (s[i+k]==s[j]) {fail[i][j]=++k;break;}
				if (!k) {fail[i][j]=k;break;}
				k=fail[i][i+k-1];
			}
			while (true);
	}
	dp[0]=0;for (i=1;i<=len;i++) dp[i]=INF;
	for (i=1;i<=len;i++)
		for (j=0;j<=i-1;j++)
			dp[i]=min(dp[i],dp[j]+calc(j+1,i));
	printf("%d\n",dp[len]);
	return 0;
}
