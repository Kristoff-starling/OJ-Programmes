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

int n,m,K,k;

int a[48][48];
int dp[248][48][48];
int col[1048];

const int MAXM=2e5;

int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int q[MAXM+48],head,tail;

inline int solve()
{
	int Mask,x,y;
	for (Mask=0;Mask<=(1<<K)-1;Mask++)
		for (x=1;x<=n;x++)
			for (y=1;y<=m;y++)
				dp[Mask][x][y]=INF;
	head=1;tail=0;
	for (x=1;x<=n;x++)
		for (y=1;y<=m;y++)
			if (a[x][y]>0)
				dp[1<<(col[a[x][y]]-1)][x][y]=0,q[++tail]=(1<<(col[a[x][y]]-1)),q[++tail]=x,q[++tail]=y;
	while (head<=tail)
	{
		Mask=q[head++];x=q[head++];y=q[head++];
		for (register int dir=0;dir<=3;dir++)
		{
			int xx=x+dx[dir],yy=y+dy[dir];
			if (1<=xx && xx<=n && 1<=yy && yy<=m && a[xx][yy]!=-1)
			{
				int toMask=Mask;
				if (a[xx][yy]>0) toMask|=(1<<(col[a[xx][yy]]-1));
				if (dp[toMask][xx][yy]>dp[Mask][x][y]+1)
				{
					dp[toMask][xx][yy]=dp[Mask][x][y]+1;
					q[++tail]=toMask;q[++tail]=xx;q[++tail]=yy;
				}
			}
		}
	}
	int res=INF;
	for (x=1;x<=n;x++)
		for (y=1;y<=m;y++)
			res=min(res,dp[(1<<K)-1][x][y]);
	return res;
}

int main ()
{
	srand(1968);
	int ca,i,j;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(m);io.Get(K);k=0;
		for (i=1;i<=n;i++)
			for (j=1;j<=m;j++)
				io.Get(a[i][j]),k=max(k,a[i][j]);
		int ti=500,ans=INF;
		while (ti--)
		{
			for (i=1;i<=k;i++) col[i]=rand()%K+1;
			ans=min(ans,solve());
		}
		if (ans>=INF) io.Print(-1,'\n'); else io.Print(ans,'\n');
	}
	io.flush();return 0;
}
