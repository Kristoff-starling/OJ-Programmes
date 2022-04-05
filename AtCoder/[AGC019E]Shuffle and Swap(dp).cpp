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

const int MOD=998244353;
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

LL dp[2][100048];
int inv[200048];
LL finv[200048],fac[200048];
int n;
int a[100048],b[100048];
char s[100048];
int e,m;

inline void init_inv()
{
	int i;
	fac[0]=fac[1]=inv[0]=inv[1]=finv[0]=finv[1]=1;
	for (i=2;i<=n;i++)
	{
		fac[i]=(fac[i-1]*i)%MOD;
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
}

int main ()
{
	int i,j,k,cur,nxt;
	scanf("%s",s+1);n=strlen(s+1);
	for (i=1;i<=n;i++) a[i]=s[i]-'0';
	scanf("%s",s+1);
	for (i=1;i<=n;i++) b[i]=s[i]-'0';
	init_inv();
	e=m=0;
	for (i=1;i<=n;i++)
	{
		if (a[i]==1 && b[i]==0) e++;
		if (a[i]==1 && b[i]==1) m++;
	}
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for (i=1,cur=0,nxt=1;i<=e;i++,cur^=1,nxt^=1)
	{
		for (j=0;j<=m;j++) dp[nxt][j]=0;
		for (j=0;j<=m;j++)
			for (k=0;k<=j;k++)
				dp[nxt][j]=(dp[nxt][j]+dp[cur][k]*finv[j-k+1])%MOD;
	}
	LL ans=0;
	for (i=0;i<=m;i++) ans=(ans+dp[cur][i])%MOD;
	ans=ans*fac[e]%MOD*fac[m]%MOD*fac[e+m]%MOD;
	printf("%lld\n",ans);
	return 0;
}
