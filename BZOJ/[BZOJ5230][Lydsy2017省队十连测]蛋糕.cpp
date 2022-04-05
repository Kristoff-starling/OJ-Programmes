#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
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

const int MOD=998244353;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);
const int T=100;
const double Tmin=1e-8;
const double delta=0.98;

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

LL n,p;
inline LL mod(LL x) {while (x>=p) x-=p;while (x<0) x+=p;return x;}
inline LL mul(LL x) {return x%p;}

const int lim=1000000;

LL phi[lim+48];LL F[lim+48][4];
bool isprime[lim+48];int prime[lim+48],tot;
inline void init()
{
	int i,j;
	phi[1]=1;
	tot=0;memset(isprime,true,sizeof(isprime));
	for (i=2;i<=lim;i++)
	{
		if (isprime[i]) prime[++tot]=i,phi[i]=i-1;
		for (j=1;j<=tot && (long long)i*prime[j]<=lim;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) phi[i*prime[j]]=phi[i]*prime[j]; else phi[i*prime[j]]=phi[i]*(prime[j]-1);
			if (i%prime[j]==0) break;
		}
	}
	F[1][0]=F[1][1]=F[1][2]=1;
	for (i=2;i<=lim;i++)
	{
		F[i][0]=mod(F[i-1][0]+(phi[i]%p));
		F[i][1]=mod(F[i-1][1]+mul(phi[i]*i));
		F[i][2]=mod(F[i-1][2]+mul(mul(phi[i]*i)*i));
	}
}

LL res[10048][5];

inline LL getsum(LL m,int k)
{
	if (k==1) return ((m+1)*m/2)%p;
	if (k==2)
	{
		unsigned long long M=m;
		LL res=((M*(M+1))%(6ll*p)*(M*2+1))%(6ll*p);
		res/=6;return res;
	}
	if (k==3)
	{
		LL res=getsum(m,1)%p;
		return mul(res*res);
	}
}

inline LL solve(int m,int k)
{
	if (m<=lim) return F[m][k];
	if (res[n/m][k]!=-1) return res[n/m][k];
	LL Res=getsum(m,k+1)%p,curans;
	int pre=m,i;
	do
	{
		i=m/(m/pre+1);
		curans=mod(getsum(pre,k)%p-getsum(i,k)%p);
		curans=mul(curans*solve(m/pre,k));
		Res=mod(Res-curans);
		pre=i;
	}
	while (pre!=1);
	res[n/m][k]=Res;
	return Res;
}

int main ()
{
	int i,j;
	n=getint();p=getint();
	init();
	for (i=1;i<=10000;i++)
		for (j=0;j<=2;j++)
			res[i][j]=-1;
	LL ans=mod(mul(mul(mul(4ll*solve(n,0))*n)*n)-mul(mul(6ll*n)*solve(n,1))+mul(2ll*solve(n,2)));
	printf("%lld\n",ans);
	return 0;
}
