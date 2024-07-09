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

int pre[1000048];
inline int find_anc(int x)
{
	if (pre[x]!=x) pre[x]=find_anc(pre[x]);
	return pre[x];
}
inline void update(int x,int y)
{
	x=find_anc(x);y=find_anc(y);
	pre[x]=y;
}

int n;
int a[1000048];
int ans=0;

int main ()
{
	n=getint();
	int i;
	for (i=1;i<=n;i++) a[i]=getint();
	int cur=n+1;
	ans=0;
	for (i=n;i>=1;i--)
	{
		if (i<cur) ans++;
		int to=i-a[i];
		to=max(to,0);
		cur=min(cur,to);
		if (cur==0) break;
	}
	printf("%d\n",ans);
	return 0;
}
