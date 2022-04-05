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
#define pf push_front
#define LL long long
#define Pair pair<int,int>
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=1e9+7;
const int INF=2e9;
const int magic=348;
const LL LINF=2e16;
const double eps=1e-10;
const int Ni=500000004;
 
inline int getint()
{
	char ch;
	while ((ch=getchar())<'0' || ch>'9') {}
	int res=ch-'0';
	while ((ch=getchar())>='0' && ch<='9') res=res*10+ch-'0';
	return res;
}

LL ans=0;
int n,L,W;
int head[300048],nxt[300048],to[300048],tot=0;LL f[300048];
inline int addedge(int s,int t,int l)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=l;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=l;
}

bool visited[300048];
int cnt[300048];
int depth[300048];LL sum[300048];
multiset<Pair> s;
vector<int> u;

int c[300048];
inline void update(int x)
{
	while (x<=n)
	{
		c[x]++;
		if (c[x]==1) u.pb(x);
		x+=LOWBIT(x);
	}
}
inline int query(int x)
{
	int res=0;
	while (x>0)
	{
		res+=c[x];
		x-=LOWBIT(x);
	}
	return res;
}

void dfs(int cur,int father)
{
	cnt[cur]=1;
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !visited[y])
		{
			dfs(y,cur);
			cnt[cur]+=cnt[y];
		}
	}
}

int find_mid(int cur,int father,int sz)
{
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !visited[y] && cnt[y]>sz/2) return find_mid(y,cur,sz);
	}
	return cur;
}

vector<Pair> vv;
void Dfs(int cur,int father)
{
	cnt[cur]=1;
	int i,y;
	for (i=head[cur];i;i=nxt[i])
	{
		y=to[i];
		if (y!=father && !visited[y])
		{
			depth[y]=depth[cur]+1;
			sum[y]=sum[cur]+f[i];
			Dfs(y,cur);
			cnt[cur]+=cnt[y];
		}
	}
	vv.pb(mp(sum[cur],depth[cur]));
}

bool cmp(Pair x,Pair y)
{
	return x.x>y.x;
}

void solve(int root,int sz)
{
	dfs(root,-1);
	int i,j,y,mid=find_mid(root,-1,sz);
	root=mid;visited[root]=true;
	s.clear();multiset<Pair>::iterator iter;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y])
		{
			vv.clear();u.clear();
			depth[y]=1;sum[y]=f[i];
			Dfs(y,root);
			sort(vv.begin(),vv.end(),cmp);iter=s.begin();
			for (j=0;j<vv.size();j++)
			{
				while (iter!=s.end() && iter->x+vv[j].x<=W)
				{
					//cout<<iter->y<<"("<<endl;
					update(iter->y);
					++iter;
				}
				//if (iter!=s.end() && iter->x+vv[j].x<=W) update(iter->y);
				ans+=query(L-vv[j].y);
				//cout<<L-vv[j].y<<")"<<endl;
				if (vv[j].x<=W && vv[j].y<=L) ans++;
				//cout<<y<<' '<<ans<<"*"<<endl;
			}
			//cout<<y<<' '<<ans<<' '<<s.size()<<"*"<<endl;
			for (j=0;j<u.size();j++) c[u[j]]=0;
			for (j=0;j<vv.size();j++) s.insert(vv[j]);
		}
	}
	//cout<<root<<' '<<ans<<endl;
	for (i=head[root];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y]) solve(y,cnt[y]);
	}
}

int main ()
{
	n=getint();L=getint();W=getint();
	L=min(L,n);
	int i,x,s;
	for (i=1;i<=n-1;i++)
	{
		x=getint();s=getint();
		addedge(i+1,x,s);
	}
	solve(1,n);
	printf("%I64d\n",ans);
	return 0;
}
