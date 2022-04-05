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

const int MOD=999911659;
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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL n,g;
LL M[]={2,3,4679,35617};
LL m[5],invm[5];
LL A[5];
int lim;

LL fac[4][100048],inv[4][100048],finv[4][100048];
inline void sieve()
{
	int i,j;
	for (i=0;i<=3;i++)
		fac[i][0]=fac[i][1]=inv[i][0]=inv[i][1]=finv[i][0]=finv[i][1]=1;
	for (j=0;j<=3;j++)
		for (i=2;i<=50000;i++)
		{
			fac[j][i]=(fac[j][i-1]*i)%M[j];
			inv[j][i]=M[j]-((long long)(M[j]/i)*inv[j][M[j]%i])%M[j];
			finv[j][i]=(finv[j][i-1]*inv[j][i])%M[j];
		}
}

inline LL C(int type,LL x,LL y)
{
	if (x<y) return 0;
	LL res=fac[type][x];res=(res*finv[type][y])%M[type];res=(res*finv[type][x-y])%M[type];
	return res;
}

inline LL Lucas(int type,LL x,LL y)
{
	if (x<y) return 0;
	if (x<M[type]) return C(type,x,y);
	return (C(type,x%M[type],y%M[type])*Lucas(type,x/M[type],y/M[type]))%M[type];
}

inline LL solve(LL x,LL y)
{
	int i;
	for (i=0;i<=3;i++) A[i]=Lucas(i,x,y);
	LL res=0;
	for (i=0;i<=3;i++)
		res=(res+((A[i]*m[i])%(MOD-1)*invm[i])%(MOD-1))%(MOD-1);
	return res;
}

inline LL quick_pow(LL x,LL y,LL MO)
{
	LL res=1;x%=MO;
	while (y)
	{
		if (y&1) res=(res*x)%MO,y--;
		x=(x*x)%MO;y>>=1;
	}
	return res;
}

int main ()
{
	n=getLL();g=getLL();
	if (g%MOD==0) {puts("0");return 0;}
	lim=int(sqrt(n));int i;sieve();
	for (i=0;i<=3;i++) m[i]=(MOD-1)/M[i],invm[i]=quick_pow(m[i],M[i]-2,M[i]);
	LL P=0;
	for (i=1;i<=lim;i++)
		if (n%i==0)
		{
			P=(P+solve(n,i))%(MOD-1);
			if (n/i!=i) P=(P+solve(n,n/i))%(MOD-1);
		}
	printf("%lld\n",quick_pow(g,P,MOD));
	return 0;
}
