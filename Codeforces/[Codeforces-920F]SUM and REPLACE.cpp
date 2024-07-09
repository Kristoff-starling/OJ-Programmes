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
using namespace std;

const int MOD=1e9+7;
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

int n,q;
int a[300048],d[1000048];

int prime[1000048],tot;bool isprime[1000048];
inline void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));
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

int go(int x)
{
	int res=1,i,cnt;
	for (i=1;i<=tot;i++)
	{
		if (x%prime[i]==0)
		{
			cnt=0;
			while (x%prime[i]==0)
			{
				cnt++;
				x/=prime[i];
			}
			res*=(cnt+1);
		}
		if (x==1 || prime[i]>int(sqrt(x))) break;
	}
	if (x!=1) res*=2;
	return res;
}

namespace BIT
{
	#define LOWBIT(x) x & (-x)
	LL c[300048];
	inline void update(int x,int delta) {while (x<=n) {c[x]+=delta;x+=LOWBIT(x);}}
	inline LL query(int x){LL res=0;while (x) {res+=c[x];x-=LOWBIT(x);}return res;}
	inline LL calc(int left,int right) {return query(right)-query(left-1);}
}

namespace DSU
{
	int i,pre[300048],rnk[300048];
	inline void init() {for (i=1;i<=n+10;i++) pre[i]=i,rnk[i]=1;}
	inline int find_anc(int x) {if (pre[x]!=x) pre[x]=find_anc(pre[x]);return pre[x];}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		if (rnk[x]>=rnk[y])
		{
			pre[y]=x;
			if (rnk[x]==rnk[y]) rnk[x]++;
		}
		else
			pre[x]=y;
	}
}

int main ()
{
	int i,type,l,r,pos;
	n=getint();q=getint();
	for (i=1;i<=n;i++) a[i]=getint(),BIT::update(i,a[i]);
	sieve();
	for (i=1;i<=1000000;i++) d[i]=go(i);
	DSU::init();
	while (q--)
	{
		type=getint();l=getint();r=getint();
		//for (i=1;i<=n;i++) cout<<BIT::calc(i,i)<<' ';
		//cout<<endl;
		//for (i=1;i<=n;i++) std::cout<<a[i]<<' ';
		//std::cout<<endl;
		if (type==1)
		{
			for (pos=DSU::find_anc(l);pos<=r;pos=DSU::find_anc(pos+1))
			{
				BIT::update(pos,d[a[pos]]-a[pos]);
				a[pos]=d[a[pos]];
				if (a[pos]<=2) DSU::update(pos,pos+1);
			}
		}
		else
		{
			printf("%lld\n",BIT::calc(l,r));
		}
	}
	return 0;
}