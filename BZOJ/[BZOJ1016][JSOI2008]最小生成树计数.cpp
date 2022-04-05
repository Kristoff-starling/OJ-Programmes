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

const int MOD=31011;
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
int pre[148],rnk[148];
inline int find_anc(int x)
{
	if (x==pre[x]) return pre[x]; else return find_anc(pre[x]);
}
inline Pair update(int x,int y)
{
	x=find_anc(x);y=find_anc(y);
	if (rnk[x]>=rnk[y])
	{
		pre[y]=x;
		if (rnk[x]==rnk[y])
		{
			rnk[x]++;
			return mp(x,1);
		}
		return mp(x,0);
	}
	else
	{
		pre[x]=y;
		return mp(y,0);
	}
}

struct Edge
{
	int x,y;
	int len,nl;
}edge[1048];
int sum[1048],Left[1048],Right[1048];
int ans=1;

bool cmp(Edge x,Edge y)
{
	return x.len<y.len;
}

int dfs(int cur,int ed,int cur_cnt,int lim)
{
	if (cur==ed+1)
	{
		if (cur_cnt==lim) return 1; else return 0;
	}
	int res=0;
	if (cur_cnt<lim && find_anc(edge[cur].x)!=find_anc(edge[cur].y))
	{
		int xx=find_anc(edge[cur].x),yy=find_anc(edge[cur].y);
		Pair sta=update(xx,yy);
		res+=dfs(cur+1,ed,cur_cnt+1,lim);
		//int xx=find_anc(edge[cur].x),yy=find_anc(edge[cur].y);
		if (sta.x==xx)
		{
			pre[yy]=yy;
			if (sta.y) rnk[xx]--;
		}
		else
		{
			pre[xx]=xx;
			if (sta.y) rnk[yy]--;
		}
	}
	res+=dfs(cur+1,ed,cur_cnt,lim);
	return res;
}

void update_edge(int left,int right,int lim)
{
	int cnt=0;
	for (int i=left;i<=right && cnt<lim;i++)
		if (find_anc(edge[i].x)!=find_anc(edge[i].y))
		{
			cnt++;
			update(edge[i].x,edge[i].y);
		}
}

int main ()
{
	int i;
	n=getint();e=getint();
	for (i=1;i<=n;i++) pre[i]=i,rnk[i]=1;
	for (i=1;i<=e;i++) edge[i].x=getint(),edge[i].y=getint(),edge[i].len=getint();
	sort(edge+1,edge+e+1,cmp);
	edge[1].nl=1;
	for (i=2;i<=e;i++) edge[i].nl=edge[i-1].nl+(edge[i].len==edge[i-1].len?0:1);
	for (i=1;i<=e;i++)
	{
		if (i==1 || edge[i].nl!=edge[i-1].nl) Left[edge[i].nl]=i;
		if (i==e || edge[i].nl!=edge[i+1].nl) Right[edge[i].nl]=i;
	}
	//for (i=1;i<=e;i++) cout<<edge[i].nl<<' ';
	//cout<<endl;
	int cnt=0;
	for (i=1;i<=e && cnt<n-1;i++)
		if (find_anc(edge[i].x)!=find_anc(edge[i].y))
		{
			cnt++;
			sum[edge[i].nl]++;
			update(edge[i].x,edge[i].y);
		}
	if (cnt<n-1)
	{
		printf("0\n");
		return 0;
	}
	//for (i=1;i<=edge[e].nl;i++) cout<<sum[i]<<' '<<Left[i]<<' '<<Right[i]<<endl;
	for (i=1;i<=n;i++) pre[i]=i,rnk[i]=1;
	for (i=1;i<=edge[e].nl;i++)
		if (sum[i])
		{
			cnt=dfs(Left[i],Right[i],0,sum[i]);
			ans=ans*cnt%MOD;
			update_edge(Left[i],Right[i],sum[i]);
		}
	printf("%d\n",ans);
	return 0;
}
