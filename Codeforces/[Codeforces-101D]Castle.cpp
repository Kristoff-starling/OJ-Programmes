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
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
vector<Pair> v[100048];
int sz[100048],edgelen[100048];

inline void dfs(int cur,int father)
{
	int i,y;sz[cur]=1;edgelen[cur]=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father)
		{
			dfs(y,cur);
			sz[cur]+=sz[y];
			edgelen[y]+=v[cur][i].y*2;edgelen[cur]+=edgelen[y];
		}
	}
}

inline bool cmp(Pair x,Pair y) {return (long long)edgelen[x.x]*sz[y.x]<(long long)edgelen[y.x]*sz[x.x];}

LL ans=0;
inline void Dfs(int cur,int father,int tm)
{
	int i,y;sort(v[cur].begin(),v[cur].end(),cmp);
	ans+=tm;int curtm=tm;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (y!=father) Dfs(y,cur,curtm+v[cur][i].y),curtm+=edgelen[y];
	}
}
	
int main ()
{
	int i,x,y,c;n=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();c=getint();
		v[x].pb(mp(y,c));v[y].pb(mp(x,c));
	}
	dfs(1,-1);
	Dfs(1,-1,0);
	double fans=ans;fans/=(n-1);
	printf("%.6lf\n",fans);
	return 0;
}
