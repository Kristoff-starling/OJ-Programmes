#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2&...y) {Get(x);Get(y...);}

const int MOD=1e9+7;
const int MAXN=1000;

inline int quick_pow(int x,int y,int MO)
{
	int res=1;
	while (y)
	{
		if (y&1) res=1ll*res*x%MO;
		x=1ll*x*x%MO;y>>=1;
	}
	return res;
}

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

int n,d;

int c[MAXN+48][MAXN+48];

inline void init_c()
{
	c[0][0]=1;
	for (register int i=1;i<=MAXN;i++)
	{
		c[i][0]=c[i][i]=1;
		for (register int j=1;j<=i-1;j++) c[i][j]=add(c[i-1][j]+c[i-1][j-1]);
	}
}

inline int calc(int d)
{
	int res=0;
	for (register int i=0;i<=n;i++)
	{
		int cur=1ll*quick_pow(d,i,MOD-1)*quick_pow(d+1,n-i,MOD-1)%(MOD-1);
		cur=quick_pow(2,cur,MOD);
		if (~i&1) Add(res,1ll*c[n][i]*cur%MOD); else Sub(res,1ll*c[n][i]*cur%MOD);
	}
	return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	init_c();int t;Get(t);
	while (t--)
	{
		Get(n,d);
		printf("%d\n",sub(calc(d)-calc(d-1)));
	}
	return 0;
}
