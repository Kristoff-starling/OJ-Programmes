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
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=1e9;
const int magic=3048;
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
int ga[58][58];
int g1,g2,s1,s2;
int fastest[58],slowest[58];
bool G[58],S[58],B[58];
LL dp[58][58][58];

LL solve(int goldline,int bronzeline,int silverup,int silverdown)
{
	memset(G,false,sizeof(G));
	memset(S,false,sizeof(S));
	memset(B,false,sizeof(B));
	int i,j,k;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (i!=j)
			{
				if (ga[i][j]<=goldline) G[i]=true;
				if (ga[i][j]>=bronzeline) B[i]=true;
				if (ga[i][j]>silverup && ga[i][j]<silverdown) S[i]=true;
			}
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for (i=1;i<=n;i++)
		for (j=0;j<=i;j++)
			for (k=0;j+k<=i;k++)
			{
				if (G[i]) dp[i][j][k]+=dp[i-1][j-1][k];
				if (S[i]) dp[i][j][k]+=dp[i-1][j][k-1];
				if (B[i]) dp[i][j][k]+=dp[i-1][j][k];
			}
	LL res=0;
	for (i=g1;i<=g2;i++)
		for (j=s1;j<=s2;j++)
			res+=dp[n][i][j];
	return res;
}

void floyd()
{
	int i,j,k;
	for (k=1;k<=n;k++)
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				if (k!=i && k!=j && i!=j && ga[i][k]+ga[k][j]<ga[i][j])
					ga[i][j]=ga[i][k]+ga[k][j];
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (ga[i][j]<INF) ga[i][j]=ga[i][j]*n+i;
}

int main ()
{
	int i,j,x,y,c;
	n=getint();m=getint();
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			ga[i][j]=(i==j?0:INF);
	for (i=1;i<=m;i++)
	{
		x=getint();y=getint();c=getint();
		ga[x][y]=c;ga[y][x]=c;
	}
	g1=getint();g2=getint();s1=getint();s2=getint();
	floyd();
	for (i=1;i<=n;i++)
	{
		int maxlen=-INF,minlen=INF;
		for (j=1;j<=n;j++)
			if (i!=j) maxlen=max(maxlen,ga[i][j]),minlen=min(minlen,ga[i][j]);
		fastest[i]=minlen;slowest[i]=maxlen;
	}
	LL ans=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			ans=ans+solve(fastest[i],slowest[j],fastest[i],slowest[j])-solve(fastest[i]-1,slowest[j],fastest[i],slowest[j])-solve(fastest[i],slowest[j]+1,fastest[i],slowest[j])+solve(fastest[i]-1,slowest[j]+1,fastest[i],slowest[j]);
	printf("%lld\n",ans);
	return 0;
}
