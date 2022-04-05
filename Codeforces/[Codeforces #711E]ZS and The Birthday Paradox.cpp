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

const int MOD=1e6+3;
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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL n,k;
LL Gcd,Inv;
LL Up,Down;

inline LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

inline void calc_gcd()
{
	Gcd=1;Inv=quick_pow(2,MOD-2);
	for (register LL i=2;i<=k-1;i<<=1)
		Gcd=(Gcd*quick_pow(Inv,(k-1)/i))%MOD;
}

namespace brute
{
	inline void solve()
	{
		LL i,cnt=0,starter=quick_pow(2,n);
		for (i=(starter-1+MOD)%MOD,Up=1,cnt=1;cnt<=k-1;i=(i-1+MOD)%MOD,cnt++) Up=(Up*i)%MOD;
		Up=(Up*Gcd)%MOD;
		Down=quick_pow(quick_pow(2,n),k-1);Down=(Down*Gcd)%MOD;
		Up=(Down-Up+MOD)%MOD;
		printf("%lld %lld\n",Up,Down);
	}
}

namespace big
{
	inline void solve()
	{
		Down=quick_pow(quick_pow(2,n),k-1);Down=(Down*Gcd)%MOD;
		printf("%lld %lld\n",Down,Down);
	}
}

int main ()
{
	n=getLL();k=getLL();
	if (n<=63 && (1ll<<n)<k) {printf("1 1\n");return 0;}
	calc_gcd();
	if (k<=1e6+48) {brute::solve();return 0;}
	big::solve();return 0;
}
