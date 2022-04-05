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
#define ull unsigned long long
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
const LL LINF=2e18;
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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL dp[70][90048];
LL n,m;

inline void init()
{
	int i,j;
	memset(dp,0,sizeof(dp));
	for (i=1;i<=90000;i++) dp[3][i]=(long long)i*((long long)i*i+5)/6;
	for (i=4;i<=68;i++)
		for (j=1;j<=90000;j++)
		{
			if (dp[i-1][j-1]>=LINF || dp[i][j-1]>=LINF) {dp[i][j]=LINF;continue;}
			if (dp[i-1][j-1]+dp[i][j-1]+1>=LINF) dp[i][j]=LINF; else dp[i][j]=dp[i-1][j-1]+dp[i][j-1]+1;
		}
}

inline bool Larger(ull x,ull y,ull cmp)
{
	ull res=0;
	while (y)
	{
		if (y&1)
		{
			res=res+x;
			if (res>cmp) return true;
			y--;
		}
		x=x+x;
		if (x>cmp && y) return true;
		y>>=1;
	}
	return false;
}

inline ull calc_3(ull x)
{
	ull X=x*x+5;
	if (Larger(X,x,6e18)) return LINF;
	return X*x/6;
}

int main ()
{
	//freopen ("table2.out","w",stdout);
	init();
	/*for (n=1;n<=1000;n++)
	{
		for (m=1;m<=20;m++)
	{
		m=min(m,(long long)68);int i;
		for (i=1;i<=68;i++)
			if (dp[m][i]>=n) break;
		printf("%d ",i);
	}
		cout<<endl;
	}*/
	//cout<<dp2[10][1000]<<endl;
	while (scanf("%lld%lld",&m,&n) && m && n)
	{
		m=min(m,(long long)68);
		if (m==1) {printf("%lld\n",n);continue;}
		if (m==2)
		{
			LL res=(long long)sqrt(n*2);
			while ((res+1)*res/2<n) res++;
			printf("%lld\n",res);
			continue;
		}
		if (m==3)
		{
			int l=1,r=4000000,mid,ans;
			while (l<=r)
			{
				mid=(l+r)>>1;
				if (calc_3(mid)>=n) ans=mid,r=mid-1; else l=mid+1;
			}
			printf("%d\n",ans);
			continue;
		}
		int l=1,r=90000,mid,ans;
		while (l<=r)
		{
			mid=(l+r)>>1;
			if (dp[m][mid]>=n) ans=mid,r=mid-1; else l=mid+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
