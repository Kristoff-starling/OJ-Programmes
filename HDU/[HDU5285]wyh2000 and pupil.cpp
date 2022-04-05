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

int bel[100048];
bool visited[100048];
vector<int> v[100048];
vector<int> h1,h2;
vector<int> ans1,ans2;
int n,e;
bool superf;

struct node
{
	int num1,num2;
	vector<int> h1,h2;
	int choose;
}a[100048];
int tot=0;

int used[100048],u_top=0;
queue<int> q;
void bfs(int start)
{
	while (!q.empty()) q.pop();
	q.push(start);
	int i,x;
	h1.clear();h2.clear();
	u_top=0;
	bel[start]=1;
	while (!q.empty())
	{
		x=q.front();q.pop();visited[x]=true;used[++u_top]=x;
		if (bel[x]==1) h1.pb(x); else h2.pb(x);
		for (i=0;i<v[x].size();i++)
		{
			if (!bel[v[x][i]])
			{
				bel[v[x][i]]=3-bel[x];
				q.push(v[x][i]);
			}
			if (bel[v[x][i]] && bel[v[x][i]]+bel[x]!=3)
			{
				superf=false;
				return;
			}
		}
	}
	a[++tot].h1=h1;a[tot].h2=h2;
	a[tot].num1=h1.size();a[tot].num2=h2.size();
	for (i=1;i<=u_top;i++) bel[used[i]]=0;
}

void Clear()
{
	int i;
	for (i=1;i<=n;i++) v[i].clear();
	memset(visited,false,sizeof(visited));
	tot=0;
}

int main ()
{
	int i,j,x,y,ca;
	ca=getint();
	while (ca--)
	{
		n=getint();e=getint();
		Clear();
		for (i=1;i<=e;i++)
		{
			x=getint();y=getint();
			v[x].pb(y);v[y].pb(x);
		}
		if (n<2)
		{
			printf("Poor wyh\n");
			continue;
		}
		superf=true;
		for (i=1;i<=n;i++)
			if (!visited[i])
			{
				bfs(i);
				if (!superf)
				{
					printf("Poor wyh\n");
					break;
				}
			}
		if (!superf) continue;
		int cnt1=0,cnt2=0;
		for (i=1;i<=tot;i++) cnt1+=max(a[i].num1,a[i].num2),cnt2+=min(a[i].num1,a[i].num2);
		if (cnt2!=0)
			printf("%d %d\n",cnt1,cnt2);
		else
		{
			if (tot==1)
			{
				printf("Poor wyh\n");
				continue;
			}
			int minn=INF;
			for (i=1;i<=tot;i++) minn=min(minn,max(a[i].num1,a[i].num2));
			cnt1-=minn;cnt2+=minn;
			printf("%d %d\n",cnt1,cnt2);
		}
	}
	return 0;
}
