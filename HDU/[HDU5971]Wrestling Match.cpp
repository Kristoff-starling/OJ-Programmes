#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const int base=248;

inline int getint()
{
	char ch;int res=0;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int pre[2048];
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

vector<int> v[2048];
bool good[1048],bad[1048];
int n,e,gnum,bnum;
Pair edge[100048];
int bel[2048];
int used[2048],u_top=0;
bool superf;
bool visited[2048];

queue<int> q;
void bfs(int start)
{
	while (!q.empty()) q.pop();
	q.push(start);
	int i,x;
	while (!q.empty())
	{
		x=q.front();q.pop();visited[x]=true;
		for (i=0;i<v[x].size();i++)
			if (!bel[v[x][i]])
			{
				bel[v[x][i]]=3-bel[x];
				q.push(v[x][i]);
			}
			else
			{
				if (bel[v[x][i]]+bel[x]!=3)
				{
					superf=false;
					printf("NO\n");
					return;
				}
				if (!visited[v[x][i]]) q.push(v[x][i]);
			}
	}
}

void Clear()
{
	superf=true;
	memset(visited,false,sizeof(visited));
	int i;
	for (i=1;i<=n;i++) v[i].clear();
	memset(bel,0,sizeof(bel));
}

int main ()
{
	int i,x,y;
	while (scanf("%d%d%d%d",&n,&e,&gnum,&bnum)!=EOF)
	{
		Clear();
		for (i=1;i<=e;i++)
		{
			x=getint();y=getint();
			v[x].pb(y);v[y].pb(x);
		}
		for (i=1;i<=gnum;i++)
		{
			x=getint();
			bel[x]=1;
		}
		for (i=1;i<=bnum;i++)
		{
			x=getint();
			bel[x]=2;
		}
		for (i=1;i<=n;i++)
			if (!visited[i] && bel[i])
			{
				bfs(i);
				if (!superf) break;
			}
		if (!superf) continue;
		for (i=1;i<=n;i++)
			if (!visited[i])
			{
				bel[i]=1;
				bfs(i);
				if (!superf) break;
			}
		if (superf) printf("YES\n");
	}
	return 0;
}
