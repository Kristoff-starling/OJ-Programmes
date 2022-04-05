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

const int MAXN=1e5;

int n;
vector<int> v[MAXN+48];

LL maxn[MAXN+48][2][2],minn[MAXN+48][2][2];
//exist brother; root chosen
int val[MAXN+48];

inline void dfs(int cur)
{
	int i,y;LL maxsum=0,minsum=0,maxdelta=0,mindelta=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i],dfs(y);
		maxsum+=maxn[y][0][0];minsum+=minn[y][0][0];
		maxdelta=max(maxdelta,maxn[y][0][1]-maxn[y][0][0]);
		mindelta=min(mindelta,minn[y][0][1]-minn[y][0][0]);
	}
	maxn[cur][0][0]=maxsum+maxdelta;minn[cur][0][0]=minsum+mindelta;
	maxn[cur][0][1]=maxn[cur][0][0]+val[cur];minn[cur][0][1]=minn[cur][0][0]+val[cur];
	LL fmax=-LINF,smax=-LINF,fmin=LINF,smin=LINF;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		LL delta=maxn[y][0][1]-maxn[y][0][0];
		if (delta>=fmax) smax=fmax,fmax=delta;
		else if (delta>smax) smax=delta;
		delta=minn[y][0][1]-minn[y][0][0];
		if (delta<=fmin) smin=fmin,fmin=delta;
		else if (delta<smin) smin=delta;
	}
	maxn[cur][1][0]=maxsum+fmax+smax;minn[cur][1][0]=minsum+fmin+smin;
	maxsum=0;minsum=0;LL Maxn=-LINF,Minn=LINF,vmax=0,vmin=0;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i];
		maxsum+=maxn[y][0][0];minsum+=minn[y][0][0];
		LL delta=maxn[y][1][0]-maxn[y][0][0];
		Maxn=max(Maxn,delta);
		delta=minn[y][1][0]-minn[y][0][0];
		Minn=min(Minn,delta);
		vmax=max(vmax,1ll*val[y]);vmin=min(vmin,1ll*val[y]);
	}
	maxn[cur][1][0]=max(maxn[cur][1][0],maxsum+Maxn+vmax);
	minn[cur][1][0]=min(minn[cur][1][0],minsum+Minn+vmin);
	maxn[cur][1][1]=maxn[cur][1][0]+val[cur];
	minn[cur][1][1]=minn[cur][1][0]+val[cur];
}

inline void Clear()
{
	for (register int i=1;i<=n;i++) v[i].clear();
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca,x,i;io.Get(ca);
	while (ca--)
	{
		io.Get(n);Clear();
		for (i=2;i<=n;i++) io.Get(x),v[x].pb(i);
		for (i=1;i<=n;i++) io.Get(val[i]);
		dfs(1);
		io.Print(max(max(maxn[1][0][0],maxn[1][0][1]),max(maxn[1][1][0],maxn[1][1][1])),' ');
		io.Print(min(min(minn[1][0][0],minn[1][0][1]),min(minn[1][1][0],minn[1][1][1])),'\n');
	}
	io.flush();return 0;
}
