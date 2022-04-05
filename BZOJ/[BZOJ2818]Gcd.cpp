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
#define Pair pair<int,LL>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;
 
const int MOD=100003;
const LL LINF=2e16;
const int INF=1e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
 
inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int tot=0;
int prime[10000048];bool isprime[10000048];int mu[10000048];
int sum[10000048];
int N;

inline void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));
	mu[1]=1;sum[1]=1;
	for (i=2;i<=N;i++)
	{
		if (isprime[i]) prime[++tot]=i,mu[i]=-1;
		sum[i]=sum[i-1]+mu[i];
		for (j=1;j<=tot && (long long)i*prime[j]<=N;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) mu[i*prime[j]]=0; else mu[i*prime[j]]=-mu[i];
			if (i%prime[j]==0) break;
		}
	}
}

int main ()
{
	int i,n;N=getint();
	sieve();
	LL ans=0;
	for (i=1;i<=tot;i++)
	{
		n=N/prime[i];
		int lastpos=1,pos=0;
		while (lastpos<=n && pos<=n)
		{
			pos=n/(n/lastpos);if (pos>n) break;
			ans+=(long long)(sum[pos]-sum[lastpos-1])*(long long)(n/pos)*(n/pos);
			lastpos=pos+1;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
