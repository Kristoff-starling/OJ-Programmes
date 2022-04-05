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

const LL MOD=1e9+7;
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

int n,k;
int pre[48];
int p[48];
double dp[101][34448];

int main ()
{
	int i,Mask,cur,x;n=getint();k=getint();
	for (i=1;i<=k;i++)
	{
		p[i]=getint();
		while (scanf("%d",&x) && x) pre[i]|=(1<<(x-1));
	}
	for (i=0;i<=n;i++)
		for (Mask=0;Mask<=(1<<k)-1;Mask++)
			dp[i][Mask]=0;
	for (i=n-1;i>=0;i--)
		for (Mask=0;Mask<=(1<<k)-1;Mask++)
		{
			for (cur=1;cur<=k;cur++)
				if ((Mask|pre[cur])==Mask)
					dp[i][Mask]+=max(dp[i+1][Mask],dp[i+1][Mask|(1<<(cur-1))]+p[cur])*1.0/k;
				else
					dp[i][Mask]+=dp[i+1][Mask]*1.0/k;
		}
	printf("%.6lf\n",dp[0][0]);
	return 0;
}
