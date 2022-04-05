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

const int MOD=998244353;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int a[400048],b[400048],n,m;

namespace poly
{
	const int G=3;
	int wn_pos[400048],wn_neg[400048];
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
	inline void init_wn()
	{
		for (register int clen=2;clen<=262144;clen<<=1)
			wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
	inline void NTT(int c[],int len,int fl)
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
			for (i=0;i<len;i++) c[i]=(1ll*c[i]*inv)%MOD;
		}
	}
	inline void poly_mul(int A[],int B[],int N,int M)
	{
		int len=1;while (len<=N+M) len<<=1;
		NTT(A,len,1);NTT(B,len,1);
		for (register int i=0;i<len;i++) A[i]=(1ll*A[i]*B[i])%MOD;
		NTT(A,len,-1);
	}
	inline void poly_inv(int A[],int B[],int N)
	{
		B[0]=quick_pow(A[0],MOD-2);
		static int tmp[400048];int Len,i;
		for (register int clen=2;(clen>>1)<N;clen<<=1)
		{
			Len=min(N,clen);
			memcpy(tmp,A,Len*sizeof(int));
			memset(tmp+Len,0,((clen<<1)-Len)*sizeof(int));
			memset(B+(clen>>1),0,((clen<<1)-(clen>>1))*sizeof(int));
			NTT(tmp,clen<<1,1);NTT(B,clen<<1,1);
			for (i=0;i<(clen<<1);i++) B[i]=(1ll*B[i]*sub(2-(1ll*tmp[i]*B[i])%MOD))%MOD;
			NTT(B,clen<<1,-1);
			memset(B+(clen<<1),0,((clen<<1)-(clen>>1))*sizeof(int));
		}
	}
	inline int calc_sqrt(int x) {for (register int i=1;i<=MOD;i++) if ((1ll*i*i)%MOD==x) return i;}
	inline void poly_sqrt(int A[],int B[],int N)
	{
		B[0]=calc_sqrt(A[0]);
		static int tmp[800048],tinv[800048];int i,Len;
		for (register int clen=2;(clen>>1)<N;clen<<=1)
		{
			Len=min(N,clen);
			memcpy(tmp,A,Len*sizeof(int));
			memset(tmp+Len,0,((clen<<1)-Len)*sizeof(int));
			memset(B+(clen>>1),0,((clen<<1)-(clen>>1))*sizeof(int));
			poly_inv(B,tinv,clen);
			memset(tinv+clen,0,((clen<<1)-clen)*sizeof(int));
			NTT(tmp,clen<<1,1);NTT(B,clen<<1,1);NTT(tinv,clen<<1,1);
			for (i=0;i<(clen<<1);i++)
				B[i]=(1ll*add(B[i]+(1ll*tmp[i]*tinv[i])%MOD)*(MOD+1)/2)%MOD;
			NTT(B,clen<<1,-1);
			memset(B+clen,0,((clen<<1)-clen)*sizeof(int));
		}
	}
}

int main ()
{
	using namespace poly;init_wn();
	n=getint();int i;
	for (i=0;i<n;i++) a[i]=getint();
	poly_sqrt(a,b,n);
	for (i=0;i<n;i++) printf("%d ",b[i]);
	return 0;
}
