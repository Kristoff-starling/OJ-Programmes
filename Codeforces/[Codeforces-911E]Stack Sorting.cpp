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

set<int> s,ss;
set<int>::iterator iter;
int a[200048],n,k;
int minn[200048];
bool visited[200048];

int main ()
{
	int i;
	n=getint();k=getint();
	for (i=1;i<=k;i++) a[i]=getint(),visited[a[i]]=true;
	s.insert(a[1]);
	minn[k]=a[k];
	for (i=k-1;i>=1;i--) minn[i]=min(minn[i+1],a[i]);
	bool f=true;
	for (i=2;i<=k-1;i++)
	{
		iter=s.lower_bound(a[i]);
		if (iter!=s.begin())
		{
			int num=*(--iter);
			if (num>minn[i+1] && a[i]>minn[i+1])
			{
				f=false;
				break;
			}
		}
		s.insert(a[i]);
	}
	if (!f)
	{
		printf("-1\n");
		return 0;
	}
	int xx=-1,yy=-1;
	s.clear();
	s.insert(a[1]);
	for (i=2;i<=k;i++)
	{
		iter=s.lower_bound(a[i]);
		if (iter!=s.begin())
		{
			int num=*(--iter);
			if (num>xx)
			{
				xx=num;
				yy=a[i];
			}
		}
		s.insert(a[i]);
	}
	for (i=1;i<=n;i++) if (!visited[i]) ss.insert(i);
	if (*(ss.begin())<xx)
	{
		printf("-1\n");
		return 0;
	}
	for (i=k+1;i<=n;i++)
	{
		if (*(ss.begin())<xx)
		{
			printf("-1\n");
			return 0;
		}
		int curmin=*(ss.begin());
		iter=s.lower_bound(curmin);
		int lim;
		if (iter==s.end()) lim=INF; else lim=*iter;
		iter=ss.lower_bound(lim);
		if (iter==ss.begin())
		{
			printf("-1\n");
			return 0;
		}
		a[i]=*(--iter);
		iter=s.lower_bound(a[i]);
		if (iter!=s.begin())
		{
			int nn=*(--iter);
			if (nn>xx) xx=nn;
		}
		ss.erase(a[i]);s.insert(a[i]);
	}
	for (i=1;i<=n;i++) printf("%d ",a[i]);
	printf("\n");
}
