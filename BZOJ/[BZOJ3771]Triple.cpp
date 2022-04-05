#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <iomanip>
#include <functional>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int MOD=1e9+7;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

struct Complex
{
	double r,i;
	Complex () {}
	inline Complex (double x,double y) {r=x;i=y;}
	inline Complex operator + (Complex x) {return Complex(r+x.r,i+x.i);}
	inline Complex operator - (Complex x) {return Complex(r-x.r,i-x.i);}
	inline Complex operator * (Complex x) {return Complex(r*x.r-i*x.i,r*x.i+i*x.r);}
	inline Complex operator / (double x) {return Complex(r/x,i/x);}
}A[300048],B[300048];

int n,len=262144;
int a[100048];
Complex ans[300048],ans1[300048];

inline void FFT(Complex c[],int fl)
{
	int i,j,k,clen;
	for (i=(len>>1),j=1;j<len;j++)
	{
		if (i<j) swap(c[i],c[j]);
		for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
	}
	for (clen=2;clen<=len;clen<<=1)
	{
		Complex wn=Complex(cos(2*pi*fl/clen),sin(2*pi*fl/clen));
		for (j=0;j<len;j+=clen)
		{
			Complex w=Complex(1,0);
			for (k=j;k<j+(clen>>1);k++)
			{
				Complex tmp1=c[k],tmp2=c[k+(clen>>1)]*w;
				c[k]=tmp1+tmp2;c[k+(clen>>1)]=tmp1-tmp2;
				w=w*wn;
			}
		}
	}
	if (fl==-1)
		for (i=0;i<len;i++) c[i]=c[i]/len;
}

inline void calc_FFT()
{
	FFT(A,1);FFT(B,1);
	for (register int i=0;i<len;i++) A[i]=A[i]*B[i];
	FFT(A,-1);
}

int main ()
{
	int i;n=getint();
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=0;i<len;i++) A[i]=Complex(0,0);
	for (i=1;i<=n;i++) A[a[i]].r++;
	for (i=0;i<len;i++) B[i]=A[i];
	calc_FFT();
	for (i=0;i<len;i++) B[i]=Complex(0,0);
	for (i=1;i<=n;i++) B[a[i]].r++;
	calc_FFT();
	for (i=0;i<len;i++) ans[i]=A[i];
	for (i=0;i<len;i++) A[i]=Complex(0,0);
	for (i=1;i<=n;i++) A[a[i]*2].r++;
	for (i=0;i<len;i++) B[i]=Complex(0,0);
	for (i=1;i<=n;i++) B[a[i]].r++;
	calc_FFT();
	for (i=0;i<len;i++) ans[i]=ans[i]-A[i]*Complex(3,0);
	for (i=1;i<=n;i++) ans[a[i]*3].r+=2;
	for (i=0;i<len;i++) ans[i]=ans[i]/6;
	for (i=0;i<len;i++) A[i]=Complex(0,0);
	for (i=1;i<=n;i++) A[a[i]].r++;
	for (i=0;i<len;i++) B[i]=A[i];
	calc_FFT();
	for (i=1;i<=n;i++) A[a[i]*2].r--;
	for (i=0;i<len;i++) ans[i]=ans[i]+A[i]/2;
	for (i=1;i<=n;i++) ans[a[i]].r++;
	for (i=0;i<len;i++)
	{
		int res=int(ans[i].r+0.5);
		if (res) printf("%d %d\n",i,res);
	}
	return 0;
}
