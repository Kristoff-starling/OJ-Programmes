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

const int MAXN=1e5;

int n;
int a[MAXN+48];
int Mask;

int main ()
{
	int i,ca;ca=getint();
	while (ca--)
	{
		int x;Mask=0;
		n=getint();for (i=1;i<=n;i++) x=getint(),Mask^=x;
		for (i=1;i<=n-1;i++) x=getint(),x=getint();
		if (!Mask) puts("D"); else puts("Q");
	}
	return 0;
}
