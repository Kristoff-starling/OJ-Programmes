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

const int MOD=1e9+9;
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

int n,m;
pair<int,short> dp[148][30048];int pre[148][30048];
int cost[148],val[148];
char name[148][48];

inline void getans(int i,int j)
{
	if (i==0) return;
	getans(i-1,pre[i][j]);
	int num=(j-pre[i][j])/val[i];
	if (num) printf("%s %d\n",name[i]+1,num);
}

inline void update(int v1,int v2,int x1,int y1,int x2,int y2)
{
	if (v1<v2)
	{
		dp[x2][y2].x=v1;
		if (x1!=x2) {dp[x2][y2].y=dp[x1][y1].y;pre[x2][y2]=y1;}
		else
		{
			if (pre[x1][y1]!=y1) dp[x2][y2].y=dp[x1][y1].y; else dp[x2][y2].y=dp[x1][y1].y+1;
			pre[x2][y2]=pre[x1][y1];
		}
		return;
	}
	if (v1==v2)
	{
		if (x1!=x2 && dp[x1][y1].y>=dp[x2][y2].y)
		{
			dp[x2][y2].y=dp[x1][y1].y;
			pre[x2][y2]=y1;
		}
		if (x1==x2)
		{
			int vv=dp[x1][y1].y;if (pre[x1][y1]==y1) vv++;
			if (vv>dp[x2][y2].y)
			{
				dp[x2][y2].y=vv;
				pre[x2][y2]=pre[x1][y1];
			}
		}
	}
}

int main ()
{
	int i,j;double tmp;n=getint();m=getint();
	for (i=1;i<=n;i++)
	{
		scanf("%s%d%lf",name[i]+1,&cost[i],&tmp);
		val[i]=int(tmp*1000+0.5);
	}
	for (i=0;i<=n;i++)
		for (j=0;j<=m*1000+10000;j++)
			dp[i][j]=mp(INF,-INF);
	dp[0][0]=mp(0,0);int ans=INF,ansv=-INF,ansx,ansy;
	for (i=1;i<=n;i++)
		for (j=0;j<=m*1000+10000;j++)
		{
			update(dp[i-1][j].x,dp[i][j].x,i-1,j,i,j);
			if (j-val[i]>=0) update(dp[i][j-val[i]].x+cost[i],dp[i][j].x,i,j-val[i],i,j);
		}
	for (j=m*1000;j<=m*1000+10000;j++)
		if (dp[n][j].x<ans || (dp[n][j].x==ans && dp[n][j].y>ansv))
			{ans=dp[n][j].x;ansv=dp[n][j].y;ansx=n;ansy=j;}
	printf("%d\n",ans);
	getans(ansx,ansy);
	return 0;
}
