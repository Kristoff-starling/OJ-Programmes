#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;
const int MAXN=5e5;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

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

int n,m;

int tmp1[MAXN+48],tmp2[MAXN+48],A[MAXN+48],B[MAXN+48];
int Tmp[MAXN+48],TmpA[MAXN+48],TmpB[MAXN+48];

void solve(int n)
{
    if (n==0) {tmp1[0]=1;tmp2[0]=1;tmp2[1]=1;tmp2[2]=1;return;}
    if (n==1)
    {
        tmp1[0]=1;tmp1[1]=1;tmp1[2]=1;
        tmp2[0]=1;tmp2[1]=3;tmp2[2]=5;tmp2[3]=3;tmp2[4]=1;
        return;
    }
    int L=n/2,R=n-L;
    if (L==R)
    {

        solve(L-1);int N=min(m+1,(L-1)<<1|1),M=min(m+1,L<<1|1);
        memset(Tmp,0,min(n<<1|1,m+1)*sizeof(int));
        memcpy(TmpA,tmp1,N*sizeof(int));
        memcpy(TmpB,tmp2,M*sizeof(int));

        memcpy(A,tmp1,N*sizeof(int));memcpy(B,tmp1,N*sizeof(int));
        poly::poly_mul(A,B,N,N);
        for (int i=0;i<min(N+N-1,m+1);i++) Add(Tmp[i+1],A[i]),Add(Tmp[i+2],add(A[i]+A[i])),Add(Tmp[i+3],A[i]);
        N=min(m+1,L<<1|1);
        memcpy(A,tmp2,N*sizeof(int));memcpy(B,tmp2,N*sizeof(int));
        poly::poly_mul(A,B,N,N);
        for (int i=0;i<min(N+N-1,m+1);i++) Add(Tmp[i],A[i]),tmp1[i]=Tmp[i]; 

        memset(Tmp,0,min((n+1)<<1|1,m+1)*sizeof(int));

        N=min(m+1,(L-1)<<1|1);M=min(m+1,L<<1|1);
        memcpy(A,TmpA,N*sizeof(int));memcpy(B,TmpB,M*sizeof(int));
        poly::poly_mul(A,B,N,M);
        for (int i=0;i<min(N+M-1,m+1);i++) Add(Tmp[i+1],A[i]),Add(Tmp[i+2],add(A[i]+A[i])),Add(Tmp[i+3],A[i]);

        N=min(m+1,(L+1)<<1|1);
        for (int i=0;i<N;i++)
        {
            long long tt=0;
            if (i<min(m+1,L<<1|1)) tt+=TmpB[i];
            if (i>=1 && i-1<min(m+1,L<<1|1)) tt+=TmpB[i-1];
            if (i>=1 && i-1<min(m+1,(L-1)<<1|1)) tt+=TmpA[i-1];
            if (i>=2 && i-2<min(m+1,L<<1|1)) tt+=TmpB[i-2];
            if (i>=2 && i-2<min(m+1,(L-1)<<1|1)) tt+=TmpA[i-2]+TmpA[i-2];
            if (i>=3 && i-3<min(m+1,(L-1)<<1|1)) tt=tt+TmpA[i-3];
            tt%=MOD;A[i]=tt;
        }
        memcpy(B,TmpB,M*sizeof(int));
        poly::poly_mul(A,B,N,M);
        for (int i=0;i<min(N+M-1,m+1);i++) Add(Tmp[i],A[i]),tmp2[i]=Tmp[i];
    }
    else
    {
        solve(L-1);
        int N=min(m+1,(L-1)<<1|1),M=min(m+1,L<<1|1);
        memcpy(TmpA,tmp1,N*sizeof(int));memcpy(TmpB,tmp2,M*sizeof(int));
        
        memset(Tmp,0,min(m+1,n<<1|1)*sizeof(int));
        memcpy(A,TmpA,N*sizeof(int));memcpy(B,TmpB,M*sizeof(int));
        poly::poly_mul(A,B,N,M);
        for (int i=0;i<min(N+M-1,m+1);i++) Add(Tmp[i+1],A[i]),Add(Tmp[i+2],add(A[i]+A[i])),Add(Tmp[i+3],A[i]);
        N=min(m+1,(L+1)<<1|1);
        for (int i=0;i<N;i++)
        {
            long long tt=0;
            if (i<min(m+1,L<<1|1)) tt+=TmpB[i];
            if (i>=1 && i-1<min(m+1,L<<1|1)) tt+=TmpB[i-1];
            if (i>=1 && i-1<min(m+1,(L-1)<<1|1)) tt+=TmpA[i-1];
            if (i>=2 && i-2<min(m+1,L<<1|1)) tt+=TmpB[i-2];
            if (i>=2 && i-2<min(m+1,(L-1)<<1|1)) tt+=TmpA[i-2]+TmpA[i-2];
            if (i>=3 && i-3<min(m+1,(L-1)<<1|1)) tt=tt+TmpA[i-3];
            tt%=MOD;A[i]=tt;
        }
        memcpy(TmpA,A,N*sizeof(int));
        memcpy(B,TmpB,M*sizeof(int));
        poly::poly_mul(A,B,N,M);
        for (int i=0;i<min(N+M-1,m+1);i++) Add(Tmp[i],A[i]),tmp1[i]=Tmp[i];

        memset(Tmp,0,min(m+1,(n+1)<<1|1)*sizeof(int));
        N=min(m+1,L<<1|1);
        memcpy(A,TmpB,N*sizeof(int));memcpy(B,TmpB,N*sizeof(int));
        poly::poly_mul(A,B,N,N);
        for (int i=0;i<min(N+N-1,m+1);i++) Add(Tmp[i+1],A[i]),Add(Tmp[i+2],add(A[i]+A[i])),Add(Tmp[i+3],A[i]);
        N=min(m+1,(L+1)<<1|1);
        memcpy(A,TmpA,N*sizeof(int));memcpy(B,TmpA,N*sizeof(int));
        poly::poly_mul(A,B,N,N);
        for (int i=0;i<min(N+N-1,m+1);i++) Add(Tmp[i],A[i]),tmp2[i]=Tmp[i];
    }
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);
        solve(n);
        rep(i,1,m) printf("%d ",tmp1[i]);
        puts("");
    }
    return 0;
}