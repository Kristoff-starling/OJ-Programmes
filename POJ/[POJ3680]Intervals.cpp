#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <functional>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <list>
#include <stack>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=100000;
const int LIM=1e5;

int n,k,S,T;

int table[LIM+48];

int head[MAXN+48],cur[MAXN+48],nxt[MAXN+48],to[MAXN+48],f[MAXN+48],cost[MAXN+48],tot=1;
inline void addedge(int s,int t,int cap,int cc)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=cap;cost[tot]=cc;
	to[++tot]=s;nxt[tot]=head[t];head[t]=tot;f[tot]=0;cost[tot]=-cc;
}

struct Edge
{
	int x,y,c;
	inline void input() {x=getint();y=getint();c=getint();}
}edge[MAXN+48];

vector<int> pos;
int N;

int mincost;
int D[MAXN+48];bool visited[MAXN+48];
inline int aug(int x,int maxf)
{
	if (x==T) {mincost+=(-D[S])*maxf;return maxf;}
	visited[x]=true;
	int y,minf,now,ans=0;
	for (int &i=cur[x];i;i=nxt[i])
	{
		y=to[i];
		if (!visited[y] && f[i] && D[x]+cost[i]-D[y]==0)
		{
			minf=min(maxf-ans,f[i]);
			now=aug(y,minf);
			f[i]-=now;f[i^1]+=now;ans+=now;
		}	
	}
	return ans;
}

inline bool relabel()
{
	int d=INF,cur,i,y;
	for (cur=1;cur<=N+2;cur++)
		if (visited[cur])
			for (i=head[cur];i;i=nxt[i])
			{
				y=to[i];
				if (!visited[y] && f[i]) d=min(d,D[cur]+cost[i]-D[y]);
			}
	if (d==INF) return false;
	for (cur=1;cur<=N+2;cur++)
		if (visited[cur]) D[cur]-=d;
	return true;
}

inline void Clear()
{
	memset(head,0,sizeof(head));tot=1;
	pos.clear();
	mincost=0;memset(D,0,sizeof(D));
}

inline int zkw()
{
	do
	{
		memcpy(cur+1,head+1,(N+2)*sizeof(int));
		do
			memset(visited,false,sizeof(visited));
		while (aug(S,INF));
	}
	while (relabel());
}

int main ()
{
	int ca,i;ca=getint();
	while (ca--)
	{
		n=getint();k=getint();
		Clear();
		for (i=1;i<=n;i++) edge[i].input(),pos.pb(edge[i].x),pos.pb(edge[i].y);
		sort(pos.begin(),pos.end());
		pos.resize(unique(pos.begin(),pos.end())-pos.begin());N=int(pos.size());
		for (i=0;i<=N-1;i++) table[pos[i]]=i+1;
		S=N+1;T=N+2;
		for (i=1;i<=N-1;i++) addedge(i,i+1,INF,0);
		addedge(S,1,k,0);addedge(N,T,k,0);
		int ans=0;
		for (i=1;i<=n;i++)
		{
			addedge(table[edge[i].y],table[edge[i].x],1,edge[i].c);
			ans-=edge[i].c;addedge(S,table[edge[i].y],1,0);addedge(table[edge[i].x],T,1,0);
		}
		zkw();ans+=mincost;
		printf("%d\n",-ans);
	}
	return 0;
}
