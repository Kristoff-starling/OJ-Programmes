#include <bits/stdc++.h>
#define LL long long
using namespace std;

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') res=0,f=false; else res=ch-'0',f=true;
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MOD=1e9+7;
LL fac[10000048],sum[10000048],ss[10000048];

inline int mod(int x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

inline void init()
{
	fac[0]=1;int i;
	for (i=1;i<=10000000;i++) fac[i]=(fac[i-1]*i)%MOD;
	sum[0]=1;
	for (i=1;i<=10000000;i++) sum[i]=mod(sum[i-1]+fac[i]);
	ss[0]=sum[0];
	for (i=1;i<=10000000;i++) ss[i]=mod(ss[i-1]+sum[i]);
}

int main ()
{
	init();
	int ca;ca=getint();int n;LL ans;
	while (ca--)
	{
		n=getint();
		ans=mod(2*sum[n-1]-1);
		if (ans>=2) ans=mod(ans-ss[n-2]);
		ans=mod(fac[n]-ans);
		printf("%lld\n",ans);
	}
	return 0;
}

