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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,k;
string s[2048];
int cntCh[27];
string ans;
bitset<1000048> can[2048];
Pair dp[2][1000048];

int main ()
{
	int i,j,cnt,ncnt,cur,minCh,minSt;
	n=getint();k=getint();
	for (i=1;i<=n;i++)
	{
		cin>>s[i];
		for (j=0;j<int(s[i].size());j++)
			cntCh[s[i][j]-'a'+1]++;
	}
	int fcnt=0;
	for (i=1;i<=26;i++)
		if (cntCh[i]) fcnt++;
	if (fcnt==1)
	{
		for (i=1;i<=26;i++)
			if (cntCh[i])
			{
				ans=string(k,'a'+i-1);
				cout<<ans<<endl;
				return 0;
			}
	}
	can[n+1][0]=1;
	for (i=n;i>=1;i--)
		can[i]=can[i+1]|(can[i+1]<<(int(s[i].size())));
	for (i=1;i<=n;i++)
		if (can[i+1][k-int(s[i].size())]) dp[0][++cnt]=mp(i,0);
	cur=0;
	for (i=1;i<=k;i++)
	{
		cnt=min(cnt,10000);ncnt=0;
		minCh=26;
		for (j=1;j<=cnt;j++)
			minCh=min(minCh,s[dp[cur][j].x][dp[cur][j].y]-'a'+1);
		ans+=string(1,'a'+minCh-1);
		minSt=INF;
		for (j=1;j<=cnt;j++)
			if (s[dp[cur][j].x][dp[cur][j].y]-'a'+1==minCh)
			{
				if (dp[cur][j].y==int(s[dp[cur][j].x].size())-1)
					minSt=min(minSt,dp[cur][j].x+1);
				else
					dp[cur^1][++ncnt]=mp(dp[cur][j].x,dp[cur][j].y+1);
			}
		for (j=minSt;j<=n;j++)
			if (k-i-int(s[j].size())>=0 && can[j+1][k-i-int(s[j].size())])
				dp[cur^1][++ncnt]=mp(j,0);
		cnt=ncnt;cur^=1;
	}
	cout<<ans<<endl;
	return 0;
}	