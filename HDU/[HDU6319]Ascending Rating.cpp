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

const int MAXN=1e7;

int n,m,k,P,Q,R,MO;
int a[MAXN+48];
int head,tail;Pair q[MAXN+48];
LL A,B;

int main ()
{
	int i,ca;ca=getint();
	while (ca--)
	{
		n=getint();m=getint();k=getint();P=getint();Q=getint();R=getint();MO=getint();
		for (i=1;i<=k;i++) a[i]=getint();
		for (i=k+1;i<=n;i++) a[i]=((1ll*P*a[i-1])+(1ll*Q*i+R))%MO;
		head=1;tail=0;A=0;B=0;
		for (i=n;i>=n-m+1;i--)
		{
			while (tail-head+1 && q[tail].x<=a[i]) tail--;
			q[++tail]=mp(a[i],i);
		}
		A+=(q[head].x^(n-m+1));B+=((tail-head+1)^(n-m+1));
		for (i=n-m;i>=1;i--)
		{
			if (q[head].y==i+m) head++;
			while (tail-head+1 && q[tail].x<=a[i]) tail--;
			q[++tail]=mp(a[i],i);
			A+=(q[head].x^i);B+=((tail-head+1)^i);
		}
		printf("%lld %lld\n",A,B);
	}
	return 0;
}
