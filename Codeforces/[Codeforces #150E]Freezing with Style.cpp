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
#include <Windows.h>
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LL long long
#define LB long double
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+7;
const double eps=1e-10;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;

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
	int maxn,max_ind;
}tree[600048];
int SZ;

void build()
{
	for (int i=1;i<=SZ*4+48;i++)
	{
		tree[i].maxn=-INF;
		tree[i].max_ind=0;
	}
}

int lft,rght;
Pair query(int cur,int left,int right)
{
	if (lft<=left && right<=rght)
		return mp(tree[cur].maxn,tree[cur].max_ind);
	Pair res1=mp(-INF,0),res2=mp(-INF,0);
	int mid=(left+right)>>1;
	if (lft<=mid) res1=query(cur<<1,left,mid);
	if (mid+1<=rght) res2=query(cur<<1|1,mid+1,right);
	if (res1.x>res2.x) return res1; else return res2;
}

int pos,Num,Sum;
void update(int cur)
{
	int nn=1,l=1,r=SZ,mid;
	while (l<r)
	{
		mid=(l+r)>>1;
		if (cur<=mid)
		{
			nn<<=1;
			r=mid;
		}
		else
		{
			nn=(nn<<1|1);
			l=mid+1;
		}
	}
	cur=nn;
	if (tree[cur].maxn<Sum)
	{
		tree[cur].maxn=Sum;
		tree[cur].max_ind=Num;
		while (cur!=1)
		{
			cur>>=1;
			if (tree[cur<<1].maxn>tree[cur<<1|1].maxn)
			{
				tree[cur].maxn=tree[cur<<1].maxn;
				tree[cur].max_ind=tree[cur<<1].max_ind;
			}
			else
			{
				tree[cur].maxn=tree[cur<<1|1].maxn;
				tree[cur].max_ind=tree[cur<<1|1].max_ind;
			}
		}
	}
}

int Root;
int n,Left,Right;
bool visited[200048];
int cnt[200048],sum[200048],depth[200048];
Pair anspair;

int tot=0,head[200048],to[200048],nxt[200048],f[200048],ff[200048];
inline void addedge(int s,int t,int l)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=l;
}

void dfs(int cur,int father)
{
	cnt[cur]=1;
	int i;
	for (i=head[cur];i;i=nxt[i])
		if (to[i]!=father && !visited[to[i]])
		{
			dfs(to[i],cur);
			cnt[cur]+=cnt[to[i]];
		}
}

int find_mid(int cur,int father,int sz)
{
	int i,y;
	for (i=head[cur];i;i=nxt[i])
		if (to[i]!=father && !visited[to[i]])
			if (cnt[to[i]]>sz/2) return find_mid(to[i],cur,sz);
	return cur;
}

struct ins
{
	int num,sum;
}v[200048],putin;int v_top,max_depth;

bool Dfs(int cur,int father)
{
	
	max_depth=max(max_depth,depth[cur]);
	if (Left<=depth[cur] && depth[cur]<=Right && sum[cur]>=0)
	{
		anspair.x=cur;
		anspair.y=Root;
		return true;
	}
	lft=min(max(1,Left-depth[cur]),SZ);rght=min(Right-depth[cur],SZ);
	if (lft>0 && rght>0 && rght>=lft)
	{
		Pair res=query(1,1,SZ);
		if (sum[cur]+res.x>=0)
		{
			anspair.x=cur;
			anspair.y=res.y;
			return true;
		}
	}
	putin.num=cur;putin.sum=sum[cur];
	if (v[depth[cur]].sum<putin.sum) v[depth[cur]]=putin;
	if (depth[cur]>=Right) return false;
	int i;
	for (i=head[cur];i;i=nxt[i])
		if (to[i]!=father && !visited[to[i]])
		{
			depth[to[i]]=depth[cur]+1;
			sum[to[i]]=sum[cur]+ff[i];
			if (Dfs(to[i],cur)) return true;
		}
	return false;
}

bool solve(int root,int sz)
{
	int i,j;
	dfs(root,-1);
	Root=root=find_mid(root,-1,sz);visited[root]=true;
	SZ=min(sz,Right);
	build();dfs(root,-1);
	for (i=head[root];i;i=nxt[i])
		if (!visited[to[i]])
		{
			//cout<<"$"<<endl;
			sum[to[i]]=ff[i];depth[to[i]]=1;
			for (j=1;j<=SZ;j++) v[j].sum=-INF;
			max_depth=1;//cout<<"#"<<endl;
			if (Dfs(to[i],root)) return true;
			for (j=1;j<=max_depth;j++)
			{
				Num=v[j].num;Sum=v[j].sum;
				update(j);
			}
		}
	for (i=head[root];i;i=nxt[i])
		if (!visited[to[i]] && solve(to[i],cnt[to[i]])) return true;
	return false;
}

vector<int> len;
int main ()
{
	int i,x,y,c;
	n=getint();Left=getint();Right=getint();
	for (i=1;i<=n-1;i++)
	{
		x=getint();y=getint();c=getint();
		addedge(x,y,c);
		len.pb(c);
	}
	int l=0,r=1e9,mid,need;
	sort(len.begin(),len.end());
	len.resize(unique(len.begin(),len.end())-len.begin());
	r=len.size()-1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		need=len[mid];
		for (i=1;i<=tot;i++) if (f[i]<need) ff[i]=-1; else ff[i]=1;
		memset(visited,false,sizeof(visited));
		if (solve(1,n)) l=mid+1; else r=mid-1;
	}
	printf("%d %d\n",anspair.x,anspair.y);
	return 0;
}
