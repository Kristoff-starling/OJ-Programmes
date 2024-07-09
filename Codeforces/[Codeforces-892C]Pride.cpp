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

inline int gcd(int x,int y)
{
	return y==0?x:gcd(y,x%y);
}

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

int n;
int a[2048];
int g[2048][2048];

int main ()
{
	int i,j;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++) g[i][i]=a[i];
	int ans=-1;
	for (i=1;i<=n;i++) if (a[i]==1)
	{
		ans=1;
		break;
	}
	if (ans==1)
	{
		int cnt=0;
		for (i=1;i<=n;i++)
			cnt+=(a[i]==1);
		cout<<n-cnt<<endl;
		return 0;
	}
	if (ans==-1)
	{
		for (int u=2;u<=n;u++)
		{
			for (i=1;i<=n-u+1;i++)
			{
				g[i][i+u-1]=gcd(g[i][i+u-2],a[i+u-1]);
				if (g[i][i+u-1]==1)
				{
					ans=u;
					break;
				}
			 } 
			if (ans!=-1) break;
		}
	}
	if (ans==-1) printf("%d\n",ans); 
	else 
	{
		cout<<ans-1+n-1<<endl;
	}
	return 0;
}
