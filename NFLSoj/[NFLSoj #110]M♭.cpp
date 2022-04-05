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

int dp[4148][4148];
char ss[5048],s[5048];int slen,len;

int main ()
{
	int i,j,ca,clen,left,right;ca=getint();
	while (ca--)
	{
		scanf("%s%s",ss+1,s+1);slen=strlen(ss+1);len=strlen(s+1);
		for (i=1;i<=slen;i++)
			for (j=i;j<=slen;j++)
				dp[i][j]=0;
		for (i=1;i<=slen;i++)
			if (ss[i]==s[1]) dp[i][i]=1;
		for (clen=2;clen<=slen;clen++)
			for (i=1;i<=slen-clen+1;i++)
			{
				left=i;right=i+clen-1;
				dp[left][right]=max(dp[left+1][right],dp[left][right-1]);
				if (dp[left][right]==len) continue;
				if (ss[left]==s[dp[left+1][right]+1]) dp[left][right]=max(dp[left][right],dp[left+1][right]+1);
				if (ss[right]==s[dp[left][right-1]+1]) dp[left][right]=max(dp[left][right],dp[left][right-1]+1);
			}
		int ans=0;
		for (i=1;i<=slen;i++)
			for (j=i;j<=slen;j++)
				if (dp[i][j]==len) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
