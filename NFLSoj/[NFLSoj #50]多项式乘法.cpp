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

const int G=3;
const LL MOD=998244353;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.1415926535897932384626;

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

int n,m;
LL a[300048],b[300048];

LL quick_pow(LL x,LL y)
{
	x%=MOD;LL res=1;
	while (y)
	{
		if (y&1)
		{
			res=(res*x)%MOD;
			y--;
		}
		x=(x*x)%MOD;
		y>>=1;
	}
	return res;
}

void NTT(LL c[],int len,int fl)
{
	int i,j,k,clen,id=0;
	for (i=(len>>1),j=1;j<len;j++)
	{
		if (i<j) swap(c[i],c[j]);
		for (k=(len>>1);i&k;k>>=1) i^=k;
		i^=k;
	}
	for (clen=2;clen<=len;clen<<=1)
	{
		LL wn=quick_pow(G,fl==1?(MOD-1)/clen:(MOD-1)-(MOD-1)/clen);
		for (j=0;j<len;j+=clen)
		{
			LL w=1ll;
			for (k=j;k<j+(clen>>1);k++)
			{
				LL tmp1=c[k]%MOD,tmp2=((c[k+(clen>>1)]%MOD)*w)%MOD;
				c[k]=(tmp1+tmp2)%MOD;c[k+(clen>>1)]=((tmp1-tmp2)%MOD+MOD)%MOD;
				w=(w*wn)%MOD;
			}
		}
	}
	if (fl==-1)
	{
		LL inv=quick_pow(len,MOD-2);
		for (i=0;i<len;i++) c[i]=(c[i]%MOD*inv)%MOD;
	}
}	

void calc_NTT()
{
	int i,l=(1<<18);
	NTT(a,l,1);
	NTT(b,l,1);
	for (i=0;i<l;i++) a[i]=(a[i]*b[i])%MOD;
	NTT(a,l,-1);
}

int main ()
{
	int i,x;
	n=getint();m=getint();
	for (i=0;i<n;i++) scanf("%d",&x),a[i]=x;
	for (i=0;i<m;i++) scanf("%d",&x),b[i]=x;
	calc_NTT();
	for (i=0;i<n+m-1;i++) printf("%lld ",a[i]%MOD);
	printf("\n");
	return 0;
}
