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

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,e;
vector<int> v[1048];
bool ga[1048][1048];
bool S[1048];
bool visited[1048];
bool added[1048];
vector<int> G;
vector<int> G1;

void dfs(int cur)
{
	int i;
	visited[cur]=true;
	G.pb(cur);
	for (i=0;i<v[cur].size();i++)
		if (!visited[v[cur][i]])
		{
			if (S[v[cur][i]])
			{
				if (!added[v[cur][i]])
				{
					G1.pb(v[cur][i]);
					added[v[cur][i]]=true;
				}
				continue;
			}
			dfs(v[cur][i]);
		}
}

int main ()
{
	int i,j,k,cen,x,y;
	n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		v[x].pb(y);v[y].pb(x);
		ga[x][y]=true;ga[y][x]=true;
	}
	for (cen=1;cen<=n;cen++)
	{
		memset(S,false,sizeof(S));memset(visited,false,sizeof(visited));
		for (i=0;i<v[cen].size();i++) S[v[cen][i]]=true;
		for (i=1;i<=n;i++)
			if (i!=cen && !visited[i] && !S[i])
			{
				memset(added,false,sizeof(added));
				G.clear();G1.clear();
				dfs(i);
				int num=G1.size();
				for (j=0;j<G1.size();j++)
					for (k=0;k<G1.size();k++)
						if (G1[j]!=G1[k] && !ga[G1[j]][G1[k]])
						{
							printf("yes\n");
							return 0;
						}
			}
	}
	printf("no\n");
	return 0;
}
