#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define uint unsigned int
#define ull unsigned long long
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

template<typename T> inline void Get(T &x)
{
	T res;bool f;char ch;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	x=(f?res:-res);
}

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T gcd(T x,T y) {return ((!y)?x:gcd(y,x%y));}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Sub(int &x,int y) {x=sub(x-y);}

const int MAXN=100;

int n,m;
int a[MAXN+48][MAXN+48];
int dp[MAXN+48][100048];

inline int getmask(int Mask,int pos) {return Mask>>((pos-1)<<1)&3;}
inline void Set(int &Mask,int pos,int val)
{
	if (((Mask&(1<<((pos-1)<<1)))?1:0)^(val&1)) Mask^=(1<<((pos-1)<<1));
	if (((Mask&(1<<((pos-1)<<1|1))?1:0))^((val&2)?1:0)) Mask^=(1<<((pos-1)<<1|1));
}

int tot;int A[48];
inline void getmap(int Mask)
{
	tot=0;
	for (register int i=1;i<=m;i++)
	{
		int w=getmask(Mask,i);
		if (!w) A[i]=0;
		else if (w==1)
			A[i]=++tot;
		else
			A[i]=A[i-1];
	}
}

int B[48];
inline bool getnxt(int id,int extend)
{
	for (register int i=1;i<=m;i++)
		if (A[i]==0) B[i]=0;
		else if (extend&(1<<(A[i]-1)))
		{
			if (!a[id][i]) return false;
			B[i]=A[i];
		}
		else B[i]=0;
	return true;
}

inline Pair newMask(int id)
{
	int tt=tot;
	for (register int i=1;i<=m;i++)
		if (a[id][i] && !B[i])
			if (i==1 || B[i-1]<=tot) B[i]=++tt; else B[i]=B[i-1];
	int rMask=0;
	for (register int i=1;i<=m;i++)
		if (B[i])
			if (i==1 || B[i]!=B[i-1]) Set(rMask,i,1); else Set(rMask,i,2);
	return mp(rMask,tt-tot);
}

int main ()
{
	Get(n);Get(m);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=m;j++)
			Get(a[i][j]);
	for (register int i=0;i<=n;i++)
		for (register int Mask=0;Mask<=(1<<(m<<1))-1;Mask++)
			dp[i][Mask]=INF;
	dp[0][0]=0;
	for (register int i=0;i<=n-1;i++)
		for (register int Mask=0;Mask<=(1<<(m<<1))-1;Mask++)
			if (dp[i][Mask]<INF)
			{
				getmap(Mask);
				for (register int extend=0;extend<=(1<<tot)-1;extend++)
				{
					bool f=getnxt(i+1,extend);
					if (!f) continue;
					Pair res=newMask(i+1);
					check_min(dp[i+1][res.x],dp[i][Mask]+res.y);
				}
			}
	int ans=INF;
	for (register int Mask=0;Mask<=(1<<(m<<1))-1;Mask++) check_min(ans,dp[n][Mask]);
	printf("%d\n",ans);return 0;
}
