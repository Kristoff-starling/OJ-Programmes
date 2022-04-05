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
inline int quick_pow(int x,int y) {int res=1;while (y) {if (y&1) res=1ll*res*x%MOD;x=1ll*x*x%MOD;y>>=1;}return res;}
inline int quick_pow(int x,int y,int MO) {int res=1;while (y) {if (y&1) res=1ll*res*x%MO;x=1ll*x*x%MO;y>>=1;}return res;}

int n,m,k;char a[148][148];int table[348];
int rowodd[148][4],roweven[148][4],colodd[148][4],coleven[148][4];
int dp[58][2548][4][4],DP[58][58][4];

class ColorfulTiles
{
	inline int calc_row()
	{
		if (n<2) return 0;
		if (m<2)
		{
			memset(DP,0,sizeof(DP));
			for (register int i=0;i<=3;i++)
				DP[1][table[a[1][1]]!=i][i]=1;
			for (register int i=1;i<=n-1;i++)
				for (register int j=0;j<=min(i,k);j++)
					for (register int col=0;col<=3;col++)
						if (DP[i][j][col])
							for (register int nxt=0;nxt<=3;nxt++)
								if (col!=nxt) Add(DP[i+1][j+(table[a[i+1][1]]!=nxt)][nxt],DP[i][j][col]);
			int res=0;
			for (register int j=0;j<=min(n,k);j++)
				for (register int col=0;col<=3;col++)
					res=add(res+DP[n][j][col]);
			return res;
		}
		memset(dp,0,sizeof(dp));
		for (register int i=0;i<=3;i++)
			for (register int j=0;j<=3;j++)
				if (i!=j) dp[1][m-rowodd[1][i]-roweven[1][j]][i][j]=1;
		for (register int i=1;i<=n-1;i++)
			for (register int j=0;j<=min(i*m,k);j++)
				for (register int col1=0;col1<=3;col1++)
					for (register int col2=0;col2<=3;col2++)
						if (dp[i][j][col1][col2])
							for (register int nxt1=0;nxt1<=3;nxt1++)
								if (nxt1!=col1 && nxt1!=col2)
								{
									register int nxt2=6-col1-col2-nxt1;
									Add(dp[i+1][j+m-rowodd[i+1][nxt1]-roweven[i+1][nxt2]][nxt1][nxt2],dp[i][j][col1][col2]);
								}
		int res=0;
		for (register int j=0;j<=min(n*m,k);j++)
			for (register int col1=0;col1<=3;col1++)
				for (register int col2=0;col2<=3;col2++)
					if (dp[n][j][col1][col2]) Add(res,dp[n][j][col1][col2]);
		return res;
	}
	inline int calc_col()
	{
		if (m<2) return 0;
		if (n<2)
		{
			memset(DP,0,sizeof(DP));
			for (register int i=0;i<=3;i++)
				DP[1][table[a[1][1]]!=i][i]=1;
			for (register int i=1;i<=m-1;i++)
				for (register int j=0;j<=min(i,k);j++)
					for (register int col=0;col<=3;col++)
						if (DP[i][j][col])
							for (register int nxt=0;nxt<=3;nxt++)
								if (col!=nxt)
									Add(DP[i+1][j+(table[a[1][i+1]]!=nxt)][nxt],DP[i][j][col]);
			int res=0;
			for (register int j=0;j<=min(m,k);j++)
				for (register int col=0;col<=3;col++)
					Add(res,DP[m][j][col]);
			return res;
		}
		memset(dp,0,sizeof(dp));
		for (register int i=0;i<=3;i++)
			for (register int j=0;j<=3;j++)
				if (i!=j) dp[1][n-colodd[1][i]-coleven[1][j]][i][j]=1;
		for (register int i=1;i<=m-1;i++)
			for (register int j=0;j<=min(i*n,k);j++)
				for (register int col1=0;col1<=3;col1++)
					for (register int col2=0;col2<=3;col2++)
						if (dp[i][j][col1][col2])
							for (register int nxt1=0;nxt1<=3;nxt1++)
								if (nxt1!=col1 && nxt1!=col2)
								{
									register int nxt2=6-col1-col2-nxt1;
									Add(dp[i+1][j+n-colodd[i+1][nxt1]-coleven[i+1][nxt2]][nxt1][nxt2],dp[i][j][col1][col2]);
								}
		int res=0;
		for (register int j=0;j<=min(n*m,k);j++)
			for (register int col1=0;col1<=3;col1++)
				for (register int col2=0;col2<=3;col2++)
					if (dp[m][j][col1][col2]) Add(res,dp[m][j][col1][col2]);
		return res;
	}
	inline int calc_repeat()
	{
		if (n<2 || m<2) return 0;
		int c[2][2],res=0;
		for (c[1][1]=0;c[1][1]<=3;c[1][1]++)
			for (c[1][0]=0;c[1][0]<=3;c[1][0]++)
				if (c[1][1]!=c[1][0])
					for (c[0][1]=0;c[0][1]<=3;c[0][1]++)
						if (c[0][1]!=c[1][1] && c[0][1]!=c[1][0])
						{
							c[0][0]=6-c[1][1]-c[1][0]-c[0][1];
							int cnt=0;
							for (register int i=1;i<=n;i++)
								for (register int j=1;j<=m;j++)
									cnt+=(table[a[i][j]]!=c[i&1][j&1]);
							if (cnt<=k) res++;
						}
		return res;
	}
	public:
		inline int theCount(vector<string> room,int K)
		{
			n=int(room.size());m=int(room[0].size());k=K;
			if (n==1 && m==1) return (!k)?1:4;
			table['R']=0;table['G']=1;table['B']=2;table['Y']=3;
			memset(rowodd,0,sizeof(rowodd));memset(roweven,0,sizeof(roweven));
			memset(colodd,0,sizeof(colodd));memset(coleven,0,sizeof(coleven));
			for (register int i=1;i<=n;i++)
				for (register int j=1;j<=m;j++)
				{
					a[i][j]=room[i-1][j-1];
					if (j&1) rowodd[i][table[a[i][j]]]++; else roweven[i][table[a[i][j]]]++;
					if (i&1) colodd[j][table[a[i][j]]]++; else coleven[j][table[a[i][j]]]++;
				}
			return sub(add(calc_row()+calc_col())-calc_repeat());
		}
};

#ifdef LOCAL
int main ()
{
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
	int nn,kk;string s;vector<string> ss;
	ColorfulTiles A;
	while (cin>>nn>>kk)
	{
		ss.clear();
		for (register int i=1;i<=nn;i++) cin>>s,ss.pb(s);
		cout<<A.theCount(ss,kk)<<endl;
	}
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif