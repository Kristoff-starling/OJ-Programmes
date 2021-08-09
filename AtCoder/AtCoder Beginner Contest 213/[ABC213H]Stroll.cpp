#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define Pair pair<int,int>
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MOD=998244353;

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

int n,m,T;

int dp[11][50048];
int X[48],Y[48],p[11][50048];
int A[300048],B[300048];

void solve(int l,int r)
{
    if (l==r) return;
    int mid=(l+r)>>1;
    solve(l,mid);int N,M;
    rep(i,1,m)
    {
        N=mid-l+1;rep(j,0,N-1) A[j]=dp[X[i]][l+j];
        M=r-l+1;B[0]=0;rep(j,1,M-1) B[j]=p[i][j];
        poly::poly_mul(A,B,N,M);
        rep(j,mid+1,r) Add(dp[Y[i]][j],A[N-1+j-mid]);
        rep(j,0,N-1) A[j]=dp[Y[i]][l+j];
        B[0]=0;rep(j,1,M-1) B[j]=p[i][j];
        poly::poly_mul(A,B,N,M);
        rep(j,mid+1,r) Add(dp[X[i]][j],A[N-1+j-mid]);
    }
	solve(mid+1,r);
}

int main ()
{
    scanf("%d%d%d",&n,&m,&T);
    rep(i,1,m)
    {
        scanf("%d%d",X+i,Y+i);
        rep(j,1,T) scanf("%d",&p[i][j]);
    }
    memset(dp,0,sizeof(dp));dp[1][0]=1;
    solve(0,T);
    printf("%d\n",dp[1][T]);
    return 0;
}