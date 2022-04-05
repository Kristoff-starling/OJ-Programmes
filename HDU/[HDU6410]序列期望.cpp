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

const int MAXN=100;
const int INV=500000004;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

inline int quick_pow(int x,int y)
{
	int res=1;
	while (y)
	{
		if (y&1) res=(1ll*res*x)%MOD,y--;
		x=(1ll*x*x)%MOD,y>>=1;
	}
	return res;
}

int n;
int L[MAXN+48],R[MAXN+48];
int maxn,minn;

int dp[MAXN+48][2];

int main ()
{
	int ca;io.Get(ca);int i;
	while (ca--)
	{
		io.Get(n);maxn=minn=0;
		for (i=1;i<=n;i++) io.Get(L[i]),io.Get(R[i]),maxn=max(maxn,R[i]),minn=max(minn,L[i]);
		int ans=0;
		for (register int h=minn;h<=maxn;h++)
		{
			dp[0][0]=1;
			for (i=1;i<=n;i++)
				if (R[i]<h)
				{
					dp[i][0]=(1ll*dp[i-1][0]*((1ll*(h-L[i]+1+h-R[i]+1))%MOD*(R[i]-L[i]+1)%MOD*INV%MOD))%MOD;
					dp[i][1]=(1ll*dp[i-1][1]*((1ll*(h-L[i]+1+h-R[i]+1))%MOD*(R[i]-L[i]+1)%MOD*INV%MOD))%MOD;
				}
				else
				{
					dp[i][0]=(1ll*dp[i-1][0]*((1ll*(h-L[i]+1+h-(h-1)+1))%MOD*(h-1-L[i]+1)%MOD*INV%MOD))%MOD;
					dp[i][1]=(1ll*dp[i-1][1]*((1ll*(h-L[i]+1+h-h+1))%MOD*(h-L[i]+1)%MOD*INV%MOD))%MOD;
					dp[i][1]=add(dp[i][1]+dp[i-1][0]);
				}
			ans=add(ans+dp[n][1]);
		}
		for (i=1;i<=n;i++) ans=(1ll*ans*quick_pow(R[i]-L[i]+1,MOD-2))%MOD;
		io.Print(ans);
	}
	io.flush();return 0;
}
