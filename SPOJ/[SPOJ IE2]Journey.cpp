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

const int MOD=1e9+9;
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

int n,e,k,d;
int ga[48][48];

inline LL mod(LL x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}
inline LL mul(LL x) {return x%MOD;}

struct Matrix
{
	LL b[48][48];
	inline void init_I() {for (register int i=1;i<=n;i++) b[i][i]=1;}
	inline void clear() {memset(b,0,sizeof(b));}
	inline Matrix operator + (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=n;j++)
				res.b[i][j]=mod(b[i][j]+ma.b[i][j]);
		return res;
	}
	inline Matrix operator * (Matrix ma)
	{
		Matrix res;res.clear();
		for (register int i=1;i<=n;i++)
			for (register int j=1;j<=n;j++)
				for (register int k=1;k<=n;k++)
					res.b[i][j]=mod(res.b[i][j]+mul(b[i][k]*ma.b[k][j]));
		return res;
	}
}trans,sta;

inline Matrix quick_pow(Matrix ma,LL y)
{
	Matrix res;res.clear();res.init_I();
	while (y)
	{
		if (y&1) res=res*ma,y--;
		ma=ma*ma;y>>=1;
	}
	return res;
}

int main ()
{
	int i,j,x,y,Mask;
	n=getint();e=getint();k=getint();d=getint();
	for (i=1;i<=e;i++)
	{
		x=getint();y=getint();
		ga[x][y]=ga[y][x]=1;
	}
	LL ans=0;
	for (Mask=0;Mask<=(1<<k)-1;Mask++)
	{
		trans.clear();
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				trans.b[i][j]=(ga[i][j] && !(Mask&(1<<(i-1))) && !(Mask&(1<<(j-1))));
		sta.clear();
		for (i=1;i<=n;i++) sta.b[1][i]=(!(Mask&(1<<(i-1))));
		sta=sta*quick_pow(trans,d-1);
		int sg=(__builtin_popcount(Mask)%2==0)?1:-1;
		for (i=1;i<=n;i++) ans=mod(ans+mul(sta.b[1][i]*sg));
	}
	printf("%lld\n",ans);
	return 0;
}
