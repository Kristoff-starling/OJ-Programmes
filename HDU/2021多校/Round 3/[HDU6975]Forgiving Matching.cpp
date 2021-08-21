#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=1e6;
const int MOD=998244353;

int n,m;
char s[MAXN+48],t[MAXN+48];
int a[MAXN+48],b[MAXN+48];

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}

namespace poly
{
    const int NTT_MAX=8e5;
	const int G=3;
	int wn_pos[NTT_MAX+48],wn_neg[NTT_MAX+48];bool init;
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
		for (int clen=2;clen<=262144*2;clen<<=1)
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
			for (int i=0;i<len;i++) c[i]=(1ll*c[i]*inv)%MOD;
		}
	}
	inline void poly_mul(int A[],int B[],int N,int M)
	{
        poly_init();int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)*sizeof(int));memset(B+M,0,(len-M)*sizeof(int));
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (int i=0;i<len;i++) A[i]=(1ll*A[i]*B[i])%MOD;
		poly_ntt(A,len,-1);
	}
    inline void poly_mul(int A[],int B[],int N,int M,int C[])
    {
        poly_init();int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)*sizeof(int));memset(B+M,0,(len-M)*sizeof(int));
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (int i=0;i<len;i++) C[i]=(1ll*A[i]*B[i])%MOD;
		poly_ntt(C,len,-1);
    }
}

int cnt[MAXN+48];
int ans[MAXN+48];

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);scanf("%s%s",s+1,t+1);
        rep(i,1,n-m+1) cnt[i]=m;
        rep(bit,0,9)
        {
            a[0]=b[0]=0;
            rep(i,1,n) if (s[i]-'0'==bit || s[i]=='*') a[i]=1; else a[i]=0;
            rep(i,1,m) if (t[i]-'0'==bit || t[i]=='*') b[i]=1; else b[i]=0;
            reverse(b,b+m+1);
            poly::poly_mul(a,b,n+1,m+1);
            rep(i,1,n-m+1) cnt[i]-=a[m+i-1];
        }
        a[0]=b[0]=0;
        rep(i,1,n) if (s[i]=='*') a[i]=1; else a[i]=0;
        rep(i,1,m) if (t[i]=='*') b[i]=1; else b[i]=0;
        reverse(b,b+m+1);
        poly::poly_mul(a,b,n+1,m+1);
        rep(i,1,n-m+1) cnt[i]+=9*a[m+i-1];
        rep(i,0,m) ans[i]=0;
        rep(i,1,n-m+1) ans[cnt[i]]++;
        rep(i,1,m) ans[i]+=ans[i-1];
        rep(i,0,m) printf("%d\n",ans[i]);
    }
    return 0;
}