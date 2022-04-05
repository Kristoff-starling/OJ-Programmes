#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int 
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
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rlen,wlen;
	fastio () {rlen=wlen=0;}
	inline char Getchar()
	{
		if (rlen==S) rlen=0,fread(rbuf,1,S,stdin);
		return rbuf[rlen++];
	}
	template <class T> inline void Get(T &x)
	{
		T res=0;char ch;bool f;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=res;
	}
	inline void flush() {fwrite(wbuf,1,wlen,stdout);rlen=0;}
	inline void Writechar(char ch)
	{
		wbuf[wlen++]=ch;
		if (wlen==S) flush();
	}
	template <class T> inline void Print(T res,char ch)
	{
		char s[48];int pt;
		if (res==0)
		{
			pt=1;
			s[1]='0';
		}
		else
		{
			bool f=true;if (res<0) f=false,res=-res;
			pt=0;while (res) s[++pt]=res%10+'0',res/=10;
			if (!f) s[++pt]='-';
		}
		while (pt>=1) Writechar(s[pt--]);
		Writechar(ch);
	}
}io;

const int MAXN=(1<<20);

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

namespace poly
{
	const int G=3;
	int wn_pos[MAXN+48],wn_neg[MAXN+48];
	int len;
	inline void init_w()
	{
		for (register int clen=2;clen<=(1<<20);clen<<=1)
			wn_pos[clen]=quick_pow(G,(MOD-1)/clen),wn_neg[clen]=quick_pow(G,(MOD-1)-(MOD-1)/clen);
	}
	inline void init(int n) {for (len=1;len<=n;len<<=1);}
	inline void ntt(int c[],int fl)
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
			int ilen=quick_pow(len,MOD-2);
			for (i=0;i<len;i++) c[i]=(1ll*c[i]*ilen)%MOD;
		}
	}
}

int I2,I3,I6,I24;

int A[MAXN+48],P[MAXN+48],Q[MAXN+48],B[MAXN+48];

//A(x)=x(A(x)^3/6+A(x)A(x^2)/2+A(x^3)/3)
inline void calc(int l,int r)
{
	if (l+1==r) return;
	int mid=(l+r)>>1,len=r-l;
	calc(l,mid);
	static int tmp[MAXN+48],a[MAXN+48],C1[MAXN+48],C2[MAXN+48];
	poly::init(len<<1);
	memset(a,0,poly::len*sizeof(int));for (register int i=l;i<mid;i++) a[i-l]=A[i];
	memset(C1,0,poly::len*sizeof(int));for (register int i=0;i<len;i++) C1[i]=A[i];
	memset(C2,0,poly::len*sizeof(int));for (register int i=0;i*2<len;i++) C2[i*2]=A[i];
	//A(x^3)
	for (register int i=l;i*3+1<r;i++) if (i*3+1>=mid) A[i*3+1]=add(A[i*3+1]+(1ll*A[i]*I3)%MOD);
	poly::ntt(a,1);poly::ntt(C1,1);poly::ntt(C2,1);
	//A(x)^3
	for (register int i=0;i<poly::len;i++) tmp[i]=(1ll*a[i]*C1[i]%MOD*C1[i]%MOD);
	poly::ntt(tmp,-1);
	for (register int i=mid;i<r;i++) A[i]=add(A[i]+1ll*tmp[i-l-1]*(l?I2:I6)%MOD);
	//A(x)A(x^2)
	for (register int i=0;i<poly::len;i++) tmp[i]=(1ll*a[i]*C2[i])%MOD;
	poly::ntt(tmp,-1);
	for (register int i=mid;i<r;i++) A[i]=add(A[i]+1ll*tmp[i-l-1]*I2%MOD);
	calc(mid,r);
}

inline void init()
{
	int n=1e5+1;
	I2=quick_pow(2,MOD-2);I3=quick_pow(3,MOD-2);I6=quick_pow(6,MOD-2);I24=quick_pow(24,MOD-2);
	//calc A(x)
	A[0]=1;calc(0,n);
	static int A1[MAXN+48],A2[MAXN+48],A3[MAXN+48],A4[MAXN+48];
	for (register int i=0;i<n;i++) A1[i]=A2[i*2]=A3[i*3]=A4[i*4]=A[i];
	poly::init(n*4);
	poly::ntt(A1,1);poly::ntt(A2,1);poly::ntt(A3,1);poly::ntt(A4,1);
	//calc P(x)
	for (register int i=0;i<poly::len;i++)
	{
		P[i]=1ll*A1[i]*A1[i]%MOD*A1[i]%MOD*A1[i]%MOD;
		P[i]=add(P[i]+6ll*A1[i]%MOD*A1[i]%MOD*A2[i]%MOD);
		P[i]=add(P[i]+3ll*A2[i]%MOD*A2[i]%MOD);
		P[i]=add(P[i]+8ll*A1[i]%MOD*A3[i]%MOD);
		P[i]=add(P[i]+6ll*A4[i]%MOD);
		P[i]=(1ll*P[i]*I24)%MOD;
	}
	poly::ntt(P,-1);
	for (register int i=n-2;i>=0;i--) P[i+1]=P[i];P[0]=1;
	//calc Q(x)
	for (register int i=0;i<poly::len;i++) Q[i]=(1ll*add(1ll*sub(A1[i]-1)*sub(A1[i]-1)%MOD+sub(A2[i]-1))*I2)%MOD;
	poly::ntt(Q,-1);
	//calc B(x)
	for (register int i=0;i<n;i++) B[i]=add(sub(P[i]-Q[i])+(!(i&1)*A[i>>1]));
}

int main ()
{
	//freopen ("a.in","r",stdin);
	//freopen ("a.out","w",stdout);
	poly::init_w();
	init();int ca,x;io.Get(ca);
	int a[10];memset(a,0,sizeof(a));a[0]=1;a[1]=2;
	int b[10];memset(b,0,sizeof(b));b[0]=1;b[1]=2;b[2]=1;
	poly::init(4);
	cerr<<poly::len<<endl;
	poly::ntt(a,1);poly::ntt(b,1);
	int c[10];
	for (int i=0;i<poly::len;i++) c[i]=(1ll*a[i]*b[i])%MOD;
	poly::ntt(c,-1);
	for (int i=0;i<=3;i++) cerr<<c[i]<<' ';
	cerr<<endl;
	while (ca--)
	{
		io.Get(x);
		io.Print(B[x],' ');io.Print(A[x],'\n');
	}
	io.flush();return 0;
}
