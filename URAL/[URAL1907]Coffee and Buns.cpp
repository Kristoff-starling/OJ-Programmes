#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <sstream>
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

const int MOD=1e9+3;
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

LL a,n;
int prime[1000048],tot;bool isprime[1000048];
inline void sieve()
{
	int i,j;
	tot=0;memset(isprime,true,sizeof(isprime));
	for (i=2;i<=1000000;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot && (long long)i*prime[j]<=1000000;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) break;
		}
	}
}

LL p[48];int ptot;
inline void Decompose(LL x)
{
	int i;
	for (i=1;i<=tot;i++)
		if (x%prime[i]==0)
		{
			p[++ptot]=prime[i];
			while (x%prime[i]==0) x/=prime[i];
		}
	if (x>1) p[++ptot]=x;
}

inline LL getodd() {if (n%2==1) return n/2+1; else return n/2;}
inline LL geteven() {return n/2;}

inline LL calcodd()
{
	LL res=0;
	int i,Mask;LL st,ed,t,cnt;LL pp;
	for (Mask=1;Mask<=(1<<ptot)-1;Mask++)
	{
		pp=1;
		for (i=1;i<=ptot;i++)
			if (Mask&(1<<(i-1))) pp*=p[i];
		if (pp%2==0) continue;
		st=pp;t=n/pp;
		if (t%2==0) t--;
		if (t<0) continue;
		ed=t*pp;
		cnt=(ed-st)/(pp*2)+1;
		if (__builtin_popcount(Mask)%2==1) res+=cnt; else res-=cnt;
	}
	return res;
}

inline LL calceven()
{
	LL res=0;
	int i,Mask;LL st,ed,t,cnt;LL pp;
	for (Mask=1;Mask<=(1<<ptot)-1;Mask++)
	{
		pp=1;
		for (i=1;i<=ptot;i++)
			if (Mask&(1<<(i-1))) pp*=p[i];
		if (pp%2==0)
		{
			cnt=n/pp;
		}
		else
		{
			if (pp*2>n) cnt=0;
			else
			{
				st=pp*2;t=n/pp;
				if (t%2==1) t--;
				ed=t*pp;
				cnt=(ed-st)/(pp*2)+1;
			}
		}
		if (__builtin_popcount(Mask)%2==1) res+=cnt; else res-=cnt;
	}
	return res;
}

int main ()
{
	a=getLL();n=getLL();
	sieve();Decompose(a);
	if (a%2==0) printf("%lld\n",geteven()+calcodd()); else printf("%lld\n",getodd()+calceven());
	return 0;
}
