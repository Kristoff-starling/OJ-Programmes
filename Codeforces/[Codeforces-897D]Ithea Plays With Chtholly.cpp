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
#include <Windows.h>
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

inline int myabs(int x)
{
	return x>=0?x:-x;
}

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

int a[1048];
int n,m,c,p,head,tail;

int main ()
{
	cin>>n>>m>>c;
	head=0;tail=n+1;
	while (m--)
	{
		cin>>p;
		bool f=false;
		if (p>c/2)
		{
			for (int i=n;i>=tail;i--)
				if (a[i]<p)
				{
					printf("%d\n",i);
					a[i]=p;
					f=true;
					break;
				}
			if (!f)
			{
				a[--tail]=p;
				printf("%d\n",tail);
			}
		}
		else
		{
			for (int i=1;i<=head;i++)
				if (a[i]>p)
				{
					printf("%d\n",i);
					a[i]=p;
					f=true;
					break;
				}
			if (!f)
			{
				a[++head]=p;
				printf("%d\n",head);
			}
		}
		fflush(stdout);
		if (head+1==tail) break;
	}
	return 0;
}
