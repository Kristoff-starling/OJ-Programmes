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

struct Bigint
{
	const int lim=100000000;
	LL b[148],len;
	inline void clear() {memset(b,0,sizeof(b));len=1;}
	inline void Set(LL x)
	{
		clear();len=0;
		if (!x) {len=1;return;}
		while (x) b[++len]=x%lim,x/=lim;
	}
	inline Bigint operator = (Bigint other)
	{
		len=other.len;
		for (register int i=1;i<=len;i++) b[i]=other.b[i];
		return (*this);
	}
	inline Bigint operator + (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=max(len,other.len);i++)
		{
			res.b[i]+=b[i]+other.b[i];
			res.b[i+1]+=res.b[i]/lim;res.b[i]%=lim;
		}
		res.len=max(len,other.len);
		if (res.b[res.len+1]) res.len++;
		return res;
	}
	inline Bigint operator * (Bigint other)
	{
		Bigint res;res.clear();
		for (register int i=1;i<=len;i++)
			for (register int j=1;j<=other.len;j++)
			{
				res.b[i+j-1]+=b[i]*other.b[j];
				res.b[i+j]+=res.b[i+j-1]/lim;res.b[i+j-1]%=lim;
			}
		for (register int i=1;i<=len+other.len-1;i++) res.b[i+1]+=res.b[i]/lim,res.b[i]%=lim;
		res.len=len+other.len;
		while (res.len && !res.b[res.len]) res.len--;
		if (!res.len) res.len=1;
		return res;
	}
	inline int getd(int x)
	{
		if (!x) return 1;
		int res=0;
		while (x) res++,x/=10;
		return res;
	}
	inline void print()
	{
		for (register int i=len;i>=1;i--)
		{
			if (i!=len)
			{
				int Le=8-getd(b[i]);
				while (Le--) printf("0");
			}
			printf("%lld",b[i]);
		}
		printf("\n");
	}
};

Bigint c[48][48];
int N,M,K;
Bigint dp[48][48];
Bigint trans[48][48];

inline void init_trans()
{
	int i,j,k;
	for (i=0;i<=N;i++) // 0 num 1
		for (j=0;j<=N;j++) //0 num 2
		{
			trans[i][j].Set(0);
			for (k=0;k<=min(K,min(N-j,i));k++)
			{
				if (N-j-k>N-i) continue;
				trans[i][j]=trans[i][j]+c[i][k]*c[N-i][N-j-k];
			}
		}
}

inline void init_c()
{
	c[0][0].Set(1);
	for (register int i=1;i<=N;i++)
	{
		c[i][0].Set(1);c[i][i].Set(1);
		for (register int j=1;j<=i-1;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	}
}

int main ()
{
	int i,j,k,m;
	N=getint();M=getint();K=getint();
	init_c();init_trans();
	for (i=0;i<=M;i++)
		for (j=0;j<=N;j++)
			dp[i][j].Set(0);
	dp[0][0].Set(1);
	for (i=0;i<=M-1;i++)
		for (j=0;j<=N;j++) //num of 0
			if (dp[i][j].len>1 || dp[i][j].b[1])
				for (k=0;k<=N;k++)
					dp[i+1][k]=dp[i+1][k]+dp[i][j]*trans[j][k];
	Bigint ans;ans.Set(0);
	for (j=0;j<=N;j++) ans=ans+dp[M][j];
	ans.print();
	return 0;
}
