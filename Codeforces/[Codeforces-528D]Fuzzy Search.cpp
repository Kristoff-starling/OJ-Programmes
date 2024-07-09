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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

char s[200048],ss[200048];int n,m,k;
bool exist[5][200048];int curpos;
int table[248];
bool type[5][200048];int cnt[5];

struct Complex
{
	double r,i;
	Complex() {}
	inline Complex(double x,double y) {r=x;i=y;}
	inline Complex operator + (Complex x) {return Complex(r+x.r,i+x.i);}
	inline Complex operator - (Complex x) {return Complex(r-x.r,i-x.i);}
	inline Complex operator * (Complex x) {return Complex(r*x.r-i*x.i,r*x.i+i*x.r);}
	inline Complex operator / (double x) {return Complex(r/x,i/x);}
};

Complex a[1500048],b[1500048],res[5][1500048];int len;

inline void FFT(Complex c[],int fl)
{
	int clen,i,j,k;
	for (i=(len>>1),j=1;j<len;j++)
	{
		if (i<j) swap(c[i],c[j]);
		for (k=(len>>1);i&k;k>>=1) i^=k;
		i^=k;
	}
	for (clen=2;clen<=len;clen<<=1)
	{
		Complex wn=Complex(cos(pi*2*fl/clen),sin(pi*2*fl/clen));
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

inline void calc_FFT(int cur)
{
	int i;
	len=1;while (len<=n+1+m) len<<=1;
	for (i=0;i<len;i++) a[i]=Complex(0,0),b[i]=Complex(0,0);
	for (i=1;i<=n;i++) a[i]=(exist[cur][i]?Complex(1,0):Complex(0,0));
	for (i=m-1;i>=0;i--) b[i]=(type[cur][m-i]?Complex(1,0):Complex(0,0));
	FFT(a,1);FFT(b,1);
	for (i=0;i<len;i++) a[i]=a[i]*b[i];
	FFT(a,-1);
	for (i=0;i<len;i++) res[cur][i]=a[i];
}

int main ()
{
	int i,j;
	n=getint();m=getint();k=getint();
	scanf("%s%s",s+1,ss+1);
	table['A']=1;table['T']=2;table['G']=3;table['C']=4;
	for (j=1;j<=4;j++)
	{
		curpos=-INF;
		for (i=1;i<=n;i++)
		{
			if (table[s[i]]==j) curpos=i;
			if (i-curpos<=k) exist[j][i]=true;
		}
		curpos=INF;
		for (i=n;i>=1;i--)
		{
			if (table[s[i]]==j) curpos=i;
			if (curpos-i<=k) exist[j][i]=true;
		}
	}
	for (j=1;j<=4;j++)
		for (i=1;i<=m;i++)
			type[j][i]=(table[ss[i]]==j),cnt[j]+=(table[ss[i]]==j);
	for (i=1;i<=4;i++) calc_FFT(i);
	int ans=0;
	for (i=m;i<=n;i++)
	{
		bool f=true;
		for (j=1;j<=4;j++)
		{
			int val=int(res[j][i].r+0.5);
			if (val!=cnt[j]) {f=false;break;}
		}
		if (f) ans++;
	}
	printf("%d\n",ans);
	return 0;
}
