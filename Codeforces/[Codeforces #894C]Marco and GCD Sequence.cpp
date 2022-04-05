#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#include <deque>
#include <sstream>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

inline int gcd(int x,int y)
{
	return y==0?x:gcd(y,x%y);
}

int n;
int a[1048];

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	int g=a[1];for (i=2;i<=n;i++) g=gcd(g,a[i]);
	if (g!=a[1])
	{
		printf("-1\n");
	}
	else
	{
		printf("%d\n",n*2);
		for (i=1;i<=n;i++) printf("%d %d ",a[i],a[1]);
	}
	return 0;
}
