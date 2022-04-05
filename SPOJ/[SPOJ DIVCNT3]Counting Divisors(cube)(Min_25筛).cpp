#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

inline LL getLL()
{
    char ch;LL res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

LL n;

const int maxlim=22000000;
const int maxsqrt=348000;
bool noprime[maxlim+48];int prime[maxlim+48],tot;
LL g[maxlim+48],d[maxlim+48],f[maxlim+48];
int mu[maxlim+48];
int omega[maxsqrt+48];
vector<pLL> v[maxsqrt+48];
LL pow2[25],pow3[25];

inline void sieve()
{
	int i,j;g[1]=1;f[1]=1;mu[1]=1;
	for (i=2;i<=maxlim;i++)
	{
		if (!noprime[i])
		{
			prime[++tot]=i;
			g[i]=2;d[i]=1;f[i]=2;mu[i]=-1;
		}
		for (j=1;j<=tot && (long long)i*prime[j]<=maxlim;j++)
		{
			noprime[i*prime[j]]=true;
			if (i%prime[j]==0)
			{
				d[i*prime[j]]=d[i]+1;
				g[i*prime[j]]=g[i]/(d[i]+1)*(d[i]+2);f[i*prime[j]]=0;mu[i*prime[j]]=0;
				break;
			}
			d[i*prime[j]]=1;g[i*prime[j]]=g[i]*2;f[i*prime[j]]=f[i]*2;mu[i*prime[j]]=-mu[i];
		}
	}
	for (i=2;i<=maxlim;i++) g[i]+=g[i-1],f[i]+=f[i-1];
	pow2[0]=pow3[0]=1;
	for (i=1;i<=20;i++) pow2[i]=pow2[i-1]*2,pow3[i]=pow3[i-1]*3;
	omega[1]=0;
	for (i=2;i<=maxsqrt;i++)
		if (!noprime[i])
			for (j=i;j<=maxsqrt;j+=i) omega[j]++;
	int k;
	for (i=1;i<=maxsqrt;i++)
		if (mu[i])
			for (j=i,k=1;j<=maxsqrt;j+=i,k++)
				if (mu[j])
				{
					int tmp1=omega[i],tmp2=omega[k];
					v[i].pb(mp(j,pow2[tmp1]*pow3[tmp2]));
				}
}

LL needg[1000048];

inline LL solve_g(LL N)
{
	if (N<=maxlim) return g[N];
	LL i,pre;LL num,res=0;
	for (i=N;i;pre=i,i=N/(N/i+1))
	{
		if (i==N) num=1; else num=(N/i)-(N/pre);
		res+=i*num;
	}
	return res;
}

LL needf[1000048];

inline int bsearch(int ind,LL cmp)
{
	int res=-1;
	int l=0,r=int(v[ind].size())-1,mid;
	while (l<=r)
	{
		mid=(l+r)>>1;
		if (v[ind][mid].x<=cmp) res=mid,l=mid+1; else r=mid-1;
	}
	return res;
}

LL nn;

inline LL solve_f(LL N)
{
	if (N<=maxlim) return f[N];
	LL lim=int(sqrt(N));int i,j;
	LL res=0;
	for (i=1;i<=lim;i++)
		if (mu[i])
		{
			int pt=bsearch(i,lim+1);
			for (j=0;j<=pt;j++)
			{
				LL aa=v[i][j].x;LL bb=v[i][j].y;
				LL add=mu[aa]*bb*mu[i];
				LL tmp=N/((long long)aa*aa*i);
				if (tmp>maxlim) add*=needg[nn/tmp]; else add*=g[tmp];
				res+=add;
			}
		}
	return res;
}

int main ()
{
	sieve();
	int ca;ca=getint();LL i;int cnt;
	while (ca--)
	{
		n=getLL();int ccc=0;
		for (i=n,cnt=0;i>maxlim;i=n/(n/i+1),cnt++) needg[n/i]=solve_g(i);
		nn=n;
		for (i=n,cnt=0;i>maxlim;i=n/(n/i+1),cnt++) needf[n/i]=solve_f(i);
		LL pre=0,cur;LL ans=0,curans;
		for (i=n;i;i=n/(n/i+1))
		{
			if (i>maxlim) curans=needg[n/i]; else curans=g[i];
			LL R=n/i;
			if (R>maxlim) cur=needf[n/R]; else cur=f[R];
			ans+=(cur-pre)*curans;
			pre=cur;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
