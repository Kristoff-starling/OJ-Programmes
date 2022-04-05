#include <bits/stdc++.h>
// #define LOCAL true
using namespace std;

const int MAXN=5e5;
const int XMAX=524288;

int n,A[MAXN+48];

namespace polynomial
{
	inline void fwt(int c[],int len,int fl)
	{
		for (register int clen=2;clen<=len;clen<<=1)
			for (register int j=0;j<len;j+=clen)
				for (register int k=j;k<j+(clen>>1);k++)
				{
					int tmp1=c[k],tmp2=c[k+(clen>>1)];
					if (fl==1) c[k]=tmp1+tmp2,c[k+(clen>>1)]=tmp1-tmp2;
					else c[k]=(tmp1+tmp2)>>1,c[k+(clen>>1)]=(tmp1-tmp2)>>1;
				}
	}
	inline void poly_fwt(int A[],int B[])
	{
		fwt(A,XMAX,1);
		for (register int i=0;i<XMAX;i++) A[i]*=B[i];
		fwt(A,XMAX,-1);
	}
}

int a[XMAX*2+48],b[XMAX*2+48];

int main ()
{
#ifdef LOCAL
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	scanf("%d",&n);int xsum=0;
	for (register int i=1;i<=n;i++) scanf("%d",A+i),xsum^=A[i],b[A[i]]|=1;
	if (!xsum) {printf("%d\n",n);return 0;}
	if (b[xsum]) {printf("%d\n",n-1);return 0;}
	memcpy(a,b,sizeof(b));
	polynomial::fwt(b,XMAX,1);
	for (register int ans=2;ans<=n;ans++)
	{
		polynomial::poly_fwt(a,b);
		if (a[xsum]) {printf("%d\n",n-ans);return 0;}
		for (register int i=0;i<XMAX;i++) if (a[i]) a[i]=1;
	}
	return 0;
}

