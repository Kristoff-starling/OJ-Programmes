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
#define LOWBIT(x) x & (-x)

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

int n;

int main ()
{
	int ca;ca=getint();
	while (ca--)
	{
		n=getint();
		if (n%3==0)
		{
			LL x=n/3;
			printf("%lld\n",x*x*x);
			continue;
		}
		if (n%4) {puts("-1");continue;}
		LL x=n/2,y=n/4;
		printf("%lld\n",x*y*y);
	}
	return 0;
}
