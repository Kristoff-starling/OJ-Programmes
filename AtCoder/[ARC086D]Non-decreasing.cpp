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

int n;
int a[148];

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;++i) scanf("%d",&a[i]);
	int pos_maxn=-INF,neg_minn=INF,pos,neg;
	for (i=1;i<=n;i++)
	{
		if (a[i]>=0 && a[i]>pos_maxn)
		{
			pos_maxn=a[i];
			pos=i;
		}
		if (a[i]<0 && a[i]<neg_minn)
		{
			neg_minn=a[i];
			neg=i;
		}	
	}
	if (pos_maxn==-INF)
	{
		printf("%d\n",n-1);
		for (i=n;i>=2;i--) printf("%d %d\n",i,i-1);
		return 0;
	}
	if (neg_minn==INF)
	{
		printf("%d\n",n-1);
		for (i=1;i<=n-1;i++) printf("%d %d\n",i,i+1);
		return 0;
	}
	printf("%d\n",n*2-2);
	if (pos_maxn>-neg_minn)
	{
		for (i=1;i<=n;i++)
			if (i!=pos) printf("%d %d\n",pos,i);
		for (i=1;i<=n-1;i++) printf("%d %d\n",i,i+1);
	}
	else
	{
		for (i=1;i<=n;i++)
			if (i!=neg) printf("%d %d\n",neg,i);
		for (i=n;i>=2;i--) printf("%d %d\n",i,i-1);
	}
	return 0;
}
