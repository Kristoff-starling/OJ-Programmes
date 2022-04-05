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
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int Z,D,H,N,Hl,Hr;
int L[148],R[148][148],F[148][148][148],sum[148][148],sum1[148][148];
int t;

int head[200048],to[800048],nxt[800048],f[800048],tot=1;
inline void addedge(int s,int t,int cap)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;
}

int depth[200048];queue<int> q;
inline bool bfs()
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

inline int dfs(int x,int maxf)
{
	if (x==t || !maxf) return maxf;
	int i,y,now,minf,ans=0;
	for (i=head[x];i;i=nxt[i])
	{
		y=to[i];
		if (depth[y]==depth[x]+1 && f[i])
		{
			minf=min(maxf-ans,f[i]);
			now=dfs(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}
		if (ans>=maxf) return ans;
	}
	if (!ans) depth[x]=0;
	return ans;
}

int main ()
{
	int i,j,k;
	Z=getint();D=getint();H=getint();N=getint();Hl=getint();Hr=getint();
	for (i=1;i<=Z;i++) L[i]=getint();
	for (i=1;i<=D;i++)
		for (j=1;j<=H;j++)
			R[i][j]=getint();
	for (i=1;i<=Z;i++)
		for (j=1;j<=D;j++)
		{
			sum[i][j]=N;
			for (k=1;k<=H;k++)
			{
				F[i][j][k]=getint();
				sum[i][j]-=(F[i][j][k]==0);
				if (Hl<=k && k<=Hr) sum1[i][j]+=(F[i][j][k]==1);
			}
			if (sum1[i][j]==0) {printf("No\n");return 0;}
			if (sum[i][j]<0) {printf("No\n");return 0;}
		}
	t=Z+D*Z+D*Z+D*H+1;
	for (i=1;i<=Z;i++) addedge(0,i,L[i]);
	for (i=1;i<=Z;i++)
		for (j=1;j<=D;j++)
			addedge(i,Z+(i-1)*D+j,sum[i][j]);
	for (i=1;i<=Z;i++)
		for (j=1;j<=D;j++)
			addedge(Z+(i-1)*D+j,Z+D*Z+(i-1)*D+j,sum1[i][j]-1);
	for (i=1;i<=Z;i++)
		for (j=1;j<=D;j++)
			for (k=1;k<=H;k++)
			{
				if (!F[i][j][k]) continue;
				if (Hl<=k && k<=Hr)
					addedge(Z+D*Z+(i-1)*D+j,Z+D*Z+D*Z+(j-1)*H+k,1);
				else
					addedge(Z+(i-1)*D+j,Z+D*Z+D*Z+(j-1)*H+k,1);
			}
	for (i=1;i<=D;i++)
		for (j=1;j<=H;j++)
			addedge(Z+D*Z+D*Z+(i-1)*H+j,t,R[i][j]);
	int ans=0,need=0;
	for (i=1;i<=D;i++)
		for (j=1;j<=H;j++)
			need+=R[i][j];
	while (bfs()) ans+=dfs(0,2e9);
	if (ans==need) printf("Yes\n"); else printf("No\n");
	return 0;
}
