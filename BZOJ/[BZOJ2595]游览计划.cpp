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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
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

int n,m,k;
int a[48][48];
int dp[48][48][2048];
bool inq[48][48];

struct info
{
	int x,y;
	int Mask;
}pre[48][48][2048];

inline int input()
{
	int i,j,res=0;
	n=getint();m=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
		{
			a[i][j]=getint();
			if (!a[i][j]) res++;
		}
	return res;
}

queue<int> q;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
inline void spfa(int Mask)
{
	int x,y,xx,yy,i;
	while (!q.empty())
	{
		x=q.front();q.pop();y=q.front();q.pop();
		inq[x][y]=false;
		for (i=0;i<=3;i++)
		{
			xx=x+dx[i];yy=y+dy[i];
			if (xx<1 || xx>n || yy<1 || yy>m) continue;
			if (x<1 || x>n || y<1 || y>m) continue;
			if (dp[xx][yy][Mask]>dp[x][y][Mask]+a[xx][yy])
			{
				dp[xx][yy][Mask]=dp[x][y][Mask]+a[xx][yy];
				pre[xx][yy][Mask]=info{x,y,Mask};
				if (!inq[xx][yy]) inq[xx][yy]=true,q.push(xx),q.push(yy);
			}
		}
	}
}

bool visited[48][48];
inline void getans(int x,int y,int Mask)
{
	if (x>=INF || pre[x][y][Mask].Mask==0) return;
	visited[x][y]=true;
	int prex=pre[x][y][Mask].x,prey=pre[x][y][Mask].y,preMask=pre[x][y][Mask].Mask;
	getans(prex,prey,preMask);
	if (prex==x && prey==y) getans(prex,prey,Mask-preMask);
}

int main ()
{
	int i,j,Mask,sub,cc=0;
	k=input();
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			for (Mask=0;Mask<=(1<<k)-1;Mask++)
				dp[i][j][Mask]=pre[i][j][Mask].x=INF;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (!a[i][j])
				dp[i][j][1<<(cc++)]=0;
	for (Mask=1;Mask<=(1<<k)-1;Mask++)
	{
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
			{
				for (sub=((Mask-1)&Mask);sub;sub=(Mask&(sub-1)))
				{
					if (dp[i][j][sub]+dp[i][j][Mask-sub]-a[i][j]<dp[i][j][Mask])
					{
						dp[i][j][Mask]=dp[i][j][sub]+dp[i][j][Mask-sub]-a[i][j];
						pre[i][j][Mask]=info{i,j,sub};
					}
				}
				if (dp[i][j][Mask]<INF) inq[i][j]=true,q.push(i),q.push(j);
			}
		spfa(Mask);
	}
	int mx=0,my=0;
	/*for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (dp[i][j][(1<<k)-1]<ans) ans=dp[i][j][(1<<k)-1],mx=i,my=j;*/
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (!a[i][j]) {mx=i;my=j;break;}
	getans(mx,my,(1<<k)-1);
	printf("%d\n",dp[mx][my][(1<<k)-1]);
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
			if (!a[i][j])
				printf("x");
			else
				printf(visited[i][j]?"o":"_");
		if (i!=n) printf("\n");
	}
	return 0;
}
