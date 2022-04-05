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

int N,M,k,n,m;
int mu[100048],sum[100048];
bool isprime[100048];int prime[100048],tot=0;

inline void init_mu()
{
	int i,j;
	mu[1]=sum[1]=1;memset(isprime,true,sizeof(isprime));
	for (i=2;i<=100000;i++)
	{
		if (isprime[i]) prime[++tot]=i,mu[i]=-1;
		sum[i]=sum[i-1]+mu[i];
		for (j=1;j<=tot && (long long)(i)*prime[j]<=100000;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) mu[i*prime[j]]=0; else mu[i*prime[j]]=-mu[i];
		}
	}
}

int main ()
{
	int ca,x,pos,lastpos;ca=getint();
	init_mu();LL ans1,ans2;int tt=0;
	while (ca--)
	{
		N=getint();N=getint();M=getint();M=getint();k=getint();
		if (k==0)
		{
			printf("Case %d: 0\n",++tt);
			continue;
		}
		if (N>M) swap(N,M);
		n=N/k;m=M/k;lastpos=1;pos=0;ans1=0;ans2=0;
		while (pos<=n && lastpos<=n)
		{
			pos=min(n/(n/lastpos),m/(m/lastpos));if (pos>n) break;
			ans1+=(long long)(sum[pos]-sum[lastpos-1])*(long long)(n/pos)*(m/pos);
			lastpos=pos+1;
		}
		lastpos=1;pos=0;
		while (pos<=n && lastpos<=n)
		{
			pos=n/(n/lastpos);if (pos>n) break;
			ans2+=(long long)(sum[pos]-sum[lastpos-1])*(long long)(n/pos)*(n/pos);
			lastpos=pos+1;
		}
		printf("Case %d: %lld\n",++tt,ans1-(ans2>>1));
	}
	return 0;
}
