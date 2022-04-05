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

char s[300048];
LL dp[300048][5][2][2];
//i: current pos
//j: suffix zero num(<3)
//k: the odd's zero / the even's zero
//m: whether there exists an odd's zero
LL pros[300048];

inline int calc(int x)
{
	while (x>2) x-=2;
	return x;
}

int main ()
{
	int i,j,k,m,len;LL ans=0;
	scanf("%s",s+1);len=strlen(s+1);
	pros[len+1]=1;
	for (i=len;i;i--) pros[i]=(pros[i+1]*(s[i]=='?'?2:1))%MOD;
	dp[0][0][1][0]=1;
	for (i=0;i<=len-1;i++)
		for (j=0;j<=2;j++)
			for (k=0;k<=1;k++)
				for (m=0;m<=1;m++)
					if (dp[i][j][k][m])
					{
						if (s[i+1]!='1')
							dp[i+1][calc(j+1)][k][m]+=dp[i][j][k][m]%=MOD;
						if (s[i+1]!='0')
						{
							if (j==1)
							{
								dp[i+1][0][k][m]+=dp[i][j][k][m]%=MOD;
								continue;
							}
							if (j==2)
							{
								dp[i+1][0][k^1][m]+=dp[i][j][k][m]%=MOD;
								continue;
							}
							if (m==1 && !k) {ans=(ans+(dp[i][j][k][m]*pros[i+2])%MOD)%MOD;continue;}
							if (m==0 && k) {dp[i+1][0][k^1][1]+=dp[i][j][k][m]%=MOD;continue;}
							dp[i+1][0][k^1][m]+=dp[i][j][k][m]%=MOD;
						}
					}
	ans=(ans+dp[len][0][0][1])%MOD;
	printf("%lld\n",ans);
	return 0;
}
