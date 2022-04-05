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

inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

struct node
{
	int num;
	int left,right;
	int k;
}query[100048];

int in[100048],out[100048];
int col[100048];
int cnt[100048];
int n,q,num,k,time=0;
int path[100048],path_top=0;
int ans[100048];
int sum[100048];

int head[100048],to[200048],nxt[200048],tot;
inline void addedge(int s,int t)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;
}

void dfs(int cur,int father)
{
	in[cur]=++time;
	path[time]=cur;
	int i,y;
	for (i=head[cur];i;i=nxt[i])
		if (to[i]!=father) dfs(to[i],cur);
	out[cur]=time;
}

bool cmp(node x,node y)
{
	if (x.left/magic!=y.left/magic) return x.left/magic<y.left/magic;
	return x.right<y.right;
}

int main ()
{
	int i,j,x,y;
	n=getint();q=getint();
	for (i=1;i<=n;i++) col[i]=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();
		addedge(x,y);
	}
	dfs(1,-1);
	//for (i=1;i<=n;i++) cout<<i<<' '<<in[i]<<' '<<out[i]<<endl;
	//for (i=1;i<=n;i++) cout<<path[i]<<' ';cout<<endl;
	for (i=1;i<=q;i++)
	{
		num=getint();k=getint();
		query[i].num=i;
		query[i].left=in[num];query[i].right=out[num];
		query[i].k=k;
	}
	sort(query+1,query+q+1,cmp);
	int cur_ans=0,cur_left,cur_right;
	for (i=query[1].left;i<=query[1].right;i++)
	{
		cnt[col[path[i]]]++;
		sum[cnt[col[path[i]]]]++;
	}
	ans[query[1].num]=sum[query[1].k];
	cur_left=query[1].left;cur_right=query[1].right;
	for (i=2;i<=q;i++)
	{
		if (query[i].left<cur_left)
			for (j=query[i].left;j<=cur_left-1;j++)
			{
				cnt[col[path[j]]]++;
				sum[cnt[col[path[j]]]]++;
			}
		if (query[i].left>cur_left)
			for (j=cur_left;j<=query[i].left-1;j++)
			{
				sum[cnt[col[path[j]]]]--;
				cnt[col[path[j]]]--;
			}
		if (query[i].right<cur_right)
			for (j=query[i].right+1;j<=cur_right;j++)
			{
				sum[cnt[col[path[j]]]]--;
				cnt[col[path[j]]]--;
			}
		if (query[i].right>cur_right)
			for (j=cur_right+1;j<=query[i].right;j++)
			{
				cnt[col[path[j]]]++;
				sum[cnt[col[path[j]]]]++;
			}
		cur_left=query[i].left;cur_right=query[i].right;
		ans[query[i].num]=sum[query[i].k];
	}
	for (i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
