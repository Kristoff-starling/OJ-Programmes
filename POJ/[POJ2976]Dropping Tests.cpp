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
#define DEBUG(...)
using namespace std;

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;int res;bool f;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n,k;
double l,r,mid;

struct node
{
	double a,b;
	inline bool operator < (const node &x) const {return a-mid*b>x.a-mid*x.b;}
}a[10048];

inline bool check()
{
	int i;
	sort(a+1,a+n+1);
	double A=0,B=0;
	for (i=1;i<=n-k;i++) A+=a[i].a,B+=a[i].b;
	if (A/B>=mid) return true; else return false;
}

int main ()
{
	int i;double ans;
	while (scanf("%d%d",&n,&k) && !(!n && !k))
	{
		for (i=1;i<=n;i++) a[i].a=getint();
		for (i=1;i<=n;i++) a[i].b=getint();
		l=0;r=1;ans=0;
		while (r-l>1e-6)
		{
			mid=(l+r)/2;
			if (check()) ans=mid,l=mid; else r=mid;
		}
		printf("%d\n",int(ans*100+0.5));
	}
	return 0;
}
