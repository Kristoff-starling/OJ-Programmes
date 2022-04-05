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
const int INF=1e9;
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

int dp[18][18][257];Pair pre[17][17][257];

inline int getind(int x,int y) {return (x-1)*4+y;}

struct node
{
	int val;
	string route;
	inline void init() {val=-INF;route="";}
}route[17][17][17][17];

struct Map
{
	int Val[5][5];
	int door[5][5];
}a[18];

int n,Sx,Sy,sind;

vector<char> r;int sum=0;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
char table[]={'N','E','S','W'};
bool visited[5][5];
inline void update(int k,int s,int t,int len)
{
	if (sum>route[k][s][t][len].val)
	{
		route[k][s][t][len].val=sum;
		route[k][s][t][len].route="";
		for (register int i=0;i<int(r.size());i++) route[k][s][t][len].route+=string(1,r[i]);
	}
}
inline void dfs(int k,int x,int y,int step)
{
	visited[x][y]=true;sum+=a[k].Val[x][y];int dir,xx,yy;
	if (a[k].door[x][y]) update(k,sind,getind(x,y),step);
	for (dir=0;dir<=3;dir++)
	{
		xx=x+dx[dir];yy=y+dy[dir];
		if (1<=xx && xx<=4 && 1<=yy && yy<=4 && !visited[xx][yy])
		{
			r.pb(table[dir]);
			dfs(k,xx,yy,step+1);
			r.pop_back();
		}
	}
	visited[x][y]=false;sum-=a[k].Val[x][y];
}

inline void update(int k,int i,int j,int d,int lk,int li,int lj,int ld)
{
	if (dp[lk][getind(li,lj)][ld]+route[k][getind(li,lj)][getind(i,j)][d-ld].val>dp[k][getind(i,j)][d])
	{
		dp[k][getind(i,j)][d]=dp[lk][getind(li,lj)][ld]+route[k][getind(li,lj)][getind(i,j)][d-ld].val;
		pre[k][getind(i,j)][d]=mp(getind(li,lj),ld);
	}
}

string Route="";
inline void getans(int k,int pos,int d)
{
	int lp=pre[k][pos][d].x,ld=pre[k][pos][d].y;
	if (k!=n) getans(k+1,lp,ld);
	Route+=route[k][lp][pos][d-ld].route;
	if (k!=1) Route+="D";
}

int main ()
{
	n=getint();int i,j,k,d,kd,li,lj;
	for (k=n;k>=1;k--)
	{
		for (i=1;i<=4;i++)
			for (j=1;j<=4;j++)
				a[k].Val[i][j]=getint();
		for (i=1;i<=4;i++)
			for (j=1;j<=4;j++)
				a[k].door[i][j]=getint();
	}
	for (i=1;i<=4;i++)
		for (j=1;j<=4;j++)
			a[1].door[i][j]=1;
	Sx=getint();Sy=getint();
	for (k=n;k>=1;k--)
		for (i=1;i<=16;i++)
			for (j=1;j<=16;j++)
				for (d=0;d<=16;d++)
					route[k][i][j][d].init();
	for (k=n;k>=1;k--)
	{
		if (k==n) sind=getind(Sx,Sy),dfs(k,Sx,Sy,1);
		else
			for (i=1;i<=4;i++)
				for (j=1;j<=4;j++)
					if (a[k+1].door[i][j]) sind=getind(i,j),dfs(k,i,j,1);
	}
	for (k=n+1;k>=1;k--)
		for (i=1;i<=16;i++)
			for (d=0;d<=n*16;d++)
				dp[k][i][d]=-INF;
	dp[n+1][getind(Sx,Sy)][0]=0;
	a[n+1].door[Sx][Sy]=1;
	for (k=n;k>=1;k--)
		for (i=1;i<=4;i++)
			for (j=1;j<=4;j++)
				if (a[k].door[i][j])
					for (d=1;d<=(n-k+1)*16;d++)
						for (kd=1;kd<=min(d,16);kd++)
							for (li=1;li<=4;li++)
								for (lj=1;lj<=4;lj++)
									if (a[k+1].door[li][lj])
										update(k,i,j,d,k+1,li,lj,d-kd);
	double ans=0;int ansp,ansd;
	for (i=1;i<=4;i++)
		for (j=1;j<=4;j++)
			for (d=1;d<=n*16;d++)
				if (double(dp[1][getind(i,j)][d])*1.0/d>ans)
				{
					ans=double(dp[1][getind(i,j)][d])*1.0/d;
					ansp=getind(i,j);ansd=d;
				}
	printf("%.4lf\n",ans);
	getans(1,ansp,ansd);
	printf("%d\n",int(Route.size()));
	cout<<Route<<endl;
	return 0;
}
