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

inline int myabs(int x) {return x>=0?x:-x;}

int main ()
{
	int ca;ca=getint();int n;
	while (ca--)
	{
		n=getint();
		int st,ed,x;
		for (register int i=1;i<=n;i++)
		{
			x=getint();
			if (i==1) st=x;
			if (i==n) ed=x;
		}
		printf("%d\n",int(sqrt(myabs(st-ed))));
	}
	return 0;
}
