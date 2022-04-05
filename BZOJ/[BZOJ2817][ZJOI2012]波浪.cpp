// I'll always miss you like a darling.
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define ull unsigned long long
#define uint unsigned int
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) ((x) & (-x))
#define rep(i,l,r) for (register int i=int(l);i<=int(r);i++)
#define Rep(i,l,r) for (register int i=int(l);i<int(r);i++)
#define REP(i,r,l) for (register int i=int(r);i>=int(l);i--)

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
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

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T sub(T x,int MO) {if (x<0) x+=MO;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline T mul(T x,T y,int MO) {return 1ll*x*y%MO;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Add(T &x,T y,int MO) {x=add(x+y,MO);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Sub(T &x,T y,int MO) {x=sub(x-y,MO);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}
template<typename T> inline void Mul(T &x,T y,int MO) {x=mul(x,y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

const int M=4500;

int n,m,k;
double dp1[2][101][2*M+1][3];
__float128 dp2[2][101][2*M+1][3];

template<typename T> inline void print(T res,int x)
{
	T add=5;rep(i,1,x+1) add*=0.1;res+=add;
	printf("%d.",int(res));res=(res-int(res))*10;
	while (x--)
	{
		printf("%d",int(res));
		res=(res-int(res))*10;
	}
}

template<typename T> inline void solve(T dp[2][101][2*M+1][3])
{
	memset(dp,0,sizeof(dp));int base=M;
	dp[0][0][base][0]=1;int cur=0,nxt=1;
	rep(i,1,n)
	{
		rep(j,0,i-1) rep(k,base-min(M,i*i),base+min(M,i*i)) rep(l,0,2)
		if (dp[cur][j][k][l])
		{
			//join two parts together
			if (j>1) dp[nxt][j-1][k+i*2][l]+=dp[cur][j][k][l]*(j-1);
			//create a new part
			dp[nxt][j+1][k-i*2][l]+=dp[cur][j][k][l]*(j+1-l);
			//join to a part
			dp[nxt][j][k][l]+=dp[cur][j][k][l]*(j*2-l);
			//create a terminal
			if (l<2) dp[nxt][j+1][k-i][l+1]+=dp[cur][j][k][l]*(2-l);
			//join to a part and become a terminal
			if (l<2) dp[nxt][j][k+i][l+1]+=dp[cur][j][k][l]*(2-l);
			dp[cur][j][k][l]=0;
		}
		cur^=1;nxt^=1;
	}
	T res=0;
	rep(k,base+m,base+M) res+=dp[cur][1][k][2];
	rep(i,1,n) res/=i;
	print(res,k);
}

int main ()
{
#ifndef ONLINE_JUDGE
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	Get(n,m,k);
	if (k<=8) solve(dp1); else solve(dp2);
#ifndef ONLINE_JUDGE
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
