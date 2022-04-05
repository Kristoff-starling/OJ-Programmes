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
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
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

int n,m;
int a[800048],b[800048],c[800048],r[800048];

namespace poly
{
	const int NTT_MAX=8e5;
	const int G=3;
	int wn_pos[NTT_MAX+48],wn_neg[NTT_MAX+48];
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
	inline void poly_init()
	{
		for (register int clen=2;clen<=524288;clen<<=1)
			wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
	inline void poly_ntt(int c[],int len,int fl)
	{
		int clen,i,j,k,w,wn,tmp1,tmp2;
		for (i=(len>>1),j=1;j<len;j++)
		{
			if (i<j) swap(c[i],c[j]);
			for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
		}
		for (clen=2;clen<=len;clen<<=1)
		{
			wn=(fl==1?wn_pos[clen]:wn_neg[clen]);
			for (j=0;j<len;j+=clen)
			{
				w=1;
				for (k=j;k<j+(clen>>1);k++)
				{
					tmp1=c[k];tmp2=(1ll*c[k+(clen>>1)]*w)%MOD;
					c[k]=add(tmp1+tmp2);c[k+(clen>>1)]=sub(tmp1-tmp2);
					w=(1ll*w*wn)%MOD;
				}
			}
		}
		if (fl==-1)
		{
			int inv=quick_pow(len,MOD-2);
			for (register int i=0;i<len;i++) c[i]=(1ll*c[i]*inv)%MOD;
		}
	}
	inline void poly_mul(int A[],int B[],int N,int M)
	{
		int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)*sizeof(int));memset(B+M,0,(len-M)*sizeof(int));
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (register int i=0;i<len;i++) A[i]=(1ll*A[i]*B[i])%MOD;
		poly_ntt(A,len,-1);
	}
	inline void poly_inv(int A[],int B[],int N)
	{
		B[0]=quick_pow(A[0],MOD-2);
		static int tmp[NTT_MAX+48];int Len,i;
		for (register int clen=2;(clen>>1)<N;clen<<=1)
		{
			Len=min(N,clen);
			memcpy(tmp,A,Len*sizeof(int));
			memset(tmp+Len,0,((clen<<1)-Len)*sizeof(int));
			memset(B+(clen>>1),0,((clen<<1)-(clen>>1))*sizeof(int));
			poly_ntt(tmp,clen<<1,1);poly_ntt(B,clen<<1,1);
			for (int i=0;i<(clen<<1);i++) B[i]=(1ll*B[i]*sub(2-(1ll*tmp[i]*B[i])%MOD))%MOD;
			poly_ntt(B,clen<<1,-1);
		}
	}
	inline void poly_div(int A[],int B[],int C[],int R[],int N,int M)
	{
		static int ar[NTT_MAX+48],br[NTT_MAX+48],tmp[NTT_MAX+48];
		int t=N-M+1,len=1;while (len<=(t<<1)) len<<=1;
		memset(tmp,0,len*sizeof(int));
		reverse_copy(B,B+M,tmp);
		poly_inv(tmp,br,len);
		reverse_copy(A,A+N,ar);
		poly_mul(ar,br,t,t);
		reverse(ar,ar+t);memcpy(C,ar,t);
		for (register int i=0;i<t;i++) C[i]=ar[i];
		for (register int i=0;i<M;i++) br[i]=B[i];
		poly_mul(ar,br,t,M);
		for (register int i=0;i<M;i++) R[i]=sub(A[i]-ar[i]);
	}
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	using namespace poly;int i;
	n=getint();m=getint();
	for (i=0;i<n;i++) a[i]=getint();
	for (i=0;i<m;i++) b[i]=getint();
	poly_init();poly_div(a,b,c,r,n,m);
	for (i=0;i<n-m+1;i++) printf("%d ",c[i]);puts("");
	for (i=0;i<m-1;i++) printf("%d ",r[i]);puts("");
	return 0;
}
