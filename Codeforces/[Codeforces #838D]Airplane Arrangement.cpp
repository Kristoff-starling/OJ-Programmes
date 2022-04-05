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

int m,n;

inline LL quick_pow(LL x,LL y)
{
	LL res=1;
	while (y)
	{
		if (y&1) res=(res*x)%MOD,y--;
		x=(x*x)%MOD;y>>=1;
	}
	return res;
}

int main ()
{
	n=getint();m=getint();
	printf("%lld\n",((quick_pow(2*n+2,m)*(n-m+1))%MOD*quick_pow(n+1,MOD-2))%MOD);
	return 0;
}
