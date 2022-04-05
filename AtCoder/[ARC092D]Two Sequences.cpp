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
#define ll long long
#define lb long double
#define x first
#define y second
#define pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define lowbit(x) x & (-x)
using namespace std;

const int mod=1e9+7;
const ll linf=2e16;
const int inf=2e9;
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

int n;
int a[200048],b[200048],bb[200048];
ll cnt[48];

inline int binsearch_down(int cmp)
{
	int l=1,r=n,mid,res=n+1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (bb[mid]>=cmp) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}

inline int binsearch_up(int cmp)
{
	int l=1,r=n,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (bb[mid]<cmp) res=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

int main ()
{
	int i,bit,cc;n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++) b[i]=getint();
	memset(cnt,0,sizeof(cnt));
	for (bit=1;bit<=30;bit++)
	{
		for (i=1;i<=n;i++) bb[i]=(b[i]&((1<<bit)-1));
		sort(bb+1,bb+n+1);
		for (i=1;i<=n;i++)
		{
			cc=(((1<<(bit-1))-1)&a[i]);
			if (a[i]&(1<<(bit-1)))
				cnt[bit]+=binsearch_up((1<<(bit-1))-cc)+(n-(binsearch_down((1<<bit)-cc)-1));
			else
				cnt[bit]+=binsearch_up((1<<bit)-cc)-binsearch_down((1<<(bit-1))-cc)+1;
		}
	}
	int ans=0;
	for (i=1;i<=30;i++)
		if (cnt[i]%2==1) ans^=(1<<(i-1));
	printf("%d\n",ans);
	return 0;
}
