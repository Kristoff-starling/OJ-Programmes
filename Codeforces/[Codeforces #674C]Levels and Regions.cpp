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
const LL LINF=2e17;
const int INF=1e9;
const int magic=348;
const long double eps=1e-15;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,k;
long double a[200048];
long double dp[200048],tmp[200048];
long double sum[200048],sum1[200048];
int lastleft,lastright;
long double curans;

inline void Move(int left,int right)
{
	int i;
	if (lastleft==0 && lastright==0)
	{
		for (i=left;i<=right;i++) curans+=(sum1[i]-sum1[left-1])/a[i];
		return;
	}
	if (lastleft<left)
		for (i=lastleft;i<=left-1;i++) curans-=(sum[lastright]-sum[i-1])*a[i];
	if (lastleft>left)
		for (i=lastleft-1;i>=left;i--) curans+=(sum[lastright]-sum[i-1])*a[i];
	if (lastright<right)
		for (i=lastright+1;i<=right;i++) curans+=(sum1[i]-sum1[left-1])/a[i];
	if (lastright>right)
		for (i=lastright;i>=right+1;i--) curans-=(sum1[i]-sum1[left-1])/a[i];
}

queue<int> q;
inline void solve()
{
	int i,hl,hr,cl,cr,mid;
	q.push(1);q.push(n);q.push(0);q.push(n);
	for (i=0;i<=n;i++) tmp[i]=LINF;
	while (!q.empty())
	{
		hl=q.front();q.pop();hr=q.front();q.pop();cl=q.front();q.pop();cr=q.front();q.pop();
		if (hl>hr || cl>cr) continue;
		if (hl==1)
		{
			curans=0;
			lastleft=lastright=0;
		}
		mid=(hl+hr)>>1;int minpos=0;
		for (i=cl;i<=min(cr,mid-1);i++)
		{
			Move(i+1,mid);
			if (tmp[mid]-(dp[i]+curans)>eps)
			{
				tmp[mid]=dp[i]+curans;
				minpos=i;
			}
			lastleft=i+1;lastright=mid;
		}
		q.push(hl);q.push(mid-1);q.push(cl);q.push(minpos);
		q.push(mid+1);q.push(hr);q.push(minpos);q.push(cr);
	}
	for (i=0;i<=n;i++) dp[i]=tmp[i];
}

int main ()
{
	int i;n=getint();k=getint();
	for (i=1;i<=n;i++) a[i]=getint(),sum[i]=sum[i-1]+double(1)/a[i],sum1[i]=sum1[i-1]+a[i];
	dp[0]=0;for (i=1;i<=n;i++) dp[i]=LINF;
	while (k--) solve();
	printf("%.10Lf\n",dp[n]);
	return 0;
}
