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

const int MAXN=1e5;

int n,e;
LL val[MAXN+48];
LL a[MAXN+48],tot;

vector<int> v[MAXN+48];

namespace DSU
{
	int pre[MAXN+48];
	inline void init () {for (register int i=1;i<=n;i++) pre[i]=i;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y) {x=find_anc(x);y=find_anc(y);pre[x]=y;}
}

inline bool cmp(int x,int y) {return val[x]<val[y];}

inline void Clear()
{
	for (register int i=1;i<=n;i++) v[i].clear();
}

int bit[MAXN+48][48],sum[MAXN+48][48];

int main ()
{
	int ca,i,x,y;io.Get(ca);
	while (ca--)
	{
		io.Get(n);io.Get(e);Clear();
		for (i=1;i<=n;i++) io.Get(val[i]);
		DSU::init();
		for (i=1;i<=e;i++)
		{
			io.Get(x);io.Get(y);
			DSU::update(x,y);
		}
		for (i=1;i<=n;i++)
			v[DSU::find_anc(i)].pb(i);
		LL ans=0;
		for (i=1;i<=n;i++)
			if (int(v[i].size()))
			{
				tot=int(v[i].size());
				for (register int j=1;j<=tot;j++) a[j]=val[v[i][j-1]];
				sort(a+1,a+tot+1);
				for (register int k=1;k<=31;k++) sum[0][k]=0;
				for (register int j=1;j<=tot;j++)
					for (register int k=1;k<=31;k++)
					{
						if (a[j]&(1<<(k-1))) bit[j][k]=1; else bit[j][k]=0;
						sum[j][k]=sum[j-1][k]+bit[j][k];
					}
				for (register int j=tot;j>=2;j--)
				{
					LL coef=0;
					for (register int k=1;k<=31;k++)
						if (bit[j][k]) coef=(coef+(1ll*(1ll<<(k-1))*sum[j-1][k])%MOD)%MOD;
					ans=(ans+(((1ll*a[j])%MOD)%MOD*coef)%MOD)%MOD;
				}
			}
		io.Print(ans);
	}
	io.flush();return 0;
}
