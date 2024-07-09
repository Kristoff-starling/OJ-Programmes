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

int n,k;
LL a[100048];
int cnt[100048];
LL dp[100048],tmp[100048];
LL curans;

inline void Move(int left,int right,int lastleft,int lastright)
{
	int i;
	if (lastleft==0 && lastright==0)
	{
		for (i=left;i<=right;i++)
			curans+=(cnt[a[i]]++);
		return;
	}
	if (left<lastleft)
		for (i=lastleft-1;i>=left;i--) curans+=(cnt[a[i]]++);
	if (left>lastleft)
		for (i=lastleft;i<=left-1;i++) curans-=(--cnt[a[i]]);
	if (right<lastright)
		for (i=lastright;i>=right+1;i--) curans-=(--cnt[a[i]]);
	if (right>lastright)
		for (i=lastright+1;i<=right;i++) curans+=(cnt[a[i]]++);
}

queue<int> q;
inline void solve()
{
	int hl,hr,cl,cr,mid,i,lastleft,lastright;
	q.push(1);q.push(n);q.push(0);q.push(n);
	while (!q.empty())
	{
		hl=q.front();q.pop();hr=q.front();q.pop();cl=q.front();q.pop();cr=q.front();q.pop();
		if (hl>hr || cl>cr) continue;
		if (hl==1)
		{
			curans=0;
			lastleft=lastright=0;
			memset(cnt,0,sizeof(cnt));
		}
		mid=(hl+hr)>>1;tmp[mid]=LINF;
		int minpos;
		for (i=cl;i<=min(mid-1,cr);i++)
		{
			Move(i+1,mid,lastleft,lastright);
			lastleft=i+1;lastright=mid;
			if (tmp[mid]>dp[i]+curans)
			{
				tmp[mid]=dp[i]+curans;
				minpos=i;
			}
		}
		q.push(hl);q.push(mid-1);q.push(cl);q.push(minpos);
		q.push(mid+1);q.push(hr);q.push(minpos);q.push(cr);
	}
	for (i=0;i<=n;i++) dp[i]=tmp[i];
}

int main ()
{
	int i,j;n=getint();k=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++) dp[i]=LINF;dp[0]=0;
	for (i=1;i<=k;i++)
	{
		for (j=0;j<=n;j++) tmp[j]=INF;
		solve();
	}
	printf("%lld\n",dp[n]);
	return 0;
}
