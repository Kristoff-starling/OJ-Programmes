#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
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

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=998244353;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rlen,wlen;
	fastio () {rlen=wlen=0;}
	inline char Getchar()
	{
		if (rlen==S) rlen=0,fread(rbuf,1,S,stdin);
		return rbuf[rlen++];
	}
	template <class T> inline void Get(T &x)
	{
		T res=0;char ch;bool f;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=res;
	}
	inline void flush() {fwrite(wbuf,1,wlen,stdout);rlen=0;}
	inline void Writechar(char ch)
	{
		wbuf[wlen++]=ch;
		if (wlen==S) flush();
	}
	template <class T> inline void Print(T res,char ch)
	{
		char s[48];int pt;
		if (res==0)
		{
			pt=1;
			s[1]='0';
		}
		else
		{
			bool f=true;if (res<0) f=false,res=-res;
			pt=0;while (res) s[++pt]=res%10+'0',res/=10;
			if (!f) s[++pt]='-';
		}
		while (pt>=1) Writechar(s[pt--]);
		Writechar(ch);
	}
}io;

LL dp[11][20][11],g[11][20][11];

inline LL solve(int Fmax,int num,int last)
{
	if (dp[Fmax][num][last]!=-1) return dp[Fmax][num][last];
	if (num==0)
	{
		if (Fmax==0) {dp[Fmax][num][last]=1;g[Fmax][num][last]=0;return 1;}
		if (Fmax>last) {dp[Fmax][num][last]=1;g[Fmax][num][last]=last-Fmax+10;return 1;}
		else {dp[Fmax][num][last]=2;g[Fmax][num][last]=10-Fmax;return 2;}
	}
	dp[Fmax][num][last]=0;
	int curFmax,curlast=last;
	for (register int i=9;i>=0;i--)
	{
		dp[Fmax][num][last]+=solve(max(Fmax,i),num-1,curlast);
		curlast=g[max(Fmax,i)][num-1][curlast];
	}
	g[Fmax][num][last]=curlast;
	return dp[Fmax][num][last];
}

inline void init_dp()
{
	memset(dp,-1,sizeof(dp));
	for (register int i=0;i<=9;i++)
		for (register int j=0;j<=18;j++)
			for (register int k=0;k<=9;k++)
				dp[i][j][k]=solve(i,j,k);
}

int bit[48];int len;
int Fmax,num,last;
int smax[48];

int main ()
{
	init_dp();LL n;io.Get(n);
	if (!n) {printf("0\n");return 0;}
	for (register LL nn=n;nn;nn/=10) bit[++len]=nn%10;
	last=bit[1];
	for (register int i=2;i<=len && bit[i]==9;i++,num++);
	smax[len+1]=0;
	for (register int i=len;i>=1;i--) smax[i]=max(smax[i+1],bit[i]);
	Fmax=smax[num+2];LL ans=0;int cnt=0;
	if (Fmax==0) {io.Print(dp[0][num][last],'\n');io.flush();return 0;}
	for (register int i=num+2;i<=len;)
	{
		for (register int j=bit[i];j>=0;j--)
		{
			ans+=dp[max(smax[i+1],j)][num+cnt][last];
			last=g[max(smax[i+1],j)][num+cnt][last];
		}
		bit[i]=0;
		while (i<=len && !bit[i]) cnt++,i++;
		if (i>len) break; else bit[i]--;
	}
	io.Print(ans,'\n');
	io.flush();return 0;
}
