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
#include <cassert>
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

int n,t;
int a[5048];
int pos,rnk;
int cnt1,cnt2,cnt3;

LL fac[5048],inv[5048],finv[5048];
inline void init()
{
	fac[0]=inv[0]=finv[0]=fac[1]=inv[1]=finv[1]=1;
	for (register int i=2;i<=n;i++)
	{
		fac[i]=(fac[i-1]*i)%MOD;
		inv[i]=MOD-(inv[MOD%i]*(MOD/i))%MOD;
		finv[i]=(finv[i-1]*inv[i])%MOD;
	}
}

inline LL C(int x,int y)
{
	if (x<y || x<0) return 0ll;
	return ((fac[x]*finv[y])%MOD*finv[x-y])%MOD;
}

int main ()
{
	int i,j,m;n=getint();t=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	pos=getint();rnk=getint();
	for (i=1;i<=n;i++)
	{
		if (a[i]<a[pos]) cnt1++;
		if (a[i]==a[pos]) cnt2++;
		if (a[i]>a[pos]) cnt3++;
	}
	init();
	LL ans=0;
	for (i=0;i<=rnk-1;i++)
		for (j=rnk-i;i+j<=t;j++)
		{
			m=t-i-j;
			ans=(ans+((C(cnt1,i)*C(cnt2-1,j-1))%MOD*C(cnt3,m))%MOD)%MOD;
		}
	printf("%lld\n",ans);
	return 0;
}
