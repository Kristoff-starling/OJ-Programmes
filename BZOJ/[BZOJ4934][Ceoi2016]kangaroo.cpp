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

const int MAXN=2000;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int n,S,T;
int dp[MAXN+48][MAXN+48];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	// io.Get(n);io.Get(S);io.Get(T);
	scanf("%d%d%d",&n,&S,&T);
	dp[0][0]=1;
	for (register int i=0;i<=n-1;i++)
		for (register int j=0;j<=i;j++)
			if (dp[i][j])
			{
				// cerr<<i<<' '<<j<<' '<<dp[i][j]<<endl;
				//create a new node
				dp[i+1][j+1]=add(dp[i+1][j+1]+dp[i][j]);
				//add before a node
				if (i+1==S)
				{
					register int valid=j;
					if (i+1>=T && i+1!=n) valid=sub(valid-1);
					dp[i+1][j]=add(dp[i+1][j]+1ll*dp[i][j]*valid%MOD);
				}
				//add after a node
				if (i+1==T)
				{
					register int valid=j;
					if (i+1>=S && i+1!=n) valid=sub(valid-1);
					dp[i+1][j]=add(dp[i+1][j]+1ll*dp[i][j]*valid%MOD);
				}
				//connect two nodes
				if (i+1!=S && i+1!=T && j>=2)
				{
					register int valid=1ll*j*(j-1)%MOD;
					if (i+1>=S) valid=sub(valid-(j-1)); //can't connect a node before S
					if (i+1>=T) valid=sub(valid-(j-1)); //can't connect a node after T
					if (i+1>=S && i+1>=T) valid=add(valid+1); //T-S is deleted twice
					if (i+1>=S && i+1>=T && i+1!=n) valid=sub(valid-1); //S-T is not allowed
					dp[i+1][j-1]=add(dp[i+1][j-1]+1ll*dp[i][j]*valid%MOD);
				}
			}
	// io.Print(dp[n][1],'\n');
	printf("%d\n",dp[n][1]);
	// io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}