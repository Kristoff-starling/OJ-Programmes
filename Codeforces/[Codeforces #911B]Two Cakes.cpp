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
	while (((ch=getchar())<'0' || ch>'9') && ch!='-') {}
	int res,mark;
	if (ch>='0' && ch<='9')
	{
		mark=1;
		res=ch-'0';
	}
	else
	{
		mark=-1;
		res=0;
	}
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res*mark;
}

inline LL getLL()
{
	char ch;
	while (((ch=getchar())<'0' || ch>'9') && ch!='-') {}
	LL res,mark;
	if (ch>='0' && ch<='9')
	{
		mark=1;
		res=ch-'0';
	}
	else
	{
		mark=-1;
		res=0;
	}
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res*mark;
}

int main ()
{
	int i,n,a,b;
	n=getint();a=getint();b=getint();
	for (i=min(a,b);i>=1;i--)
	{
		int num1,num2;
		num1=a/i;num2=b/i;
		if (num1+num2>=n)
		{
			printf("%d\n",i);
			return 0;
		}
	}
	return 0;
}
