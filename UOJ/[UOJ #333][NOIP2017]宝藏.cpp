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

int n,m;
int ga[48][48];
int d[48][5048],dist[5048][5048];
int pw[5048];
int dp[48][5048];

int main ()
{
#ifdef LOCAL
	double TIME=clock();
	freopen ("a.in","r",stdin);
	freopen ("a.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	io.Get(n);io.Get(m);
	for (register int i=1;i<=n;i++)
		for (register int j=1;j<=n;j++)
			ga[i][j]=INF;
	int x,y,c;
	for (register int i=1;i<=m;i++)
	{
		io.Get(x);io.Get(y);io.Get(c);
		check_min(ga[x][y],c);check_min(ga[y][x],c);
	}
	for (register int i=1;i<=n;i++) pw[1<<(i-1)]=i;
	for (register int i=1;i<=n;i++)
		for (register int Mask=1;Mask<=(1<<n)-1;Mask++)
			if (!(Mask&(1<<(i-1))))
			{
				d[i][Mask]=INF;
				for (register int cur=Mask;cur;cur^=LOWBIT(cur)) check_min(d[i][Mask],ga[pw[LOWBIT(cur)]][i]);
			}
	for (register int Mask=1;Mask<(1<<n)-1;Mask++)
	{
		register int R=((1<<n)-1)^Mask;
		for (register int sub=R;sub;sub=(sub-1)&R)
			for (register int cur=sub;cur;cur^=LOWBIT(cur))
			{
				if (d[pw[LOWBIT(cur)]][Mask]>=INF)
				{
					dist[Mask][sub]=INF;
					break;
				}
				dist[Mask][sub]+=d[pw[LOWBIT(cur)]][Mask];
			}
	}
	for (register int i=1;i<=n;i++)
		for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
			dp[i][Mask]=INF;
	for (register int i=1;i<=n;i++) dp[1][1<<(i-1)]=0;
	for (register int i=1;i<=n-1;i++)
		for (register int Mask=0;Mask<=(1<<n)-1;Mask++)
			if (dp[i][Mask]<INF)
			{
				// cerr<<i<<' '<<Mask<<' '<<dp[i][Mask]<<endl;
				register int R=((1<<n)-1)^Mask;
				for (register int sub=R;sub;sub=(sub-1)&R)
					if (dist[Mask][sub]<INF)
						check_min(dp[i+1][Mask|sub],dp[i][Mask]+dist[Mask][sub]*i);
			}
	int ans=INF;
	for (register int i=1;i<=n;i++) check_min(ans,dp[i][(1<<n)-1]);
	io.Print(ans,'\n');
	io.flush();
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-TIME)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}