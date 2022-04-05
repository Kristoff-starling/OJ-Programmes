#include <bits/stdc++.h>
#define LL long long
#define LB long double 
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define Pair pair<int,int>
#define pii pair<double,double>
#define pLL pair<LL,LL>
#define LOWBIT(x) x & (-x)
using namespace std;

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getcha())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	bool f;char ch;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getcha())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL mod(LL x,LL MO)
{
	while (x>=MO) x-=MO;
	while (x<0) x+=MO;
	return x;
}

inline LL mul(LL x,LL y,LL MO)
{
	x%=MO;LL res=0;
	while (y)
	{
		if (y&1) res=(res+x)%MO,y--;
		x=(x+x)%MO;y>>=1;
	}
	return res;
}

inline LL quick_pow(LL x,LL y,LL MO)
{
	x%=MO;LL res=1;
	while (y)
	{
		if (y&1) res=mul(res,x,MO),y--;
		x=mul(res,x,MO);y>>=1;
	}
	return res;
}

int m,k,ca;

int prime[1000048],tot;bool isprime[1000048];
inline void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));
	for (i=2;i<=300000;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot && (long long)i*prime[j]<=300000;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) break;
		}
	}
}

LL List[300048],ltot;
inline void Decompose()
{
	LL tmp=m,pt=0;
	while (tmp>1)
	{
		pt++;
		if (tmp%prime[pt]==0)
		{
			List[++ltot]=prime[pt];
			while (tmp%prime[pt]==0) tmp/=prime[pt],List[ltot]*=prime[pt];
		}
	}
}

LL sum[300048][148];
LL A[148],M[148],invM[148];

int main ()
{
	m=getLL();k=getLL();ca=getint();
	sieve();Decompose();int i,j;
	for (i=1;i<=ltot;i++)
	{
		sum[i][0]=0;
		for (j=1;j<=List[i]-1;j++) sum[i][j]=mod(sum[i][j-1]+quick_pow(j,k,List[i]),List[i]);
	}
	for (i=1;i<=ltot;i++) M[i]=m/list[i],invM[i]=quick_pow(
}
