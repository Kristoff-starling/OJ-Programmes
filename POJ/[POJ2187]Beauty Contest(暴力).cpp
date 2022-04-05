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
#define Pair pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const LL MOD=1e9+7;
const LL LINF=2e16;
const LL INF=2e9;
const LL magic=348;
const double eps=1e-10;

inline LL getint()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n;
Pair a[50048];
Pair convex[50048];int ctot;
Pair s[50048];int stot;

inline double calc_k(Pair x,Pair y)
{
	if (x.x==y.x) if (x.y<y.y) return INF; else return -INF;
	return double(x.y-y.y)/(x.x-y.x);
}

inline int calc_sdist(Pair x,Pair y) {return (x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);}

inline void getconvex()
{
	int i;
	//up
	stot=1;s[1]=a[1];
	for (i=2;i<=n;i++)
	{
		while(stot>=2 && calc_k(s[stot-1],s[stot])-calc_k(s[stot],a[i])<eps) stot--;
		s[++stot]=a[i];
	}
	for (i=1;i<=stot;i++) convex[++ctot]=s[i];
	//down
	stot=1;s[1]=a[1];
	for (i=2;i<=n;i++)
	{
		while (stot>=2 && calc_k(s[stot-1],s[stot])-calc_k(s[stot],a[i])>-eps) stot--;
		s[++stot]=a[i];
	}
	for (i=1;i<=stot;i++) convex[++ctot]=s[i];
}

int main ()
{
	int i,j;
	n=getint();
	for (i=1;i<=n;i++) a[i].x=getint(),a[i].y=getint();
	sort(a+1,a+n+1);
	getconvex();
	int ans=0;
	for (i=1;i<=ctot-1;i++)
		for (j=i+1;j<=ctot;j++)
			ans=max(ans,calc_sdist(convex[i],convex[j]));
	printf("%d\n",ans);
	return 0;
}
