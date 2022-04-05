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

const int MAXN=4000;

inline int add (int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub (int x) {if (x<0) x+=MOD;return x;}

int n,m,k;
int dp[MAXN+48][MAXN+48],sum[MAXN+48][MAXN+48];

int main ()
{
	io.Get(n);io.Get(m);io.Get(k);
	dp[0][0]=1;int ans=0;
	for (register int i=0;i<=m;i++) sum[0][i]=1;
	for (register int i=1;i<=n+m;i++)
		for (register int j=0;j<=m;j++)
		{
			dp[i][j]=sub(sum[i-1][j]-((j-(k-1)>0)?sum[i-1][j-(k-1)-1]:0));
			sum[i][j]=(j==0?dp[i][j]:add(sum[i][j-1]+dp[i][j]));
			if (j && j%(k-1)==m%(k-1) && (k-1)*i-j>=0 && (k-1)*i-j<=n-1 && ((k-1)*i-j)%(k-1)==(n-1)%(k-1))
				ans=add(ans+sub(dp[i][j]-dp[i-1][j]));
		}
	io.Print(ans,'\n');
	io.flush();return 0;
}