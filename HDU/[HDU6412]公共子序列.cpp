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

const int MAXN=1000;

inline int add(int x) {if (x>=MOD) x-=MOD;return x;}
inline int sub(int x) {if (x<0) x+=MOD;return x;}

int n,k;
int a[6][MAXN+48];
vector<int> v[6][MAXN+48];

struct node
{
	int pos[6];
	inline bool operator < (const node &other) const
	{
		for (register int i=1;i<=k;i++) if (pos[i]>=other.pos[i]) return false;
		return true;
	}
}sta[MAXN*10+48],ins;int tot;

int dp[MAXN*10+48];

inline void dfs(int step,int type)
{
	if (step==k+1)
	{
		sta[++tot]=ins;
		return;
	}
	for (register int i=0;i<int(v[step][type].size());i++)
		ins.pos[step]=v[step][type][i],dfs(step+1,type);
}

inline int solve(int cur)
{
	if (dp[cur]!=-1) return dp[cur];
	dp[cur]=1;
	for (register int i=1;i<=tot;i++)
		if (sta[i]<sta[cur]) dp[cur]=add(dp[cur]+solve(i));
	return dp[cur];
}

inline void Clear()
{
	for (register int i=1;i<=k;i++)
		for (register int j=1;j<=n;j++)
			v[i][j].clear();
}

int main ()
{
	int i,j,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(k);io.Get(n);Clear();
		for (i=1;i<=k;i++)
			for (j=1;j<=n;j++)
				io.Get(a[i][j]),v[i][a[i][j]].pb(j);
		tot=0;
		for (i=1;i<=n;i++) dfs(1,i);
		memset(dp,-1,sizeof(dp));int ans=0;
		for (i=1;i<=tot;i++) ans=add(ans+solve(i));
		io.Print(ans);
	}
	io.flush();return 0;
}
