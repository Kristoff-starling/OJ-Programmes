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
	int a,b,c;
	a=getint();b=getint();c=getint();
	if (a>b) swap(a,b);
	if (a>c) swap(a,c);
	if (b>c) swap(b,c);
	if (a==1)
	{
		printf("YES\n");
		return 0;
	}
	if (a==2)
	{
		if (b==2)
		{
			printf("YES\n");
			return 0;
		}
		else
		{
			if (b==4 && c==4)
			{
				printf("YES\n");
			}
			else
			{
				printf("NO\n");
			}
			return 0;
		}
	}
	if (a==3)
	{
		if (b==3 && c==3) printf("YES\n"); else printf("NO\n");
		return 0;
	}
	if (a>=4)
	{
		printf("NO\n");
		return 0;
	}
	return 0;
}
