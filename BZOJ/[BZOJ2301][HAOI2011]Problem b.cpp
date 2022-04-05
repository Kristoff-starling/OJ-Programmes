#include <bits/stdc++.h>
#define LL long long
#define LB long double
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int MOD=998244353;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int A,B,C,D,k;
int mu[100048],sum[100048];
bool isprime[100048];int prime[100048],tot;

inline void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));tot=0;mu[1]=1;
	for (i=2;i<=100000;i++)
	{
		if (isprime[i]) prime[++tot]=i,mu[i]=-1;
		for (j=1;j<=tot && (long long)i*prime[j]<=100000;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) mu[i*prime[j]]=0; else mu[i*prime[j]]=-mu[i];
			if (i%prime[j]==0) break;
		}
	}
	sum[1]=mu[1];for (i=2;i<=100000;i++) sum[i]=sum[i-1]+mu[i];
}

inline int solve(int N,int M)
{
	int n=N/k,m=M/k,lim=min(n,m);
	int i=1,pre=0;LL ans=0;
	if (!lim) return 0;
	while (true)
	{
		ans=ans+(long long)(sum[i]-sum[pre])*(n/i)*(m/i);
		if (i==lim) break;
		int n1=n/(n/(i+1)),n2=m/(m/(i+1));
		pre=i;i=min(n1,n2);
	}
	return int(ans);
}

int main ()
{
	int ca;ca=getint();
	sieve();
	while (ca--)
	{
		A=getint();B=getint();C=getint();D=getint();k=getint();
		printf("%d\n",solve(B,D)-solve(A-1,D)-solve(B,C-1)+solve(A-1,C-1));
	}
	return 0;
}
