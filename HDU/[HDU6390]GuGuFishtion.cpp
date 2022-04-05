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
		for (;ch>32;ch=Getchar()) *++s=ch;
		*(s+1)='\0';
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

const int MAXN=1e6;

int n,m,p;

inline int add(int x) {if (x>=p) x-=p;return x;}
inline int sub(int x) {if (x<0) x+=p;return x;}

int inv[MAXN+48];
inline void init_inv()
{
	inv[0]=inv[1]=1;
	for (register int i=2;i<=MAXN;i++)
		inv[i]=p-((long long)(p/i)*inv[p%i])%p;
}

int prime[MAXN+48],tot=0;bool isprime[MAXN+48];
int mu[MAXN+48],sum[MAXN+48],phi[MAXN+48];
inline void init_mu()
{
	mu[1]=sum[1]=phi[1]=1;
	memset(isprime,true,sizeof(isprime));
	for (register int i=2;i<=MAXN;i++)
	{
		if (isprime[i]) prime[++tot]=i,mu[i]=-1,phi[i]=i-1;
		if (mu[i]>=0) sum[i]=add(sum[i-1]+mu[i]); else sum[i]=sub(sum[i-1]+mu[i]);
		for (register int j=1;j<=tot && 1ll*i*prime[j]<=MAXN;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) mu[i*prime[j]]=0,phi[i*prime[j]]=phi[i]*prime[j]; else mu[i*prime[j]]=-mu[i],phi[i*prime[j]]=phi[i]*(prime[j]-1);
			if (i%prime[j]==0) break;
		}
	}
}

inline int solve(int k)
{
	int N=n/k,M=m/k,lim=min(N,M),cur,pre,res=0;
	for (pre=1;pre<=lim && cur<=lim;pre=cur+1)
	{
		cur=min(N/(N/pre),M/(M/pre));if (cur>lim) break;
		res=add(res+(((1ll*sub(sum[cur]-sum[pre-1]))%p*(N/cur))%p*(M/cur))%p);
	}
	return res;
}

int main ()
{
//	freopen ("a.in","r",stdin);
//	freopen ("a.out","w",stdout);
	int ca;io.Get(ca);
	while (ca--)
	{
		io.Get(m);io.Get(n);io.Get(p);
		init_mu();init_inv();int ans=0;
		for (register int k=1;k<=min(n,m);k++)
		{
			int coef=(1ll*k*inv[phi[k]])%p;
			ans=add(ans+(1ll*coef*solve(k))%p);
		}
		io.Print(ans);
	}
	io.flush();return 0;
}
