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

const int MAXN=2e5;

int n;
int a[MAXN+48];

int main ()
{
	int i;n=getint();
	for (i=1;i<=n*2;i++) a[i]=getint();
	sort(a+1,a+n*2+1);
	LL minn=LINF;
	LL A=a[n]-a[1],B=a[n*2]-a[n+1];
	minn=A*B;
	for (i=2;i<=n;i++)
	{
		A=a[n+i-1]-a[i];B=a[n*2]-a[1];
		minn=min(minn,A*B);
	}
	printf("%I64d\n",minn);
	return 0;
}
