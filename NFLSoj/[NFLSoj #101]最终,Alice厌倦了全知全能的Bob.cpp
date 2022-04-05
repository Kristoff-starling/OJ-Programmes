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

vector<int> v[148];
char s[148];
int n,maxdepth[148];
LL mypow[60];

inline void dfs(int cur,int father)
{
	maxdepth[cur]=1;int i;
	for (i=0;i<int(v[cur].size());i++)
		if (v[cur][i]!=father)
		{
			dfs(v[cur][i],cur);
			maxdepth[cur]=max(maxdepth[cur],1+maxdepth[v[cur][i]]);
		}
}

int main ()
{
	int i,x;
	n=getint();
	for (i=1;i<=n-1;i++) x=getint(),v[x].pb(i+1),v[i+1].pb(x);
	mypow[0]=1ll;for (i=1;i<=55;i++) mypow[i]=mypow[i-1]*2;
	scanf("%s",s+1);
	dfs(1,-1);
	LL SG=0;
	for (i=1;i<=n;i++) if (s[i]=='W') SG^=mypow[maxdepth[i]];
	printf(SG?"Alice\n":"BillXu2000\n");
	return 0;
}
