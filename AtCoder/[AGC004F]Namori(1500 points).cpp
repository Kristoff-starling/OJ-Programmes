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
const int INF=1e9;
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

int n,e;
vector<int> v[100048];

namespace tree
{
	int depth[100048];
	int cnt[100048][2];
	inline int myabs(int x) {return x>=0?x:-x;}
	inline void dfs(int cur,int father)
	{
		int i,y;
		cnt[cur][0]=cnt[cur][1]=0;cnt[cur][depth[cur]]=1;
		for (i=0;i<int(v[cur].size());i++)
		{
			y=v[cur][i];
			if (y!=father)
			{
				depth[y]=depth[cur]^1;dfs(y,cur);
				cnt[cur][0]+=cnt[y][0];cnt[cur][1]+=cnt[y][1];
			}
		}
	}
	inline int solve()
	{
		int i,x,y;
		for (i=1;i<=e;i++) x=getint(),y=getint(),v[x].pb(y),v[y].pb(x);
		depth[1]=1;dfs(1,-1);
		if (cnt[1][0]!=cnt[1][1]) return -1;
		int res=0;
		for (i=2;i<=n;i++) res+=myabs(cnt[i][0]-cnt[i][1]);
		return res;
	}
}

int main ()
{
	n=getint();e=getint();
	if (e==n-1) {printf("%d\n",tree::solve());return 0;}
	return 0;
}
