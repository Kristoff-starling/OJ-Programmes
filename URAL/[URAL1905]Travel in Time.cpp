#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <sstream>
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

const int MOD=1e9+3;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,e;

int sp,ep,st,et;
bool visited[100048];int pre[100048];
queue<int> q;

struct Edge
{
	int x,y;
	int t1,t2,ind;
	Edge() {}
	inline Edge(int a,int b,int c,int d,int e) {x=a;y=b;t1=c;t2=d;ind=e;}
}edge[100048];

int head[100048],nxt[300048],to[300048],t1[300048],t2[300048],ind[100048],tot=1,cur[100048];
inline void addedge(int s,int t,int T1,int T2,int Ind)
{
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;t1[tot]=T1;t2[tot]=T2;ind[tot]=Ind;
}

inline int Count(int cur) {if (pre[cur]==e) return 1; else return Count(pre[cur])+1;}
inline void print(int cur,int cnt) {if (pre[cur]==-1) {printf("%d\n",cnt);printf("%d ",cur);return;}print(pre[cur],cnt+1);printf("%d ",cur);}
inline bool cmp(Edge x,Edge y) {return x.ind<y.ind;}
inline bool cmp1(Edge x,Edge y) {return x.t1<y.t1;}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	int x,y,T1,T2;
	n=getint();e=getint();
	for (register int i=1;i<=e;i++)
	{
		x=getint();y=getint();T1=getint();T2=getint();
		edge[i]=Edge(x,y,T1,T2,i);
	}
	sp=getint();ep=getint();st=getint();et=getint();
	if (sp==ep && st<=et) {puts("0");return 0;}
	sort(edge+1,edge+e+1,cmp1);
	for (register int i=1;i<=e;i++)
		addedge(edge[i].x,edge[i].y,edge[i].t1,edge[i].t2,edge[i].ind);
	sort(edge+1,edge+e+1,cmp);
	for (register int i=1;i<=e;i++) visited[i]=false;
	memset(pre,-1,sizeof(pre));
	edge[++e]=Edge(-1,sp,-1,st,-1);visited[e]=true;q.push(e);
	while (!q.empty())
	{
		int x=q.front();q.pop();
		int cur=edge[x].y;
		for (int &i=head[cur];i;i=nxt[i])
		{
			y=ind[i];if (visited[y]) continue;
			if (edge[y].t1<edge[x].t2) break;
			visited[y]=true;
			pre[edge[y].ind]=edge[x].ind;q.push(y);
			if (edge[y].y==ep && edge[y].t2<=et)
			{
				print(edge[y].ind,1);puts("");return 0;
			}
		}
	}
	printf("Impossible\n");return 0;
}
