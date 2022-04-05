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

int n,m,sx,sy,K;
char a[248][248];
int dp[248][248][248];
int t[248],dir[248];

Pair q[100048];int head,tail;

int main ()
{
	int i,j,k,x,y;
	n=getint();m=getint();sx=getint();sy=getint();K=getint();
	for (i=1;i<=n;i++) scanf("%s",a[i]+1);
	for (i=1;i<=K;i++)
	{
		x=getint();y=getint();dir[i]=getint();
		t[i]=y-x+1;
	}
	for (k=0;k<=K;k++)
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				dp[k][i][j]=-INF;
	dp[0][sx][sy]=0;
	for (k=1;k<=K;k++)
	{
		if (dir[k]==1)
			for (j=1;j<=m;j++)
			{
				head=1;tail=0;
				for (i=n;i>=1;i--)
				{
					if (a[i][j]=='x') {head=1;tail=0;continue;}
					while (head<=tail && q[head].y-i>t[k]) head++;
					while (head<=tail && q[tail].x+q[tail].y-i<=dp[k-1][i][j]) tail--;
					q[++tail]=mp(dp[k-1][i][j],i);
					dp[k][i][j]=q[head].x+q[head].y-i;
				}
			}
		if (dir[k]==2)
			for (j=1;j<=m;j++)
			{
				head=1;tail=0;
				for (i=1;i<=n;i++)
				{
					if (a[i][j]=='x') {head=1;tail=0;continue;}
					while (head<=tail && i-q[head].y>t[k]) head++;
					while (head<=tail && q[tail].x+i-q[tail].y<=dp[k-1][i][j]) tail--;
					q[++tail]=mp(dp[k-1][i][j],i);
					dp[k][i][j]=q[head].x+i-q[head].y;
				}
			}
		if (dir[k]==3)
			for (i=1;i<=n;i++)
			{
				head=1;tail=0;
				for (j=m;j>=1;j--)
				{
					if (a[i][j]=='x') {head=1;tail=0;continue;}
					while (head<=tail && q[head].y-j>t[k]) head++;
					while (head<=tail && q[tail].x+q[tail].y-j<=dp[k-1][i][j]) tail--;
					q[++tail]=mp(dp[k-1][i][j],j);
					dp[k][i][j]=q[head].x+q[head].y-j;
				}
			}
		if (dir[k]==4)
			for (i=1;i<=n;i++)
			{
				head=1;tail=0;
				for (j=1;j<=m;j++)
				{
					if (a[i][j]=='x') {head=1;tail=0;continue;}
					while (head<=tail && j-q[head].y>t[k]) head++;
					while (head<=tail && q[tail].x+j-q[tail].y<=dp[k-1][i][j]) tail--;
					q[++tail]=mp(dp[k-1][i][j],j);
					dp[k][i][j]=q[head].x+j-q[head].y;
				}
			}
	}
	int ans=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			ans=max(ans,dp[K][i][j]);
	printf("%d\n",ans);
	return 0;
}
