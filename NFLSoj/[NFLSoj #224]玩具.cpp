#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <list>
#include <stack>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int MOD=998244353;
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

inline LL getLL()
{
	char ch;LL res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,p;

inline LL quick_pow(LL x,LL y)
{
	LL res=1;x%=p;
	while (y)
	{
		if (y&1) res=(res*x)%p,y--;
		x=(x*x)%p;y>>=1;
	}
	return res;
}

inline LL mod(LL x) {while (x>=p) x-=p;while (x<0) x+=p;return x;}
inline LL sub(LL x) {if (x<0) x+=p;return x;}

const int MAXN=200;

LL DP1[MAXN+48][MAXN+48],DP2[MAXN+48][MAXN+48],DP3[MAXN+48][MAXN+48];
LL Res[MAXN+48];

LL inv[MAXN+48];
inline void init_inv()
{
	int i;inv[1]=1;
	for (i=2;i<=n;i++) inv[i]=quick_pow(i,p-2);
}

inline LL Solve1(int i,int j);
inline LL Solve2(int i,int j)
{
	if (j<0) return 0;
	if (i==0) return 1;
	if (DP2[i][j]!=-1) return DP2[i][j];
	int k;DP2[i][j]=0;
	for (k=1;k<=i;k++)
		DP2[i][j]=mod(DP2[i][j]+((Solve1(k,j)*Solve2(i-k,j))%p*DP3[i][k])%p);
	return DP2[i][j];
}

inline LL Solve1(int i,int j)
{
	if (DP1[i][j]!=-1) return DP1[i][j];
	DP1[i][j]=Solve2(i-1,j-1);
	return DP1[i][j];
}

int main ()
{
	//freopen ("toy.in","r",stdin);
	//freopen ("toy.out","w",stdout);
	n=getint();p=getint();int i,j;
	if (n==1)
	{
		printf("0\n");
		return 0;
	}
	init_inv();
	DP3[1][1]=1;
	for (i=2;i<=n;i++)
		for (j=1;j<=i;j++)
			DP3[i][j]=(((DP3[i-1][j-1]*(long long)(j-1))%p*inv[i])%p+((DP3[i-1][j]*(long long)(i-j))%p*inv[i])%p)%p;
	for (i=0;i<=n;i++)
		for (j=0;j<=n;j++)
			DP1[i][j]=DP2[i][j]=-1;
	for (i=2;i<=n;i++) Res[i]=Solve1(n,i);
	Res[1]=0;LL Ans=0;
	for (i=2;i<=n;i++) Ans=mod(Ans+(mod(Res[i]-Res[i-1])*i)%p);
	printf("%lld\n",sub(Ans-1));
	return 0;
}