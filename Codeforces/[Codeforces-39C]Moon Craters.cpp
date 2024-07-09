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
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int zero_stand=1500;
const int MOD=1e9+7;
const int INF=0x7ffffff;
const int magic=348;

int n;
struct node
{
	int x,y;
	int num;
}a[2048];

int dp[2048][2048];
pair<pair<int,int>,pair<int,int> >fa[2048][2048];
bool used[2048][2048];
int ind[2048];
int l[2048],r[2048];
int nleft[2048],nright[2048];
set<Pair> s;
set<Pair>::iterator iter;

bool cmp(node x,node y)
{
	if (x.x+x.y!=y.x+y.y) return x.x+x.y<y.x+y.y;
	return x.y<y.y;
}

void print(int x,int y)
{
	if (used[x][y]) printf("%d ",a[x].num);
	if (fa[x][y].x!=mp(-1,-1)) print(fa[x][y].x.x,fa[x][y].x.y);
	if (fa[x][y].y!=mp(-1,-1)) print(fa[x][y].y.x,fa[x][y].y.y);
}

int main ()
{
	int i,j;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].num=i;
	}
	sort(a+1,a+n+1,cmp);
	for (i=1;i<=n;i++)
	{
		l[i]=a[i].x-a[i].y;
		r[i]=a[i].x+a[i].y;
	}
	for (i=1;i<=n;i++) s.insert(mp(r[i],i));
	for (i=1;i<=n;i++)
	{
		iter=s.lower_bound(mp(l[i],INF));
		if (iter==s.begin()) nleft[i]=-1; else nleft[i]=(*--iter).y;
	}
	s.clear();
	for (i=1;i<=n;i++) s.insert(mp(l[i],i));
	for (i=1;i<=n;i++)
	{
		s.erase(mp(l[i],i));
		iter=s.lower_bound(mp(l[i],0));
		if (iter==s.end())
		{
			nright[i]=-1;
			s.insert(mp(l[i],i));
			continue;
		}
		nright[i]=iter->y;
		s.insert(mp(l[i],i));
	}
	for (j=1;j<=n;j++)
	{
		if (a[1].x-a[1].y>=l[j]) 
		{
			dp[1][j]=1;
			used[1][j]=true;
		}
		else 
		{
			dp[1][j]=0;
			used[1][j]=false;
		}
		fa[1][j]=mp(mp(-1,-1),mp(-1,-1));
	}
	pair<pair<int,int>,pair<int,int> > ff;
	for (i=2;i<=n;i++)
		for (j=1;j<=n;j++)
		{
			dp[i][j]=dp[i-1][j];
			fa[i][j]=mp(mp(i-1,j),mp(-1,-1));
			used[i][j]=false;
			if (a[i].x-a[i].y<l[j]) continue;
			ff=mp(mp(-1,-1),mp(-1,-1));
			int res=0;
			if (nright[i]!=-1) 
			{
				res+=dp[i-1][nright[i]];
				ff.x=mp(i-1,nright[i]);
			}
			if (nleft[i]!=-1)
			{
				res+=dp[nleft[i]][j];
				ff.y=mp(nleft[i],j);
			}
			res++;
			if (res>dp[i][j])
			{
				dp[i][j]=max(dp[i][j],res);
				fa[i][j]=ff;
				used[i][j]=true;
			}
		}
	int ans=-1,pos;
	for (j=1;j<=n;j++) 
		if (dp[n][j]>ans)
		{
			ans=dp[n][j];
			pos=j;
		}
	printf("%d\n",ans);
	print(n,pos);
	return 0;
}