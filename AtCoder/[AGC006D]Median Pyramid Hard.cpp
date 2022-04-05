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
int a[MAXN+48],b[MAXN+48];

int main ()
{
	int i;n=getint();
	for (i=1;i<=n*2-1;i++) a[i]=getint();
	int l=1,r=n*2-1,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		for (i=1;i<=n*2-1;i++) if (a[i]<=mid) b[i]=0; else b[i]=1;
		int L=n,R=n,res;
		while (b[L]!=b[L-1] && b[R]!=b[R+1] && L>=2) L--,R++;
		if (L==1) res=b[1]; else if (b[L]==b[L-1]) res=b[L]; else res=b[R];
		if (!res) r=mid-1; else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
