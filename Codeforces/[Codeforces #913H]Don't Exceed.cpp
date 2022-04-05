#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define x first
#define y second

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48],rpos,wpos,len;
	fastio () {rpos=wpos=len=0;}
	inline char Getchar()
	{
		if (rpos==len) len=fread(rbuf,1,S,stdin),rpos=0;	
		return rbuf[rpos++];
	}
	template <class T> inline T Get(T &res)
	{
		char ch;bool f;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		if (f) res=-res;
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		wbuf[wpos++]=ch;
		if (wpos==S) flush();
	}
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;bool f=false;
		if (!x)
			s[++pt]=0;
		else
		{
			if (x<0) f=true,x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
			if (f) s[++pt]='-';
		}
		while (pt) Writechar(s[pt--]);
	}
}io;

const int MAXN=48;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int inv[2000048];
inline void iniv_inv()
{
	inv[1]=1;
	for (register int i=2;i<=2000000;i++)
		inv[i]=MOD-((long long)(MOD/i)*inv[MOD%i])%MOD;
}

int c[MAXN*2+48][MAXN*2+48];
inline void init_c()
{
	c[0][0]=1;
	for (register int i=1;i<=MAXN*2;i++)
	{
		c[i][0]=c[i][i]=1;
		for (register int j=1;j<=i-1;j++)
			c[i][j]=add(c[i-1][j-1]+c[i-1][j]);
	}
}

struct poly
{
	vector<int> coef;
	poly () {coef.clear();}
	inline poly querF(poly f)
	{
		poly res;res.coef.pb(0);
		for (register int i=0;i<int(f.coef.size());i++)
			res.coef.pb((1ll*f.coef[i]*inv[i+1])%MOD);
		return res;
	}
	inline poly operator + (poly other)
	{
		poly res;
		for (register int i=0;i<max(int(coef.size()),int(other.coef.size()));i++)
		{
			int ad=0;
			if (i<=int(coef.size())-1) ad=add(ad+coef[i]);
			if (i<=int(other.coef.size())-1) ad=add(ad+other.coef[i]);
			res.pb(ad);
		}
		return res;
	}
	inline poly operator - (poly other)
	{
		poly res;
		for (register int i=0;i<max(int(coef.size()),int(other.coef.size()));i++)
		{
			int ad=0;
			if (i<=int(coef.size())-1) ad=add(ad+coef[i]);
			if (i<=int(other.coef.size())-1) ad=sub(ad-other.coef[i]);
			res.pb(ad);
		}
		return res;
	}
	inline poly Move()
	{
		poly res;res.coef.resize(int(coef.size()));
		for (register int i=0;i<int(coef.size());i++)
			for (register int j=i;j>=0;j--) res.coef[i]=add(res.coef[i]+sub((1ll*c[i][j]*coef[i])%MOD*((i-j)&1?-1:1)));
		return res;
	}
};

struct Function
{
	vector<int> pt;
	vector<poly> Poly;
	inline Function Move(int delta)
	{
		for (register int i=0;i<int(pt.size());i++)
			pt[i]++;
		for (register int i=0;i<int(Poly.size());i++) Poly[i]=Poly[i].Move();
	}
	inline Function operator - (Function other)
	{
		Function res;vector<Pair> Pt;Pt.clear();
		for (register int i=0;i<int(pt.size());i++) Pt.pb(mp(pt[i],0));
		for (register int i=0;i<int(other.pt.size());i++) Pt.pb(mp(other.pt[i],1));
		sort(Pt.begin(),Pt.end());
	}
};

int main ()
{
	io.flush();return 0;
}
