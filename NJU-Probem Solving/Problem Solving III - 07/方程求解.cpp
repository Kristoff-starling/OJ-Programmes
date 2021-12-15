#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MAXN=5e5;
const int MOD=998244353;

int isprime[MAXN+48],prime[MAXN+48],tot;
int cnt[500048],A[2000048],B[2000048];

void sieve()
{
    rep(i,1,MAXN) isprime[i]=i;
    rep(i,2,MAXN)
    {
        if (isprime[i]==i) prime[++tot]=i;
        for (int j=1;1ll*i*prime[j]<=MAXN;j++)
        {
            isprime[i*prime[j]]=prime[j];
            if (i%prime[j]==0) break;
        }
    }
    cnt[1]=1;
    rep(i,2,MAXN)
    {
        int tmp=i,curfac=0,curcnt=0;cnt[i]=1;
        while (tmp!=1)
        {
            if (isprime[tmp]!=curfac) cnt[i]*=(curcnt+1),curfac=isprime[tmp],curcnt=1; else curcnt++;
            tmp/=isprime[tmp];
        }
        cnt[i]*=(curcnt+1);
    }
}

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

namespace poly
{
    const int NTT_MAX=2e6;
	const int G=3;
	int wn_pos[NTT_MAX+48],wn_neg[NTT_MAX+48];bool init;
	int quick_pow(int x,int y)
	{
		int res=1;
		while (y)
		{
			if (y&1) res=(1ll*res*x)%MOD,y--;
			x=(1ll*x*x)%MOD;y>>=1;
		}
		return res;
	}
	void poly_init()
	{
		for (int clen=2;clen<=1048576;clen<<=1)
			wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
	void poly_ntt(int c[],int len,int fl)
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
	void poly_mul(int A[],int B[],int N,int M)
	{
        poly_init();int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)*sizeof(int));memset(B+M,0,(len-M)*sizeof(int));
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (int i=0;i<len;i++) A[i]=(1ll*A[i]*B[i])%MOD;
		poly_ntt(A,len,-1);
	}
    void poly_mul(int A[],int B[],int N,int M,int C[])
    {
        poly_init();int len=1;while (len<=N+M) len<<=1;
		memset(A+N,0,(len-N)*sizeof(int));memset(B+M,0,(len-M)*sizeof(int));
		poly_ntt(A,len,1);poly_ntt(B,len,1);
		for (int i=0;i<len;i++) C[i]=(1ll*A[i]*B[i])%MOD;
		poly_ntt(C,len,-1);
    }
}

int main ()
{
    int ca,n;scanf("%d",&ca);
    sieve();
    A[0]=B[0]=0;rep(i,1,MAXN) A[i]=B[i]=cnt[i];
    poly::poly_mul(A,B,MAXN+1,MAXN+1);
    while (ca--)
    {
        scanf("%d",&n);
        printf("%d\n",A[n]);
    }
    return 0;
}