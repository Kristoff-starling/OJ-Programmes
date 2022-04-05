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

int n,p;

inline LL add(LL x) {if (x>=p) x-=p;return x;}
inline LL sub(LL x) {if (x<0) x+=p;return x;}

const int base=20010;
LL dp[2][101][40048];

int main ()
{
	int ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(p);
		memset(dp,0,sizeof(dp));
		dp[0][0][base]=1;
		int cur=0,nxt=1;
		for (register int i=1;i<=n;i++)
		{
			for (register int j=0;j<=i;j++)
				for (register int k=base-i*i;k<=base+i*i;k++)
					if (dp[cur][j][k])
					{
						dp[nxt][j+1][k-i-i]=add(dp[nxt][j+1][k-i-i]+dp[cur][j][k]);
						dp[nxt][j][k]=add(dp[nxt][j][k]+(1ll*dp[cur][j][k]*(2*j+1))%p);
						if (j) dp[nxt][j-1][k+i+i]=add(dp[nxt][j-1][k+i+i]+1ll*dp[cur][j][k]*j%p*j%p);
						dp[cur][j][k]=0;
					}
			cur^=1;nxt^=1;
		}
		for (register int i=base;i<=base+n*n-1;i++) io.Print(dp[cur][0][i],(i==base+n*n-1)?'\n':' ');
	}
	io.flush();return 0;
}
