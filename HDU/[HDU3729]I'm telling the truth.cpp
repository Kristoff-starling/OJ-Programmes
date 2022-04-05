#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <cmath>
#include <cctype>
#include <stack>
#include <sstream>
#define LL long long
#define LB long double
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
bool state[100048];int result[100048];
vector<int> v[48+48];
vector<int> ans_list;

void Clear()
{
	int i;
	for (i=1;i<=n;i++) v[i].clear();
	memset(result,0,sizeof(result));
}

bool find(int cur)
{
	int i;
	for (i=0;i<v[cur].size();i++)
		if (!state[v[cur][i]])
		{
			state[v[cur][i]]=true;
			if (!result[v[cur][i]] || find(result[v[cur][i]]))
			{
				result[v[cur][i]]=cur;
				return true;
			}
		}
	return false;
}

int main ()
{
	int i,j,l,r,ca;
	ca=getint();
	while (ca--)
	{
		n=getint();
		Clear();
		for (i=1;i<=n;i++)
		{
			l=getint();r=getint();
			for (j=l;j<=r;j++) v[i].pb(j);
		}
		int ans=0;
		for (i=n;i>=1;i--)
		{
			memset(state,false,sizeof(state));
			if (find(i)) ans++;
		}
		ans_list.clear();
		for (i=1;i<=100000;i++) if (result[i]) ans_list.pb(result[i]);
		sort(ans_list.begin(),ans_list.end());
		printf("%d\n",ans);
		for (i=0;i<ans_list.size();i++) 
		{
			printf("%d",ans_list[i]);
			if (i==int(ans_list.size()-1)) printf("\n"); else printf(" ");
		}
	}
	return 0;
}
