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
inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}
inline void add(int &x,int y) {x=add(x+y);}
inline void sub(int &x,int y) {x=sub(x-y);}

const int MAXN=700;

char s[MAXN+48];int n;

int dp[MAXN+48][MAXN+48][10][2],ans[MAXN+48][10];
int pw[MAXN+48];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.getstring(s+1);n=strlen(s+1);
	memset(dp,0,sizeof(dp));
	for (register int i=0;i<=9;i++) dp[0][0][i][0]=1;
	for (register int i=0;i<=n-1;i++)
		for (register int j=0;j<=i;j++)
			for (register int k=0;k<=9;k++)
			{
				if (dp[i][j][k][0])
				{
					//to 0
					add(dp[i+1][j+(s[i+1]-'0'>=k)][k][0],dp[i][j][k][0]);
					//to 1
					for (register int nxt=0;nxt<=s[i+1]-'0'-1;nxt++)
						add(dp[i+1][j+(nxt>=k)][k][1],dp[i][j][k][0]);
				}
				if (dp[i][j][k][1])
				{
					for (register int nxt=0;nxt<=9;nxt++)
						add(dp[i+1][j+(nxt>=k)][k][1],dp[i][j][k][1]);
				}
			}
	pw[1]=1;
	for (register int i=2;i<=n;i++) pw[i]=(1ll*pw[i-1]*10+1)%MOD;
	int ans=0;
	for (register int j=0;j<=n;j++)
		for (register int k=1;k<=9;k++)
			add(ans,1ll*add(dp[n][j][k][0]+dp[n][j][k][1])*pw[j]%MOD);
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}