#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
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

const int MAXN=8e5;

char s[MAXN+48];int len;

struct Complex
{
	double r,i;
	Complex () {}
	inline Complex (double x,double y) {r=x;i=y;}
	inline Complex operator + (Complex other) {return Complex(r+other.r,i+other.i);}
	inline Complex operator - (Complex other) {return Complex(r-other.r,i-other.i);}
	inline Complex operator * (Complex other) {return Complex(r*other.r-i*other.i,r*other.i+i*other.r);}
	inline Complex operator / (double x) {return Complex(r/x,i/x);}
}a[MAXN+48],b[MAXN+48];

namespace poly
{
	inline void poly_fft(Complex c[],int len,int fl)
	{
		int clen,i,j,k;
		for (i=(len>>1),j=1;j<len;j++)
		{
			if (i<j) swap(c[i],c[j]);
			for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
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
	inline void poly_mul(Complex A[],Complex B[],int N,int M)
	{
		int len=1;while (len<=N+M) len<<=1;
		for (register int i=N;i<len;i++) A[i]=Complex(0,0);
		for (register int i=M;i<len;i++) B[i]=Complex(0,0);
		poly_fft(A,len,1);poly_fft(B,len,1);
		for (register int i=0;i<len;i++) A[i]=A[i]*B[i];
		poly_fft(A,len,-1);
	}
}

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD;y>>=1;
	}
	return res;
}

char ss[MAXN+48];int RL[MAXN+48];
inline void manacher()
{
	int slen=0,i,pos,maxright;
	for (i=1;i<=len;i++) ss[++slen]='#',ss[++slen]=s[i];
	ss[++slen]='#';
	pos=maxright=0;
	for (i=1;i<=slen;i++)
	{
		if (i<maxright) RL[i]=min(maxright-i,RL[2*pos-i]); else RL[i]=1;
		while (i-RL[i]>=1 && i+RL[i]<=slen && ss[i-RL[i]]==ss[i+RL[i]]) RL[i]++;
		if (i+RL[i]-1>maxright) maxright=i+RL[i]-1,pos=i;
	}
}

int cnt[MAXN+48];

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	scanf("%s",s+1);len=strlen(s+1);
	manacher();int i;
	for (i=0;i<len;i++) a[i]=b[i]=(s[i+1]=='a'?Complex(1,0):Complex(0,0));
	poly::poly_mul(a,b,len,len);
	for (i=0;i<len*2-1;i++) if (i%2==0) cnt[i]+=(int(a[i].r+0.5)+1)/2; else cnt[i]+=int(a[i].r+0.5)/2;
	for (i=0;i<len;i++) a[i]=b[i]=(s[i+1]=='b'?Complex(1,0):Complex(0,0));
	poly::poly_mul(a,b,len,len);
	for (i=0;i<len*2-1;i++) if (i%2==0) cnt[i]+=(int(a[i].r+0.5)+1)/2; else cnt[i]+=int(a[i].r+0.5)/2;
	int ans=0;
	for (i=0;i<len*2-1;i++) ans=add(ans+sub(quick_pow(2,cnt[i])-1-RL[i+2]/2));
	printf("%d\n",ans);
	return 0;
}
