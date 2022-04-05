#include <bits/stdc++.h>
#define INF 2e9
using namespace std;

int dp[2048][2048];
int n;

bool type[4048];
int a[4048];

//1=black,2=white
int pos1[2048],pos2[2048];
set<int> ws1,ws2,bs1,bs2;
int bmark[4048][2048],smark[4048][2048];
int bsmall[4048][2048],ssmall[4048][2048];

inline int calc(int pos,int p1,int p2)
{
	return pos-bmark[pos][p1]-smark[pos][p2]-1;
}

int main ()
{
	int i,j;
	scanf("%d",&n);string ss;
	for (i=1;i<=n*2;i++)
	{
		cin>>ss;
		scanf("%d",&a[i]);
		if (ss=="B") type[i]=false; else type[i]=true;
		if (!type[i]) pos1[a[i]]=i; else pos2[a[i]]=i;
	}
	for (i=1;i<=n*2;i++)
		for (j=1;j<=i-1;j++)
			if (!type[j]) bmark[i][a[j]]++; else smark[i][a[j]]++;
	for (i=1;i<=n*2;i++)
		for (j=2;j<=n;j++)
		{
			bmark[i][j]+=bmark[i][j-1];
		}
	for (i=1;i<=n*2;i++)
		for (j=2;j<=n;j++)
			smark[i][j]+=smark[i][j-1];
	for (i=0;i<=n;i++)
		for (j=0;j<=n;j++)
			dp[i][j]=INF;
	dp[0][0]=0;
	for (i=0;i<=n;i++)
	{
		for (j=0;j<=n;j++)
		{
			if (!i && !j) continue;
			if (i) dp[i][j]=min(dp[i][j],dp[i-1][j]+calc(pos1[i],i-1,j));
			if (j) dp[i][j]=min(dp[i][j],dp[i][j-1]+calc(pos2[j],i,j-1));
		}
	}
	printf("%d\n",dp[n][n]);
	return 0;
}
