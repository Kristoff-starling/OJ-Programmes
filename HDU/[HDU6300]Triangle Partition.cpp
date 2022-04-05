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

const int MAXN=1e5;

int n;

struct node
{
	int x,y,ind;
	inline bool operator < (const node &other) const {return x<other.x;}
}a[MAXN+48];

int main ()
{
	int ca;ca=getint();int i;
	while (ca--)
	{
		n=getint();
		for (i=1;i<=3*n;i++) a[i].x=getint(),a[i].y=getint(),a[i].ind=i;
		sort(a+1,a+n*3+1);
		for (i=1;i<=n;i++) printf("%d %d %d\n",a[(i-1)*3+1].ind,a[(i-1)*3+2].ind,a[i*3].ind);
	}
	return 0;
}
