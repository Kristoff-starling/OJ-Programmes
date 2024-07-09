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

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

const int MAXN=3e5;

int n;
LL a[MAXN+48],b[MAXN+48];
LL sum[MAXN+48];

LL t1[MAXN+48],t2[MAXN+48];

int main ()
{
	n=getint();int i;
	for (i=1;i<=n;i++) a[i]=getint();
	for (i=1;i<=n;i++) b[i]=getint();
	sum[n+1]=0;
	for (i=n;i>=1;i--) sum[i]=sum[i+1]+a[i]+b[i];
	t1[n]=a[n]+b[n]+b[n];
	for (i=n-1;i>=1;i--) t1[i]=t1[i+1]+sum[i+1]+a[i]+b[i]*(n-i+1)*2;
	t2[n]=b[n]+a[n]+a[n];
	for (i=n-1;i>=1;i--) t2[i]=t2[i+1]+sum[i+1]+b[i]+a[i]*(n-i+1)*2;
	LL ans=0,ss=0,cc=0;
	for (i=1;i<=n;i++)
		if (i&1)
		{
			ans=max(ans,ss+t1[i]+sum[i]*cc);
			++cc;
			ss+=a[i]*cc;
			++cc;
			ss+=b[i]*cc;
		}
		else
		{
			ans=max(ans,ss+t2[i]+sum[i]*cc);
			++cc;
			ss+=b[i]*cc;
			++cc;
			ss+=a[i]*cc;
		}
	ans=max(ans,ss);
	printf("%lld\n",ans-sum[1]);
	return 0;
}
