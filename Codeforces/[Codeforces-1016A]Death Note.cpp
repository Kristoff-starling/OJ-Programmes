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

int n,m;

int main ()
{
	n=getint();m=getint();
	int lft=m,x,ans;
	for (register int i=1;i<=n;i++)
	{
		x=getint();
		if (x<lft) {lft-=x;printf("0 ");continue;}
		ans=1;x-=lft;lft=m;
		ans+=x/m;x%=m;
		lft-=x;
		printf("%d ",ans);
	}
	puts("");
	return 0;
}
