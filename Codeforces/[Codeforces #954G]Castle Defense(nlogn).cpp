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
LL sum[500048],b[500048];

inline void init_ori()
{
	int i,left,right;
	memset(sum,0ll,sizeof(sum));
	for (i=1;i<=n;i++)
	{
		left=max(1,i-r);right=min(n,i+r);
		sum[left]+=a[i];if (r<n) sum[right+1]-=a[i];
	}
	for (i=2;i<=n;i++) sum[i]+=sum[i-1];
}

inline bool check(LL lim)
{
	memset(b,0ll,sizeof(b));
	LL cnt=0,curadd=0;int i,pos;
	for (i=1;i<=n;i++)
	{
		curadd+=b[i];
		if (sum[i]+curadd>=lim) continue;
		if (cnt+lim-sum[i]-curadd>k) return false;
		cnt+=lim-sum[i]-curadd;pos=min(n,i+r);
		if (pos+r+1<=n) b[pos+r+1]+=sum[i]+curadd-lim;
		curadd+=lim-sum[i]-curadd;
	}
	return cnt<=k;
}

int main ()
{
	int i;
	n=getint();r=getint();k=getLL();
	for (i=1;i<=n;i++) a[i]=getint();
	init_ori();
	LL left=0,right=2e18,mid,ans=0;
	while (left<=right)
	{
		mid=(left+right)>>1;
		if (check(mid))
		{
			ans=mid;
			left=mid+1;
		}
		else
			right=mid-1;
	}
	cout<<ans<<endl;
	return 0;
}
