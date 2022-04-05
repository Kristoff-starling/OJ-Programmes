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
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template<typename T> inline void check_max(T &x,T cmp) {x=max(x,cmp);}
template<typename T> inline void check_min(T &x,T cmp) {x=min(x,cmp);}
template<typename T> inline T myabs(T x) {return x>=0?x:-x;}
template<typename T> inline T gcd(T x,T y) {return y==0?x:gcd(y,x%y);}
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int add(int x,int MO) {if (x>=MO) x-=MO;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline int sub(int x,int MO) {if (x<0) x+=MO;return x;}
inline void Add(int &x,int y) {x=add(x+y);}
inline void Add(int &x,int y,int MO) {x=add(x+y,MO);}
inline void Sub(int &x,int y) {x=sub(x-y);}
inline void Sub(int &x,int y,int MO) {x=sub(x-y,MO);}
template<typename T> inline int quick_pow(int x,T y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
template<typename T> inline int quick_pow(int x,T y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int dp[148][148],n;
vector<int> coin;
vector<int> ans[148][148];

class ChangeOptimizer
{
	map<int,int> P;
	inline void solve(int x,int y)
	{
		if (dp[x][y]!=-1) return;
		if (x==0)
		{
			dp[x][y]=coin[y]-1;
			ans[x][y][0]=coin[y]-1;
			return;
		}
		dp[x][y]=INF;
		if ((coin[y]-1)%coin[x]==coin[x]-1)
		{
			int num=(coin[y]-1)/coin[x];
			solve(x-1,x);
			if (dp[x-1][x]!=-2)
			{
				dp[x][y]=dp[x-1][x]+num;
				ans[x][y]=ans[x-1][x];ans[x][y][x]=num;
			}
		}
		solve(x-1,y);
		if (dp[x-1][y]!=-2 && dp[x-1][y]<dp[x][y])
		{
			dp[x][y]=dp[x-1][y];
			ans[x][y]=ans[x-1][y];
		}
		if (dp[x][y]>=INF) dp[x][y]=-2;
	}
	vector<int> Ans;
	public:
		inline vector<int> fewestCoins(vector<int> Coin,int val)
		{
			P.clear();
			for (register int i=0;i<int(Coin.size());i++) P[Coin[i]]=i;
			coin=Coin;
			sort(coin.begin(),coin.end());
			while (coin.back()>val) coin.pop_back();
			coin.pb(val+1);
			n=int(coin.size());
			for (register int i=0;i<=n-1;i++)
				for (register int j=0;j<=n-1;j++)
					ans[i][j].resize(n-1,0);
			memset(dp,-1,sizeof(dp));
			solve(n-2,n-1);
			int N=int(Coin.size());
			Ans.resize(N,0);
			for (register int i=0;i<=n-2;i++)
				Ans[P[coin[i]]]=ans[n-2][n-1][i];
			return Ans;
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	ChangeOptimizer A;
	int val,nn;vector<int> vv;
	while (cin>>nn>>val)
	{
		vv.clear();int x;
		for (register int i=1;i<=nn;i++) cin>>x,vv.pb(x);
		vector<int> res=A.fewestCoins(vv,val);
		for (register int i=0;i<int(res.size());i++) cout<<res[i]<<' ';
		cout<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif