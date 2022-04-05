#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define pLL pair<LL,LL>
#define LOWBIT(x) ((x) & (-x))

const int INF=2e9;
const LL LINF=2e16;
const int magic=548;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	bool f;char ch;T res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:(-res));
}

template<typename T1,typename ...T2> inline void Get(T1 &x,T2 &...y) {Get(x);Get(y...);}

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=3e5;

int n,X,Y;
int dp1[MAXN+48],dp2[2][MAXN+48],sum[MAXN+48];

inline int calc(int x)
{
	memset(dp1,0,sizeof(dp1));dp1[0]=1;
	for (register int i=x;i<=magic;i++)
		for (register int j=1;j<=n;j++)
		{
			if (i==j) Add(dp1[j],1);
			if (j-i>0) Add(dp1[j],dp1[j-i]);
		}
	memset(sum,0,sizeof(sum));memset(dp2,0,sizeof(dp2));
	dp2[0][0]=1;sum[0]=1;int cur=1,pre=0,minn=max(magic+1,x);
	for (register int i=1;i<=n/minn;i++)
	{
		memset(dp2[cur],0,sizeof(dp2[cur]));
		for (register int j=1;j<=n;j++)
		{
			if (j-i>=0) Add(dp2[cur][j],dp2[cur][j-i]);
			if (j-minn>=0) Add(dp2[cur][j],dp2[pre][j-minn]);
			Add(sum[j],dp2[cur][j]);
		}
		cur^=1;pre^=1;
	}
	int res=0;
	for (register int i=0;i<=n;i++) Add(res,1ll*dp1[i]*sum[n-i]%MOD);
	return res;
}

int main ()
{
#ifndef ONLINE_JUDGE
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
#endif
	Get(X,Y,n);
	printf("%d\n",sub(calc(X)-calc(Y+1)));
	return 0;
}
