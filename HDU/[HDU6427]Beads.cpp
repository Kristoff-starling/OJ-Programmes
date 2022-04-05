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
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

inline LL myabs(LL x) {return x>=0?x:-x;}
inline LL gcd(LL x,LL y) {return y==0?x:gcd(y,x%y);}

inline LL add(LL x,LL MO) {if (x>=MO) x-=MO;return x;}
inline LL sub(LL x,LL MO) {if (x<0) x+=MO;return x;}

inline LL quick_mul(LL x,LL y,LL MO)
{
	LL res=0;x%=MO;
	while (y)
	{
		if (y&1) res=add(res+x,MO),y--;
		x=add(x+x,MO);y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y,LL MO)
{
	LL res=1;x%=MO;
	while (y)
	{
		if (y&1) res=quick_mul(res,x,MO),y--;
		x=quick_mul(x,x,MO);y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y)
{
	LL res=1;x%=MOD;
	while (y)
	{
		if (y&1) res=(res*x%MOD),y--;
		x=(x*x%MOD);y>>=1;
	}
	return res;
}

namespace Pollard_Rho
{
	int lp[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
	LL X[148];
	inline bool Miller_Rabin(LL n)
	{
		for (register int i=0;i<=14;i++)
		{
			if (n==lp[i]) return true;
			if (n%lp[i]==0) return false;
		}
		int ti=10,k=0;LL t=n-1;
		while (!(t&1)) k++,t>>=1;
		while (ti--)
		{
			LL a=rand()%(n-2)+2;
			X[0]=quick_pow(a,t,n);
			for (register int i=1;i<=k;i++)
			{
				X[i]=quick_mul(X[i-1],X[i-1],n);
				if (X[i]==1 && X[i-1]!=1 && X[i-1]!=n-1) return false;
			}
			if (X[k]!=1) return false;
		}
		return true;
	}
	inline LL pollard_rho(LL n,LL a)
	{
		LL x=2,y=2,i=1,k=2,p;
		for (;;)
		{
			i++;
			x=add(quick_mul(x,x,n)+a,n);
			p=gcd(myabs(x-y),n);
			if (p!=1 && p!=n) return p;
			if (x==y) return n;
			if (i==k) y=x,k<<=1;
		}
		return n;
	}
	vector<LL> fac;
	inline void findfc(LL n)
	{
		if (n==1) return;
		if (Miller_Rabin(n)) {fac.pb(n);return;}
		LL p=n;
		while (p==n) p=pollard_rho(n,rand()%(n-1));
		findfc(p);findfc(n/p);
	}
	inline void findfac(LL n,vector<pLL> &fc)
	{
		fac.clear();findfc(n);
		sort(fac.begin(),fac.end());
		fc.clear();
		for (register int i=0;i<int(fac.size());i++)
			if (!int(fc.size()) || fac[i]!=fc.back().x) fc.pb(mp(fac[i],1)); else fc.back().y++;
	}
}

LL n,m;
vector<pLL> fac;int tot;
LL ans;

const int MAXN=1e7;
LL d[MAXN+48],phi[MAXN+48],cnt;

inline void calc()
{
	cnt=1;d[1]=phi[1]=1;
	for (register int i=0;i<int(fac.size());i++)
	{
		int tmp=cnt;
		for (register int j=1;j<=tmp;j++)
		{
			LL cc=fac[i].x;
			for (register int k=1;k<=fac[i].y;k++)
			{
				d[++cnt]=d[j]*cc;
				phi[cnt]=phi[j]*cc/fac[i].x*(fac[i].x-1);
				cc*=fac[i].x;
			}
		}
	}
	for (register int i=1;i<=cnt;i++) ans=add(ans+(phi[i]%MOD)*(gcd(d[i],m)%MOD)%MOD*quick_pow(m,n/d[i])%MOD,MOD);
}

int main ()
{
	int i,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);ans=0;
		Pollard_Rho::findfac(n,fac);tot=int(fac.size());
		//no reverse
		calc();
		//with reverse
		if (n&1)
		{
			ans=add(ans+1ll*quick_pow(m,(n+1)/2,MOD)*(n%MOD)%MOD,MOD);
		}
		else
		{
			ans=add(ans+1ll*quick_pow(m,n/2,MOD)*((n/2)%MOD)%MOD*(m&1?1:2)%MOD,MOD);
			ans=add(ans+1ll*quick_pow(m,n/2+1,MOD)*((n/2)%MOD)%MOD,MOD);
		}
		ans=(1ll*ans*quick_pow(n*2,MOD-2,MOD))%MOD;
		ans=(1ll*ans*quick_pow(m,MOD-2,MOD))%MOD;
		io.Print(ans,'\n');
	}
	io.flush();return 0;
}
