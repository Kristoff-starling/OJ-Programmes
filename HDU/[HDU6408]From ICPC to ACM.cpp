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
int c[MAXN+48],d[MAXN+48],m[MAXN+48],p[MAXN+48],e[MAXN+48],R[MAXN+48],E[MAXN+48];

LL ans;

struct warehouse
{
	map<int,int> Mp;
	int tot,delta;
	inline void Clear() {Mp.clear();tot=0;delta=0;}
	inline void push(int sz,int val)
	{
		Mp[val-delta]+=sz;
		tot+=sz;
	}
	inline LL getcargo(int demand)
	{
		LL res=0;
		while (demand && Mp.size())
		{
			if (Mp.begin()->y<=demand)
			{
				res+=1ll*(Mp.begin()->x+delta)*Mp.begin()->y;
				demand-=Mp.begin()->y;tot-=Mp.begin()->y;
				Mp.erase(Mp.begin());
			}
			else
			{
				res+=1ll*(Mp.begin()->x+delta)*demand;
				Mp.begin()->y-=demand;tot-=demand;
				demand=0;
			}
		}
		if (!demand) return res; else return -1;
	}
	inline void reduce(int lim)
	{
		int need=tot-lim;
		while (need>0)
		{
			if (Mp.rbegin()->y<=need)
			{
				tot-=Mp.rbegin()->y;need-=Mp.rbegin()->y;
				Mp.erase(--Mp.end());
			}
			else
			{
				tot-=need;
				Mp.rbegin()->y-=need;
				need=0;
			}
		}				
	}
}w;

int main ()
{
	int i,ca;io.Get(ca);
	while (ca--)
	{
		io.Get(n);w.Clear();
		for (i=1;i<=n;i++) io.Get(c[i]),io.Get(d[i]),io.Get(m[i]),io.Get(p[i]);
		for (i=1;i<=n-1;i++) io.Get(e[i]),io.Get(R[i]),io.Get(E[i]);
		ans=0;int rcost=INF;
		for (i=1;i<=n;i++)
		{
			rcost=min(rcost,c[i]);
			w.push(p[i],rcost+m[i]);
			LL res=w.getcargo(d[i]);
			if (res==-1) {ans=-1;break;} else ans+=res;
			w.reduce(e[i]);
			rcost+=R[i];
			w.delta+=E[i];
		}
		io.Print(ans,'\n');
	}
	io.flush();return 0;
}
