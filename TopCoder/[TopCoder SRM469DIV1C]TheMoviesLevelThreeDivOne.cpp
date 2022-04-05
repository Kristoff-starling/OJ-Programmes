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
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL dp[2][2048][2048];
int a[148],b[148];

class TheMoviesLevelThreeDivOne
{
	int n;
	const int MMAX=1000;
	inline LL calc()
	{
		int cur=0,nxt=1,i,j,k;
		memset(dp[0],0,sizeof(dp[0]));
		dp[0][MMAX][MMAX]=1;
		for (i=1;i<=n;i++)
		{
			memset(dp[nxt],0,sizeof(dp[nxt]));
			for (j=MMAX-20*i;j<=MMAX;j++)
				for (k=MMAX-20*i;k<=MMAX+20*i;k++)
					if (dp[cur][j][k])
					{
						//add i to y
						dp[nxt][min(MMAX,j+b[i])][k+b[i]]+=dp[cur][j][k];
						//add i to x
						dp[nxt][min(j,k-a[i])][k+b[i]-a[i]]+=dp[cur][j][k];
					}
			swap(cur,nxt);
		}
		LL res=0;
		for (j=MMAX-20*n;j<=MMAX-1;j++)
			for (k=MMAX-20*n;k<=MMAX+20*n;k++)
				res+=dp[cur][j][k];
		return res;
	}					
	public:
		inline LL find(vector<int> A,vector<int> B)
		{
			n=int(A.size());int i;
			for (i=1;i<=n;i++) a[i]=A[i-1],b[i]=B[i-1];
			LL res=calc();
			for (i=1;i<=n;i++) swap(a[i],b[i]);
			res+=calc();
			return (1ll<<n)-res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	TheMoviesLevelThreeDivOne A;
	int nn;vector<int> aa,bb;
	while (scanf("%d",&nn)!=EOF)
	{
		register int i,x;
		aa.clear();bb.clear();
		for (i=1;i<=nn;i++) x=getint(),aa.pb(x);
		for (i=1;i<=nn;i++) x=getint(),bb.pb(x);
		printf("%lld\n",A.find(aa,bb));
	}
	return 0;
}
*/
