#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

const int MOD=998244353;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

namespace poly
{
    const int NTT_MAX=1100000;
	const int G=3;
	bool init=false;
	int wn_pos_pw[21][NTT_MAX+48],wn_neg_pw[21][NTT_MAX+48];
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
		if (init) return;
		init=true;int w;
		for (int clen=2,c=1;clen<=1048576;clen<<=1,c++)
		{
			wn_pos_pw[c][0]=1;w=quick_pow(G,(MOD-1)/clen);
			rep(i,1,NTT_MAX) wn_pos_pw[c][i]=1ll*wn_pos_pw[c][i-1]*w%MOD;
			wn_neg_pw[c][0]=1;w=quick_pow(G,(MOD-1)-(MOD-1)/clen);
			rep(i,1,NTT_MAX) wn_neg_pw[c][i]=1ll*wn_neg_pw[c][i-1]*w%MOD;
		}
	}
	void poly_ntt(int c[],int len,int fl)
	{
		int clen,i,j,k,l,cc,tmp1,tmp2;
		for (i=(len>>1),j=1;j<len;j++)
		{
			if (i<j) swap(c[i],c[j]);
			for (k=(len>>1);i&k;k>>=1) i^=k;i^=k;
		}
		for (clen=2,cc=1;clen<=len;clen<<=1,cc++)
		{
			for (j=0;j<len;j+=clen)
			{
				for (k=j,l=0;k<j+(clen>>1);k++,l++)
				{
					tmp1=c[k];tmp2=1ll*c[k+(clen>>1)]*(fl==1?wn_pos_pw[cc][l]:wn_neg_pw[cc][l])%MOD;
					c[k]=add(tmp1+tmp2);c[k+(clen>>1)]=sub(tmp1-tmp2);
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

int pw[21][1100048],plen[21];
int A[2000048],B[2000048];

char s[2000048];int num[2000048],ans[2000048];

bool solve(int l,int r,int ans[])
{
    if (r==l+1)
    {
        int pt=0,tmp=num[l];
        while (tmp) ans[pt++]=tmp%3,tmp/=3;
        return (pt==0 ? false : true);
    }
	bool nonzero=false;
	rep(i,l,r-1) if (num[i]) {nonzero=true;break;}
	if (!nonzero) return false;
    int mid=(l+r)>>1;
    int Len=1,c=0;while (Len!=r-l) Len<<=1,c++;Len>>=1;c--;
    int L[Len*3+1],R[Len*3+1];
    memset(L,0,sizeof(L));memset(R,0,sizeof(R));
    solve(l,mid,L);rep(i,0,Len*3) ans[i]+=L[i];
	bool res=solve(mid,r,R);
	if (res)
	{
		rep(i,0,Len*6) A[i]=0;
		rep(i,0,plen[c]-1) A[i]=pw[c][i];
		rep(i,0,Len*3-1) B[i]=R[i];
		int Rlen=Len*3;while (Rlen>0 && !B[Rlen-1]) Rlen--;
		if (!Rlen) Rlen=1;
		poly::poly_mul(A,B,plen[c],Rlen);
		rep(i,0,Len*6-1) ans[i]+=A[i];
	}
    rep(i,0,Len*6-1) ans[i+1]+=ans[i]/3,ans[i]%=3;
	return true;
}

int main ()
{
    pw[0][0]=1;pw[0][1]=0;pw[0][2]=1;plen[0]=3;
    rep(i,1,18)
    {
        rep(j,0,plen[i-1]-1) A[j]=B[j]=pw[i-1][j];
        poly::poly_mul(A,B,plen[i-1],plen[i-1],pw[i]);
        plen[i]=(plen[i-1]<<1)+2;
        rep(j,0,plen[i]-1) pw[i][j+1]+=pw[i][j]/3,pw[i][j]%=3;
        while (!pw[i][plen[i]-1]) plen[i]--;
    }
    scanf("%s",s);int len=strlen(s);
    int Len=1;while (Len<len) Len<<=1;
    rep(i,0,len-1) num[i]=s[len-1-i]-'0';rep(i,len,Len-1) num[i]=0;len=Len;
    solve(0,len,ans);
    int pt=2e6;while (!ans[pt]) pt--;
    for (;pt>=0;pt--) printf("%d",ans[pt]);puts("");
    return 0;
}