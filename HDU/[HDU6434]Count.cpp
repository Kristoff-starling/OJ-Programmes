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

const int MAXN=2e7;

int phi[MAXN+48],prime[MAXN+48],tot;
bool isprime[MAXN+48];

inline void init_phi()
{
	memset(isprime,true,sizeof(isprime));
	phi[1]=1;
	for (register int i=2;i<=MAXN;i++)
	{
		if (isprime[i]) prime[++tot]=i,phi[i]=i-1;
		for (register int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]) phi[i*prime[j]]=phi[i]*(prime[j]-1); else phi[i*prime[j]]=phi[i]*prime[j];
			if (i%prime[j]==0) break;
		}
	}
}

LL ans[MAXN+48];
inline void init_ans()
{
	ans[1]=0;
	for (register int i=2;i<=MAXN;i++) if (i&1) ans[i]=ans[i-1]+phi[i]/2; else ans[i]=ans[i-1]+phi[i];
}

int main ()
{
	int ca,i,n;io.Get(ca);
	init_phi();init_ans();
	while (ca--)
	{
		io.Get(n);
		io.Print(ans[n],'\n');
	}
	io.flush();return 0;
}
