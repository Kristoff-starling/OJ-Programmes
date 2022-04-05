#include <cassert>
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
const int magic=100000;
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

LL k,n,A,B,lower,upper;
LL Left,Right;

LL a[500048];int tot=0;

inline LL mul(LL x,LL y)
{
	x%=n;LL res=0;
	while (y)
	{
		if (y&1) res=(res+x)%n,y--;
		x=(x+x)%n;y>>=1;
	}
	return res;
}

inline int bsearch1(LL cmp)
{
	int l=1,r=tot,mid,res=tot+1;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (a[mid]>=cmp) res=mid,r=mid-1; else l=mid+1;
	}
	return res;
}

inline int bsearch2(LL cmp)
{
	int l=1,r=tot,mid,res=0;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (a[mid]<=cmp) res=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

inline LL solve(LL left,LL right)
{
	int lpos=bsearch1(left),rpos=bsearch2(right);
	return max(rpos-lpos+1,0);
}

class ModuleSequence
{
	public:
		inline LL countElements(LL K,LL N,LL AA,LL BB,LL Lower,LL Upper)
		{
			k=K;n=N;A=AA;B=BB;lower=Lower;upper=Upper;k%=n;
			int i,j;
			Left=A/magic;
			while (Left*magic-(magic-1)<A) Left++;
			Right=B/magic;
			while (Right*magic<=B) Right++;Right--;
			for (i=Left;i<=Right;i++) a[++tot]=((k*i)%n*magic)%n;
			sort(a+1,a+tot+1);
			LL res=0;
			for (j=0;j<=magic-1;j++)
			{
				LL L=(lower+(k*j)%n)%n,R=(upper+(k*j)%n)%n;
				LL add=0;
				if (L<=R) add+=solve(L,R); else add+=solve(L,n-1),add+=solve(0,R);
				res+=add;
			}
			for (j=0;j<=magic-1;j++)
			{
				LL X=(Left-1)*magic-j;
				if (X<A || X>B) continue;
				LL rr=mul(k,X);
				if (lower<=rr && rr<=upper) res++;
			}
			if (Right+1!=Left-1)
			{
				for (j=0;j<=magic-1;j++)
				{
					LL X=(Right+1)*magic-j;
					if (X<A || X>B) continue;
					LL rr=mul(k,X);
					if (lower<=rr && rr<=upper) res++;
				}
			}
			return res;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	ModuleSequence A;
	LL kk,nn,aa,bb,ll,uu;
	while  (cin>>kk>>nn>>aa>>bb>>ll>>uu) cout<<A.countElements(kk,nn,aa,bb,ll,uu)<<endl;
	return 0;
}
*/
/*
890 1000 1000 10000 456 980
8229093 6444334183 346 4720366958 65 990216849
*/
