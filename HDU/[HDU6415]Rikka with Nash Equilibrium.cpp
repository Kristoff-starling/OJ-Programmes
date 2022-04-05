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
	template <class T> inline void Print(T x)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar('\n');
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

int n,m,K;

inline int add(int x) {if (x>=K) x-=K;return x;}
inline int sub(int x) {if (x<0) x+=K;return x;}

int dp[7000][81][81];

inline int calc_cross(int k,int i,int j)
{
	return i*j-(n*m+1-k);
}

inline int calc_row(int k,int i,int j)
{
	return i*(m-j);
}

inline int calc_col(int k,int i,int j)
{
	return j*(n-i);
}

int main ()
{
	int k,i,j,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(K);
		dp[n*m][1][1]=n*m;
		for (k=n*m;k>=2;k--)
			for (i=1;i<=n;i++)
				for (j=1;j<=m;j++)
					if (dp[k][i][j])
					{
						int nu=calc_cross(k,i,j);
						dp[k-1][i][j]=add(dp[k-1][i][j]+1ll*dp[k][i][j]*nu%K);
						nu=calc_row(k,i,j);
						dp[k-1][i][j+1]=add(dp[k-1][i][j+1]+1ll*dp[k][i][j]*nu%K);
						nu=calc_col(k,i,j);
						dp[k-1][i+1][j]=add(dp[k-1][i+1][j]+1ll*dp[k][i][j]*nu%K);
						dp[k][i][j]=0;
					}
		int ans=0;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				if (dp[1][i][j]) ans=add(ans+dp[1][i][j]),dp[1][i][j]=0;
		io.Print(ans);
	}
	io.flush();return 0;
}
