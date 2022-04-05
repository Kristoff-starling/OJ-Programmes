#include <bits/stdc++.h>
#define Pair pair<int,int>
#define x first
#define y second
using namespace std;

Pair a[148],b[148];
int n,t;

int head[100048],to[100048],nxt[100048],f[100048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

queue<int> q;int depth[100048];
bool bfs()
{
	int i,x,y;
	for (i=0;i<=t;i++) depth[i]=-1;
	depth[0]=0;q.push(0);
	while (!q.empty())
	{
		x=q.front();q.pop();
		for (i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if (depth[y]==-1 && f[i])
			{
				depth[y]=depth[x]+1;
				q.push(y);
			}
		}
	}
	if (depth[t]==-1) return false; else return true;
}

int dfs(int x,int maxf)
{
	if (x==t) return maxf;
	int i,y,minf,now,ans=0;
	for (i=head[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
			if (ans>=maxf) return ans;
		}
	}
	return ans;
}

int main ()
{
	int i,j;
	cin>>n;
	for (i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	for (i=1;i<=n;i++) cin>>b[i].x>>b[i].y;
	t=n*2+1;
	for (i=1;i<=n;i++) addedge(0,i,1);
	for (i=1;i<=n;i++) addedge(n+i,t,1);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (a[i].x<b[j].x && a[i].y<b[j].y) addedge(i,n+j,1);
	int ans=0;
	while (bfs()) ans+=dfs(0,2e9);
	cout<<ans<<endl;
	return 0;
}
