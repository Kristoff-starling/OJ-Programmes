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

LL n,p,k,r;

struct Matrix
{
	LL b[60][60];
	inline void Clear ()
	{
		int i,j;
		for (i=0;i<=k-1;i++)
			for (j=0;j<=k-1;j++)
				b[i][j]=0;
	}
	inline void memset_I()
	{
		int i;
		for (i=0;i<=k-1;i++) b[i][i]=1;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.Clear();
		int i,j,m;
		for (i=0;i<=k-1;i++)
			for (j=0;j<=k-1;j++)
				for (m=0;m<=k-1;m++)
					res.b[i][j]=(res.b[i][j]+(b[i][m]*ma.b[m][j])%p)%p;
		return res;
	}
}sMa,Ma;

inline Matrix quick_pow(Matrix ma,LL y)
{
	Matrix res;res.Clear();res.memset_I();
	while (y)
	{
		if (y&1)
		{
			res=res*ma;
			y--;
		}
		ma=ma*ma;
		y>>=1;
	}
	return res;
}

int main ()
{
	n=getint();p=getint();k=getint();r=getint();
	n*=k;
	sMa.Clear();sMa.b[0][1%k]++;sMa.b[0][0]++;
	int j;
	Ma.Clear();
	for (j=0;j<=k-1;j++) Ma.b[j][j]++,Ma.b[(j-1+k)%k][j]++;
	sMa=sMa*quick_pow(Ma,n-1);
	printf("%lld\n",sMa.b[0][r]);
	return 0;
}