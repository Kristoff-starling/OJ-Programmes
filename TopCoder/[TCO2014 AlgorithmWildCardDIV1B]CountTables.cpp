#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LD long double
#define uint unsigned int
#define ull unsigned long long
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

template<typename T> inline void check_max(T &x,T y) {x=(x>y?x:y);}
template<typename T> inline void check_min(T &x,T y) {x=(x<y?x:y);}
template<typename T> inline T add(T x) {if (x>=MOD) x-=MOD;return x;}
template<typename T> inline T sub(T x) {if (x<0) x+=MOD;return x;}
template<typename T> inline T mul(T x,T y) {return 1ll*x*y%MOD;}
template<typename T> inline void Add(T &x,T y) {x=add(x+y);}
template<typename T> inline void Sub(T &x,T y) {x=sub(x-y);}
template<typename T> inline void Mul(T &x,T y) {x=mul(x,y);}

const int MAXN=4000;

int S[MAXN+48][MAXN+48],pw[MAXN+48];
int dp[MAXN+48];

class CountTables
{
	inline void init(int N,int M,int C)
	{
		S[0][0]=1;
		rep(i,1,M) rep(j,1,i) S[i][j]=add(S[i-1][j-1]+mul(j,S[i-1][j]));
		pw[0]=1;rep(i,1,M) pw[i]=mul(pw[i-1],C);
	}
	inline int A(int x,int y)
	{
		if (x<y) return 0;
		int res=1;
		rep(i,0,y-1) Mul(res,x-i);
		return res;
	}
	public:
		inline int howMany(int N,int M,int C)
		{
			init(N,M,C);int ans=0;
			rep(i,1,M)
			{
				dp[i]=A(pw[i],N);
				rep(j,1,i-1) Sub(dp[i],mul(dp[j],S[i][j]));
			}
			return dp[M];
		}
};

/*--- Debug Part ---*/
/*
int main ()
{
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	int nn,mm,cc;
	CountTables A;
	while (cin>>nn>>mm>>cc) cout<<A.howMany(nn,mm,cc)<<endl;
	return 0;
}
*/
