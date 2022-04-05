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

int n,m,p,c;
LL a[100048],ori[100048];
pair<LL,int> small[10048][31],big[30048][31];

inline LL mod(LL x)
{
	while (x>=p) x-=p;
	while (x<0) x+=p;
	return x;
}

int prime[1000048],tot=0;bool isprime[1000048];
void sieve()
{
	int i,j;
	memset(isprime,true,sizeof(isprime));
	for (i=2;i<=1e6;i++)
	{
		if (isprime[i]) prime[++tot]=i;
		for (j=1;j<=tot && (long long)i*prime[j]<=1e6;j++)
		{
			isprime[i*prime[j]]=false;
			if (i%prime[j]==0) break;
		}
	}
}

int phi[48];

int query_phi(int x)
{
	int res=x,tmp=x,pt=1;
	while ((long long)prime[pt]*prime[pt]<=tmp)
	{
		if (tmp%prime[pt]==0)
		{
			res=res/prime[pt]*(prime[pt]-1);
			while (tmp%prime[pt]==0) tmp/=prime[pt];
		}
		pt++;
	}
	if (tmp!=1) res=res/tmp*(tmp-1);
	return res;
}

void init_phi()
{
	int i;phi[0]=p;
	for (i=1;i<=30;i++)
		phi[i]=query_phi(phi[i-1]);
}

int cnt[100048];
namespace DSU
{
	int pre[100048];
	inline void init()
	{
		for (int i=1;i<=n+10;i++) pre[i]=i;
	}
	inline int find_anc(int x)
	{
		if (pre[x]!=x) pre[x]=find_anc(pre[x]);
		return pre[x];
	}
	inline void update(int x,int y)
	{
		x=find_anc(x);y=find_anc(y);
		pre[x]=y;
	}
}

namespace BIT
{
	LL cc[100048];
	inline void init()
	{
		for (int i=1;i<=n;i++) cc[i]=0;
	}
	inline void update(int x,LL delta)
	{
		while (x<=n)
		{
			cc[x]=mod(cc[x]+delta);
			x+=LOWBIT(x);
		}
	}
	inline LL query(int x)
	{
		LL res=0;
		while (x)
		{
			res=mod(res+cc[x]);
			x-=LOWBIT(x);
		}
		return res;
	}
	inline LL calc(int left,int right)
	{
		return mod(query(right)-query(left-1));
	}
}

void init_pow()
{
	int i,type;
	for (type=0;type<=30;type++)
	{
		small[0][type]=mp(1ll,0);
		for (i=1;i<=10000;i++)
		{
			small[i][type].x=small[i-1][type].x*c;
			if (small[i-1][type].y)
			{
				small[i][type].y=1;
				small[i][type].x%=phi[type];
			}
			else
			{
				small[i][type].y=(small[i][type].x>=phi[type]?1:0);
				small[i][type].x%=phi[type];
			}
		}
		big[1][type]=small[10000][type];big[0][type]=mp(1ll,0);
		for (i=2;i<=30000;i++)
		{
			big[i][type].x=big[i-1][type].x*big[1][type].x;
			if (big[i-1][type].y)
			{
				big[i][type].y=1;
				big[i][type].x%=phi[type];
			}
			else
			{
				big[i][type].y=(big[i][type].x>=phi[type]?1:0);
				big[i][type].x%=phi[type];
			}
		}
	}
}

pair<LL,int> quick_pow(LL x,int mopt)
{
	pair<LL,int> res=mp(0ll,0);
	LL pt1=x/10000,pt2=x%10000;
	res.x=big[pt1][mopt].x*small[pt2][mopt].x;
	if (big[pt1][mopt].y || small[pt2][mopt].y) {res.y=1;res.x%=phi[mopt];return res;}
	res.y=(res.x>=phi[mopt]?1:0);res.x%=phi[mopt];
	return res;
}

pair<LL,int> calc(int step,int mopt,int pos)
{
	if (step==0) return mp(ori[pos]%phi[mopt],ori[pos]>=phi[mopt]?1:0);
	if (phi[mopt]==1) return mp(0ll,1);
	pair<LL,int> res=calc(step-1,mopt+1,pos);
	if (res.y) res.x+=phi[mopt+1];
	return quick_pow(res.x,mopt);
}

int main ()
{
	int i,type,l,r,pt;
	n=getint();m=getint();p=getint();c=getint();
	sieve();init_phi();
	BIT::init();
	for (i=1;i<=n;i++) a[i]=getint(),ori[i]=a[i],BIT::update(i,a[i]);
	memset(cnt,0,sizeof(cnt));DSU::init();
	init_pow();
	while (m--)
	{
		type=getint();l=getint();r=getint();
		if (type==0)
		{
			for (pt=DSU::find_anc(l);pt<=r;pt=DSU::find_anc(pt+1))
			{
				BIT::update(pt,-a[pt]);
				cnt[pt]++;if (cnt[pt]==30) DSU::update(pt,pt+1);
				a[pt]=calc(cnt[pt],0,pt).x;BIT::update(pt,a[pt]);
			}
		}
		else
			printf("%lld\n",BIT::calc(l,r));
	}
	return 0;
}