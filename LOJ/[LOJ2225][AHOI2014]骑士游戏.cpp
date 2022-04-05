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

const int MOD=1e9+7;
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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
LL A[200048],B[200048];
vector<int> v[200048],vv[200048];
LL dp[200048];bool inq[200048];
queue<int> q;

int main ()
{
	int i,nu,x,y;n=getint();
	for (i=1;i<=n;i++)
	{
		A[i]=getLL();B[i]=getLL();nu=getint();
		while (nu--) x=getint(),v[i].pb(x),vv[x].pb(i);
	}
	memset(inq,true,sizeof(inq));
	for (i=1;i<=n;i++) q.push(i),dp[i]=B[i];
	while (!q.empty())
	{
		x=q.front();q.pop();inq[x]=false;
		LL res=A[x];
		for (i=0;i<int(v[x].size());i++)
		{
			y=v[x][i];res+=dp[y];
			if (res>dp[x]) break;
		}
		if (res<dp[x])
		{
			dp[x]=res;
			for (i=0;i<int(vv[x].size());i++)
			{
				y=vv[x][i];
				if (!inq[y])
				{
					inq[y]=true;
					q.push(y);
				}
			}
		}
	}
	printf("%lld\n",dp[1]);
	return 0;
}
