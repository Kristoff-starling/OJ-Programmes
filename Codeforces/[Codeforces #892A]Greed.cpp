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

int n;
LL a[100048];
LL b[100048];

int main ()
{
	int i;
	n=getint();
	for (i=1;i<=n;i++) a[i]=getLL();
	LL sum=0;
	for (i=1;i<=n;i++) sum+=a[i];
	for (i=1;i<=n;i++) b[i]=getLL();
	sort(b+1,b+n+1);
	LL mm=b[n]+b[n-1];
	if (mm>=sum) printf("YES\n"); else printf("NO\n");
	return 0;
}
