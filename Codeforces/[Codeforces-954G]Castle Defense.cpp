#pragma GCC optimize ("O3")
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

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,r;
LL k;
int a[500048];

namespace BIT
{
	LL c[500048],cc[500048];
	inline void clear() {for (int i=1;i<=n;i++) c[i]=cc[i];}
	inline void update(int x,LL delta)
	{
		while (x<=n)
		{
			c[x]+=delta;
			x+=LOWBIT(x);
		}
	}
	inline LL query(int x)
	{
		LL res=0;
		while (x)
		{
			res+=c[x];
			x-=LOWBIT(x);
		}
		return res;
	}
	inline void init()
	{
		int i,left,right;
		memset(c,0,sizeof(c));
		for (i=1;i<=n;i++)
		{
			left=max(1,i-r);right=min(n,i+r);
			update(left,a[i]);if (right<n) update(right+1,-a[i]);
		}
		for (i=1;i<=n;i++) cc[i]=c[i];
	}
}

bool check(LL minn)
{
	LL cnt=0;int i;BIT::clear();
	for (i=1;i<=n;i++)
	{
		LL cur=BIT::query(i);
		if (cur>=minn) continue;
		LL add=minn-cur;int pos=min(n,i+r);
		if (cnt+add>k) return false;
		int left=max(1,pos-r),right=min(n,pos+r);
		BIT::update(left,add);if (right<n) BIT::update(right+1,-add);
		cnt+=add;
	}
	return cnt<=k;
}

int main ()
{
	//freopen ("test.in","r",stdin);
	int i;
	n=getint();r=getint();k=getLL();
	for (i=1;i<=n;i++) a[i]=getint();
	BIT::init();BIT::clear();
	LL l=0,ri=0,mid,ans=0;
	for (i=1;i<=n;i++) ri=max(ri,BIT::query(i));
	if (r==0) ri+=k/n+20; else ri+=k;
	while (l<=ri)
	{
		mid=(l+ri)>>1;
		if (check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
			ri=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
